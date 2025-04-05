import pyvisa 
import sys 
import os
import time as times 
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

REMOTE_IP = '192.168.0.104'
PORT = 4884
oscilloscope = None
def printIntroducing():
    print("\nThis is a program to process oscilloscope by \nRABBIT CAVE NUCLEAR ELECTRONICS TEAM\n")


def visaConnect():
    try:
        # Connect to the oscilloscope
        rm = pyvisa.ResourceManager('@py')
        oscilloscope = rm.open_resource(f'TCPIP0::{REMOTE_IP}::INSTR')
        oscilloscope.timeout = 100  # Set timeout to 0.1 seconds
        print('Connected to oscilloscope')
        print("Instrument ID:", oscilloscope.query("*IDN?"))
        return oscilloscope
    except Exception as e:
        print(f'Failed to connect to oscilloscope: {e}')
        return None
        #sys.exit(1)
def visaWrite(oscilloscope, command):
    try:
        read = oscilloscope.write(command)
        times.sleep(0.1)
        return read
    except Exception as e:
        print(f'Failed to write command: {command}')
        
def visaQuery(oscilloscope, command):
    try:
        read = oscilloscope.query(command)
        return read
    except Exception as e:
        print(f'Failed to query command: {command}')

def read_data_byChannel(oscilloscope, channelInp):
    try :
        visaWrite(oscilloscope, f':WAVeform:SOURce CHANnel{channelInp}')
        visaWrite(oscilloscope, ":WAVeform:POINts:MODE NORMal")
        visaWrite(oscilloscope, ":WAVeform:FORMat BYTE")
        visaWrite(oscilloscope, ":WAVeform:DATA?")
        return oscilloscope.read_raw()
    except Exception as e:
        print(f'Failed to read data: {e}')
        return None

def plot_data(read_data, channelInp):
    #  Get the waveform data
    header_len = 2 + int(read_data[1:2].decode())  # e.g., b'#80001200...'
    data_start = header_len
    waveform = np.frombuffer(read_data[data_start:], dtype=np.uint8)

    #  Get the waveform parameters
    x_increment = float(oscilloscope.query(":WAV:XINC?"))
    x_origin = float(oscilloscope.query(":WAV:XOR?"))
    y_increment = float(oscilloscope.query(":WAV:YINC?"))
    y_origin = float(oscilloscope.query(":WAV:YOR?"))
    y_reference = float(oscilloscope.query(":WAV:YREF?"))

    #  Calculate the time and voltage values (change to offset)
    voltage = (waveform - y_reference) * y_increment + y_origin
    time = np.arange(len(voltage)) * x_increment + x_origin

    #  Plot the waveform
    plt.figure(figsize=(10, 5))
    plt.plot(time, voltage, label=f'CH{channelInp}')
    plt.title("Oscilloscope Waveform")
    plt.xlabel("Time (s)")
    plt.ylabel("Voltage (V)")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()



printIntroducing()
oscilloscope = visaConnect()

while oscilloscope is None:
    REMOTE_IP = input('Enter the IP address of the oscilloscope: ')
    oscilloscope = visaConnect()
    
    if oscilloscope is None:
        REMOTE_IP = None

while True:
    