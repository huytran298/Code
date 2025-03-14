import pyvisa 
import sys 
import time 
import numpy as np
import matplotlib.pyplot as plt
'''
 install library:
 python get-pip.py
 pip install pyvisa 
 pip install pyvisa pyvisa-py

'''

REMOTE_IP = '192.168.1.93'
PORT = 4884
oscilloscope = None
def visa_connect():
    try:
        rm = pyvisa.ResourceManager('@py')
        oscilloscope = rm.open_resource(f'TCPIP0::{REMOTE_IP}::INSTR')
        oscilloscope.timeout = 100  # Set timeout to 0.1 seconds
        print('Connected to oscilloscope')
        print("Instrument ID:", oscilloscope.query("*IDN?"))
        return oscilloscope
    except Exception as e:
        print(f'Failed to connect to oscilloscope: {e}')
        sys.exit(1)

oscilloscope = visa_connect()
time.sleep(0.1)
oscilloscope.write(":WAVeform:SOURce CHANnel1")
time.sleep(0.1)
oscilloscope.write(":WAVeform:POINts:MODE NORMal")
time.sleep(0.1)
oscilloscope.write(":WAVeform:FORMat BYTE")
time.sleep(0.1)
oscilloscope.write(":WAVeform:DATA?")
read_data = oscilloscope.read_raw()

header_len = 2 + int(read_data[1:2].decode())  # e.g., b'#80001200...'
data_start = header_len
waveform = np.frombuffer(read_data[data_start:], dtype=np.uint8)

x_increment = float(oscilloscope.query(":WAV:XINC?"))
x_origin = float(oscilloscope.query(":WAV:XOR?"))
y_increment = float(oscilloscope.query(":WAV:YINC?"))
y_origin = float(oscilloscope.query(":WAV:YOR?"))
y_reference = float(oscilloscope.query(":WAV:YREF?"))

voltage = (waveform - y_reference) * y_increment + y_origin
time = np.arange(len(voltage)) * x_increment + x_origin

# 7. Plot the waveform
plt.figure(figsize=(10, 5))
plt.plot(time, voltage, label="CH1")
plt.title("Oscilloscope Waveform")
plt.xlabel("Time (s)")
plt.ylabel("Voltage (V)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()



