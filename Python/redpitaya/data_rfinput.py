import pyvisa as visa
import redpitaya_scpi as scpi
import sys
import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import math

IP = 'rp-f03c0e.local'
rp = scpi.scpi(IP)



# Setup
rp.tx_txt('ACQ:RST')
rp.tx_txt('ACQ:DEC 8')
rp.tx_txt('ACQ:AVG OFF')
rp.tx_txt('ACQ:DATA:UNITS VOLTS')

# Cấu hình NEGATIVE trigger
trigger = float(input("Input trigger level : "))
# baseline_time = int(input("Input time calculate baseline : "))
max_volt = float(input("Input maximum voltage : "))

rp.tx_txt(f'ACQ:TRIG:LEV {-0.05}')      # Trigger khi xuống dưới -0.1V
rp.tx_txt('ACQ:START')
rp.tx_txt('ACQ:TRIG CH1_NE')        # NE = Negative Edge (cạnh xuống)
TRIGGER_DELAY = 6000  
rp.tx_txt(f'ACQ:TRIG:DLY {TRIGGER_DELAY}')


    
max_channels = int(2 ** math.log2(1024))
channels = np.zeros(max_channels + 1)
x_axis = [i for i in range(max_channels + 1)]

minV = 0
maxV = -1
def trapezoidal_filter_auto(signal, k, l):
    """
    Auto-detect nếu signal là positive hay negative pulses
    """
    n = len(signal)
    
    # Detect polarity
    baseline = np.median(signal)
    above = np.sum(signal > baseline + np.std(signal))
    below = np.sum(signal < baseline - np.std(signal))
    
    if below > above:
        print("Detected: NEGATIVE pulses (PMT-style)")
        # Invert signal
        processed_signal = baseline - signal
    else:
        print("Detected: POSITIVE pulses")
        processed_signal = signal - baseline
    
    # Apply standard filter on corrected signal
    filtered = np.zeros(n)
    d = np.zeros(n)
    p = np.zeros(n)
    r = np.zeros(n)
    s = np.zeros(n)
    
    for i in range(1, n):
        d[i] = processed_signal[i] - processed_signal[i-1]
        
        if i >= k:
            p[i] = p[i-1] + d[i] - d[i-k]
        else:
            p[i] = p[i-1] + d[i]
        
        if i >= l:
            r[i] = p[i-l]
        
        if i >= k:
            s[i] = s[i-1] + p[i] - r[i-k]
        else:
            s[i] = s[i-1] + p[i]
        
        filtered[i] = s[i] / (k * k)
    
    return filtered
def trapezoidal_filter(x, L, M):
    """
    x: 1D numpy array of ADC samples (float)
    L: rise/decay length in samples (peaking length)
    M: flat-top width in samples
    returns: y, filtered array (same length), valid region where output stable is from index 2*L+M-1 onwards
    """
    x = np.asarray(x, dtype=float)
    n = len(x)
    # cumulative sum for fast range sums
    c = np.concatenate(([0.0], np.cumsum(x)))
    # helper to compute sum x[a:b] = c[b]-c[a]
    y = np.zeros(n)
    # For index k (0-based), trapezoid output at sample k is:
    # y[k] = (sum_{i=k-2L-M+1}^{k-L-M} x[i] - sum_{i=k-L+1}^{k} x[i]) / L
    # We'll implement with bounds checks; valid k start = 2L+M-1
    for k in range(n):
        a1 = k - 2*L - M + 1
        b1 = k - L - M + 1
        a2 = k - L + 1
        b2 = k + 1
        if a1 < 0 or b1 < 0 or a2 < 0:
            y[k] = 0.0
        else:
            sum1 = c[b1] - c[a1]
            sum2 = c[b2] - c[a2]
            y[k] = (sum1 - sum2) / L
    return y


try :

    baseline_value = 0

    # beginTime = time.time()
    # while True : 
    #     rp.tx_txt('ACQ:TRig:STAT?')
    #     if rp.rx_txt() == 'TD':
    #         continue
    #    #Get latest single value
    #     rp.tx_txt('ACQ:SOUR1:DATA?')
    #     response = rp.rx_txt()
    #     sumavg = 0
    #     cnt = 0
    #     data = [float(val) for val in response.strip('{}').split(',') if val.strip()]
    #     for val in response.strip('{}').split(',') :
    #         if val.strip() : 
    #             sumavg += float(val)
    #             cnt += 1
        
    #     if baseline_value == 0:
    #         baseline_value = sumavg / cnt
    #     else : 
    #         baseline_value = (sumavg / cnt) + baseline_value
    #         baseline_value /= 2
        
    #    #Print with overwrite
    #     print(sumavg/cnt)
    #     time.sleep(0.001) 
    #     if time.time() - beginTime >= 5:
    #         break
    # print(f'baseline value is : {baseline_value}')
    # ready = input("Is ready for analyzer ? [y/n]")
    # if ready == 'n' : 
    #     rp.close()
    #     sys.exit(0)
    fig, ax = plt.subplots()
    bars = ax.bar(x_axis ,channels, width=2)
    #ax.set_xlim(xmin=int(abs(trigger) / max_volt * max_channels), xmax=max_channels + 10)
    # rp.tx_txt(f'ACQ:TRIG:LEV {trigger}')      # Trigger khi xuống dưới -0.1V
    # rp.tx_txt('ACQ:TRIG CH1_NE')        # NE = Negative Edge (cạnh xuống)
    # rp.tx_txt('ACQ:TRIG NOW')
    for bar in bars:
        bar.sticky_edges.y.append(0)  # đáy cột ở 0
    def animate(frame):
    # Cập nhật mảng
        rp.tx_txt('ACQ:TRIG:STAT?')
        if rp.rx_txt() == 'TD':
            rp.tx_txt('ACQ:SOUR1:DATA?')
            raw_data = rp.rx_txt()
            rp.tx_txt('ACQ:STOP')    # Dừng acquisition cũ
            rp.tx_txt('ACQ:RST')      # Reset trigger
            filterData = [float(i) for i in np.fromstring(raw_data.strip('{}'), sep=',')]
            filterData = trapezoidal_filter(filterData, 48, 8)
            
            channTrig = int(abs(trigger) / max_volt * max_channels)
            
            chann = int((abs(min(filterData)) / max_volt) * max_channels)
            if 0 <= chann < max_channels: 
                
                channels[chann] += 1

            for bar, h in zip(bars, channels):
                bar.set_height(h)
            # ax.set_ydata(channels)  # Chỉ cập nhật y data, x không đổi
            
            ax.relim()
            ax.autoscale_view(scalex=True, scaley=True)
            rp.tx_txt(f'ACQ:TRIG:LEV {-0.05}')      # Trigger khi xuống dưới -0.1V
            rp.tx_txt('ACQ:START')
            rp.tx_txt('ACQ:TRIG CH1_NE')    
        return bars
    ani = animation.FuncAnimation(fig, animate, interval=0.01, blit=False, cache_frame_data=True)
    plt.title('Real-time Array Update')
    plt.show()

except KeyboardInterrupt:
    print("\n\nStopped.")
    rp.tx_txt('ACQ:STOP')
    plt.figure()
    plt.plot(channels)
    plt.title('Filtered Data')
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')
    plt.show()
    rp.close()