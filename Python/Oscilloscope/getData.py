import pyvisa 
import sys 
import os
import time 
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
'''
    install library:
    python get-pip.py
    pip install pyvisa 
    pip install pyvisa pyvisa-py
    pip install numpy
    pip install matplotlib
    pip install pandas
'''

REMOTE_IP = '192.168.1.93'
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
        time.sleep(0.1)
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
options = [1, 2, 3, 4]
print('Connected to oscilloscope')
print("Choose option you want to do:")
print('1. Plot data from oscilloscope')
print('2. Plot all data from oscilloscope')
print('3. Save data to file')
print('4. Exit')
option = input("Enter the option: ")
if option == '1':
        #set channel
    read_data = None
    while read_data is None:
        print("Choose channel you want to get data:")
        print("1. Channel 1")
        print("2. Channel 2")
        print("3. Channel 3")
        print("4. Channel 4")
        channelInp = input("Enter the channel: ")
        #check channel is valid
        if channelInp not in ['1','2','3','4']:
            print("Invalid channel")
        read_data = read_data_byChannel(oscilloscope, channelInp)
    plot_data(read_data, channelInp)
elif option == '2':
    read_data = None
    
    for i in range(1,5):
        read_data = read_data_byChannel(oscilloscope, i)
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
        voltage = (waveform - y_reference)  # * y_increment + y_origin
        times = np.arange(len(voltage)) * x_increment + x_origin

        #  Plot the waveform
        
        plt.plot(times, voltage, label=f'CH{i}')
        time.sleep(0.1)
        
    plt.xlabel("Time (s)")
    plt.ylabel("Voltage (V)")   
    plt.title("Oscilloscope Waveform")
    plt.grid(True)
    plt.legend()
    plt.show()
elif option == '3':
    file_name = input("Enter the file name (DO NOT INCLUDE FILE EXTENSION): ")
    number = input("Enter the number of data you want to get: ")
    sure = input(f"Are you sure you want to run ? (Y/N)")
    if sure == 'N' or sure == 'n':
        sys.exit(1)
    counter = 1
    subcounter = 0
    while (True):
        visaWrite(oscilloscope, ':SINGle')
        while(visaQuery(oscilloscope, ':TRIGger:SWEep?') == "NORM\n"):
            #print('Is waiting for trigger')
            time.sleep(0.01)
        #continue
        voltages = []
        times = []
        for i in range(1,5):
            read_data = read_data_byChannel(oscilloscope, i)
            
            read_data = read_data_byChannel(oscilloscope, i)
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
            V = (waveform - y_reference) * y_increment + y_origin
            voltages.append(V)
            times.append(np.arange(len(V)) * x_increment + x_origin)

        
        # Save data to file
        originPath = os.getcwd()
        if subcounter == 0:
            originPath += '/' + file_name + f'{counter}.csv'
        else :
            originPath += '/' + file_name + f'_{subcounter}_{counter}.csv'
        counter += 1
        if counter > int(number):
            counter = 1
            subcounter += 1
        data = {'Time': times[0], 'CH1': voltages[0], 'CH2': voltages[1], 'CH3': voltages[2], 'CH4': voltages[3]}
        df = pd.DataFrame(data)
        df.to_csv(originPath, index=False)
        print(f"Save data to {originPath}")
        
elif option == '4':
    sys.exit(1)



