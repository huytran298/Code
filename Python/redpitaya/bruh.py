import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.widgets import SpanSelector
import redpitaya_scpi as scpi


IP = 'rp-f03c0e.local'
rp = scpi.scpi(IP)


# Cấu hình acquisition
rp.tx_txt("ACQ:RST")
rp.tx_txt("ACQ:DEC 1")
rp.tx_txt("ACQ:TRIG:LEV -0.1")
rp.tx_txt("ACQ:TRIG:SOUR CH2_NE")
rp.tx_txt("ACQ:START")

n_bins = 1024
hist = np.zeros(n_bins, dtype=int)

# ROI mặc định
roi_range = [0, 1024]

def trapezoidal_filter(x, L=48, M=8):
    if len(x) < 2*L+M: return np.array([])
    a = np.ones(L)
    b = np.ones(L)
    s1 = np.convolve(x, a, mode='valid')
    s2 = np.convolve(x, b, mode='valid')
    s2 = np.concatenate([np.zeros(M), s2])[:len(s1)]
    return s1 - s2

# Figure setup
fig, ax = plt.subplots()
line, = ax.plot(hist, drawstyle="steps-mid")
ax.set_xlim(0, n_bins)
ax.set_ylim(0, 10)
ax.set_xlabel("Channel")
ax.set_ylabel("Counts")
title = ax.set_title("Realtime MCA - ROI: {}–{} | Counts = 0".format(*roi_range))

def update(frame):
    global hist, roi_range
    rp.tx_txt("ACQ:TRIG NOW")
    while True:
        rp.tx_txt("ACQ:TRIG:STAT?")
        if rp.rx_txt() == "TD":
            break
    rp.tx_txt("ACQ:SOUR2:DATA?")
    data_str = rp.rx_txt().strip("{}\n\r").replace("  ", "").split(',')
    data = np.array(data_str, dtype=np.float32)

    shaped = trapezoidal_filter(data)
    if shaped.size > 0:
        thr = np.mean(shaped) - 5*np.std(shaped)  # vì xung âm
        peaks = np.where((shaped[1:-1] < shaped[:-2]) & 
                         (shaped[1:-1] < shaped[2:]) & 
                         (shaped[1:-1] < thr))[0]+1
        for i in peaks:
            amp = -shaped[i]   # đảo dấu
            bin_idx = int(np.clip((amp / 5.0) * n_bins, 0, n_bins-1))
            print(bin_idx)
            hist[bin_idx] += 1

    line.set_ydata(hist)
    ax.set_ylim(0, max(hist.max(), 10))

    lo, hi = roi_range
    counts = hist[lo:hi].sum()
    title.set_text(f"Realtime MCA - ROI: {lo}–{hi} | Counts = {counts}")
    return line,

def onselect(xmin, xmax):
    global roi_range
    roi_range = [int(xmin), int(xmax)]

# ROI selector
span = SpanSelector(ax, onselect, 'horizontal', useblit=True,
                    props=dict(alpha=0.3, facecolor='red'))

ani = animation.FuncAnimation(fig, update, interval=0.01)
plt.show()
