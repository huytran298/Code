import socket
import time
import numpy as np
import matplotlib.pyplot as plt

class RedPitayaOscilloscope:
    def __init__(self, ip_address, port=5000):
        """Initialize connection to Red Pitaya"""
        self.ip = ip_address
        self.port = port
        self.socket = None
        
    def connect(self):
        """Establish SCPI connection"""
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.ip, self.port))
            print(f"Connected to Red Pitaya at {self.ip}")
        except Exception as e:
            print(f"Connection failed: {e}")
            raise
    
    def send_command(self, command):
        """Send SCPI command"""
        self.socket.sendall(f"{command}\r\n".encode())
    
    def receive_response(self):
        """Receive response from Red Pitaya"""
        response = b''
        while True:
            chunk = self.socket.recv(4096)
            response += chunk
            if len(chunk) < 4096:
                break
        return response.decode().strip()
    
    def query(self, command):
        """Send command and get response"""
        self.send_command(command)
        time.sleep(0.1)
        return self.receive_response()
    
    def setup_trigger(self, trigger_voltage, channel='CH1'):
        """Setup trigger with falling edge and single mode"""
        # Reset acquisition
        self.send_command('ACQ:RST')
        time.sleep(0.1)
        
        # Set decimation (sampling rate)
        self.send_command('ACQ:DEC 1')  # Full speed (125 MS/s)
        
        # Set trigger delay to 0 (trigger at center)
        self.send_command('ACQ:TRIG:DLY 0')
        
        # Set trigger level (voltage)
        self.send_command(f'ACQ:TRIG:LEV {trigger_voltage}')
        
        # Set trigger source with negative edge (falling)
        self.send_command(f'ACQ:TRIG {channel}_NE')
        
        print(f"Trigger configured: {channel}, Falling edge, Level: {trigger_voltage}V")
    
    def acquire_data(self, channel='CH1'):
        """Start acquisition and wait for trigger"""
        print("Waiting for trigger event...")
        
        # Start acquisition
        self.send_command('ACQ:START')
        time.sleep(0.1)
        
        # Start trigger (wait for external event)
        self.send_command('ACQ:TRIG CH1_NE')
        
        # Wait for trigger
        triggered = False
        timeout = 30  # 30 seconds timeout
        start_time = time.time()
        
        while not triggered:
            status = self.query('ACQ:TRIG:STAT?')
            if 'TD' in status:  # Triggered
                triggered = True
                print("Trigger event detected!")
            elif time.time() - start_time > timeout:
                print("Trigger timeout!")
                return None, None
            time.sleep(0.1)
        
        # Wait for buffer to fill
        time.sleep(0.5)
        
        # Read data
        source = 'SOUR1' if channel == 'CH1' else 'SOUR2'
        data_str = self.query(f'ACQ:{source}:DATA?')
        
        # Parse data
        data_str = data_str.replace('{', '').replace('}', '')
        voltage_data = np.array([float(x) for x in data_str.split(',')])
        
        # Generate time array
        decimation = int(self.query('ACQ:DEC?'))
        sampling_rate = 125e6 / decimation  # Base rate is 125 MS/s
        num_samples = len(voltage_data)
        time_data = np.arange(num_samples) / sampling_rate
        
        return time_data, voltage_data
    
    def disconnect(self):
        """Close connection"""
        if self.socket:
            self.socket.close()
            print("Disconnected from Red Pitaya")

def analyze_sipm_pulse(time_data, voltage_data):
    """
    Analyze SiPM pulse: find peak and calculate integral from 10% on both sides
    """
    # Find peak (most negative value for negative pulse)
    v_max_idx = np.argmin(voltage_data)
    v_max = voltage_data[v_max_idx]
    
    print(f"\nPulse Analysis:")
    print(f"Peak voltage: {v_max:.6f} V at time {time_data[v_max_idx]*1e6:.3f} μs")
    
    # Calculate 10% threshold
    threshold = -0.033
    print(f"10% threshold: {threshold:.6f} V")
    
    # Find index a: first point from left where v < threshold (going down)
    a = 0
    for i in range(v_max_idx, 0, -1):
        if voltage_data[i] > threshold:
            a = i
            break
            
    
    # Find index b: first point from right where v < threshold (going up)
    b = len(voltage_data) - 1
    for i in range(v_max_idx, len(voltage_data)):
        if voltage_data[i] > threshold:
            b = i
            break
    
    print(f"Range: index {a} to {b}")
    print(f"Time range: {time_data[a]*1e6:.3f} μs to {time_data[b]*1e6:.3f} μs")
    print(f"Voltage range: {voltage_data[a]:.6f} V to {voltage_data[b]:.6f} V")
    
    # Calculate the sum: Σ[(v[i] - v[i-1]) / (50 * (t[i] - t[i-1]))]
    total_sum = 0.0
    dt = 8 * 10 ** (-9)
    for i in range(a, b + 1):
        total_sum += -voltage_data[i]
    total_sum = (dt * total_sum) / (50 * 1.6 * 10 ** (-19))
    print(f"\nCalculated Sum: {total_sum:.6e}")
    
    return v_max, v_max_idx, a, b, threshold, total_sum

def main():
    # Get Red Pitaya IP address
    # ip_address = input("Enter Red Pitaya IP address (e.g., 192.168.1.100): ")
    ip_address = '169.254.110.81'
    # Get trigger voltage
    # trigger_voltage = float(input("Enter trigger voltage (V): "))
    trigger_voltage = -0.1
    # Create oscilloscope instance
    osc = RedPitayaOscilloscope(ip_address)
    
    try:
        # Connect
        osc.connect()
        
        # Setup trigger (falling edge, single mode)
        osc.setup_trigger(trigger_voltage, channel='CH1')
        
        # Acquire data
        time_data, voltage_data = osc.acquire_data(channel='CH1')
        
        if time_data is not None and voltage_data is not None:
            print(f"\nData acquired successfully!")
            print(f"Number of samples: {len(voltage_data)}")
            print(f"Time range: {time_data[0]:.6f}s to {time_data[-1]:.6f}s")
            print(f"Voltage range: {voltage_data.min():.3f}V to {voltage_data.max():.3f}V")
            
            # Analyze SiPM pulse
            v_max, v_max_idx, a, b, threshold, total_sum = analyze_sipm_pulse(time_data, voltage_data)
            
            # Plot data
            plt.figure(figsize=(12, 8))
            
            # Plot full signal
            plt.plot(time_data * 1e6, voltage_data, 'b-', linewidth=1, label='Full Signal')
            
            # Highlight analyzed region
            plt.plot(time_data[a:b+1] * 1e6, voltage_data[a:b+1], 'r-', linewidth=2, label='Analysis Region')
            
            # Mark peak
            plt.plot(time_data[v_max_idx] * 1e6, v_max, 'go', markersize=10, label=f'Peak: {v_max:.3f}V')
            
            # Mark boundaries
            plt.plot(time_data[a] * 1e6, voltage_data[a], 'ms', markersize=8, label=f'Start (10%)')
            plt.plot(time_data[b] * 1e6, voltage_data[b], 'cs', markersize=8, label=f'End (10%)')
            
            # Draw threshold line
            plt.axhline(y=threshold, color='orange', linestyle='--', 
                       label=f'10% Threshold: {threshold:.3f}V', linewidth=1.5)
            
            # Draw trigger line
            plt.axhline(y=trigger_voltage, color='purple', linestyle='--', 
                       label=f'Trigger: {trigger_voltage}V', linewidth=2)
            
            plt.xlabel('Time (μs)', fontsize=12)
            plt.ylabel('Voltage (V)', fontsize=12)
            plt.title(f'SiPM Pulse Analysis - Sum: {total_sum:.3e}', fontsize=14)
            plt.grid(True, alpha=0.3)
            plt.legend(fontsize=10)
            plt.tight_layout()
            plt.show()
            
            # Return data and analysis results
            return time_data, voltage_data, total_sum
        else:
            print("Failed to acquire data")
            return None, None, None
            
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        return None, None, None
    
    finally:
        # Disconnect
        osc.disconnect()

if __name__ == "__main__":
    time_data, voltage_data, total_sum = main()