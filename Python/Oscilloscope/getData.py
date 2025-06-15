
import pyvisa 
import sys 
import os
import time as times 
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import shutil
'''
    install library:
    python get-pip.py
    pip install pyvisa 
    pip install pyvisa pyvisa-py
    pip install numpy
    pip install matplotlib
    pip install pandas
'''

# Configure 
REMOTE_IP = '192.168.0.113'
PORT = 4884
oscilloscope = None

def printIntroducing():
    print("\nThis is a program to process oscilloscope by \nRABBIT CAVE NUCLEAR ELECTRONICS TEAM\n")


def visa_connect():
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
def visa_write(oscilloscope, command):
    try:
        oscilloscope.write(command)
        #times.sleep(0.01)
    except Exception as e:
        print(f'Failed to write command: {e}')
      
def visa_query(oscilloscope, command):
    try:
        query = oscilloscope.query(command)
        #times.sleep(0.01)
        return query
    except Exception as e:
        print(f'Failed to query command: {e}')

def read_data_byChannel(oscilloscope, channelInp):
    try :
        visa_write(oscilloscope, f':WAVeform:SOURce CHANnel{channelInp}')
        visa_write(oscilloscope, ":WAVeform:POINts:MODE NORMal")
        visa_write(oscilloscope, ":WAVeform:FORMat BYTE")
        visa_write(oscilloscope, ":WAVeform:DATA?")
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

def auto_trigger(oscilloscope, channelInp, minThreshold, maxThreshold, stepThreshold, frequency, intervalTime):
    print(f'------Ready to run trigger threshold channel {channelInp}------')
    while(abs(minThreshold) < abs(maxThreshold)):
        visa_write(oscilloscope, f':TRIGger:LEVel {minThreshold} ,CHANnel{channelInp}')
        print(f'Write {minThreshold} for channel {channelInp}')
        countSignal = 0
        #times.sleep(0.01)
        timebefore = times.time()
        isRun = 1
        lastfreq = 0
        while times.time() - timebefore < float(intervalTime):
            try : 
                if isRun == 1:
                    visa_write(oscilloscope, ':SINGle')
                    isRun = 0
                #times.sleep(0.001)
                if visa_query(oscilloscope, ':TRIGger:SWEep?') == "AUTO\n":
                    #print('is calculate')
                    read_data = read_data_byChannel(oscilloscope, channelInp)
                    header_len = 2 + int(read_data[1:2].decode())
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
                    #time = np.arange(len(voltage)) * x_increment + x_origin
                    isRun = 1
                    if min(voltage) <= minThreshold :
                        countSignal += 1
            except Exception as e:
                print(f"smt error {e}")
                continue
                
        print('Frequency is', round(countSignal / intervalTime, 3))
        print('Count is ', countSignal)
        minThreshold += stepThreshold
        lastfreq = countSignal/int(intervalTime)
        if lastfreq < frequency:
            break
        
        
    return round(countSignal / intervalTime, 3), countSignal, minThreshold


printIntroducing()
oscilloscope = visa_connect()

while oscilloscope is None:
    REMOTE_IP = input('Enter the IP address of the oscilloscope: ')
    oscilloscope = visa_connect()
    
    if oscilloscope is None:
        REMOTE_IP = None

print('Connected to oscilloscope')
print("Choose option you want to do:")
print('1. Plot data from oscilloscope')
print('2. Plot all data from oscilloscope')
print('3. Save data to file')
print('4. Trigger data')
print('5. Calculate Gain')
print('6. Calculate frequency')
print('7. Measuring')
print('8. Exit')
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
        voltage = (waveform - y_reference)  * y_increment + y_origin
        times = np.arange(len(voltage)) * x_increment + x_origin

        #  Plot the waveform
        
        plt.plot(times, voltage, label=f'CH{i}')
        times.sleep(0.1)
        
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
        visa_write(oscilloscope, ':SINGle')
        while(visa_query(oscilloscope, ':TRIGger:SWEep?') == "NORM\n"):
            #print('Is waiting for trigger')
            times.sleep(0.01)
        #continue
        voltages = []
        times = []
        for i in range(1,5):
            read_data = read_data_byChannel(oscilloscope, i)
            header_len = 2 + int(read_data[1:2].decode())  
            data_start = header_len
            waveform = np.frombuffer(read_data[data_start:], dtype=np.uint8)
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
    print('still develop')
    exit(0)
    print('Select channel to trigger (1 to select, 1 to remove):')
    channels = []
    for i in range(1, 5):
        inp = input(f'{i}. Channel {i}: ')
        if(inp == '1'):
            channels.append(i)
        else :
            if inp != '0':
                print('Invalid input')
                #i = i - 1
    # Input trigger value
    triggerChannel = []
    for i in channels:
        inp = input(f'Input trigger value for channel {i}: ')
        triggerChannel.append(float(inp))
    #create file first
    originPath = os.getcwd()
    for i in channels:
        #originPath += 
        
        df.to_csv(originPath + '/' + f'triggerChannel_{i}.csv', index=False)
    while ():
        for i in range(0, len(channels)):
            try:
                read_data = read_data_byChannel(oscilloscope, channels[i])
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
                voltage = (waveform - y_reference)# * y_increment + y_origin
                v = min(voltage)
                if min(voltage) < float(triggerChannel[i]) :
                    #read file 
                    df = pd.read_csv(originPath + '/' + f'triggerChannel_{channels[i]}.csv')
                    #add data to file
                    df['CH{channels[i]}'] = voltage
            except:
                print('passed')
elif option == '5':
    read_data = None
    print("Choose channel you want to get data:")
    print("1. Channel 1")
    print("2. Channel 2")
    print("3. Channel 3")
    print("4. Channel 4")
    channelInp = input("Enter the channel: ")
    threshold = input("Enter the threshold: ")
    #check channel is valid
    if channelInp not in ['1','2','3','4']:
        print("Invalid channel")
        exit(1)
    while 1:
            # ready = input("Is the data ready? (Y/N): ")
            # if ready == 'N' or ready == 'n':
            #     print("Please wait for data to be ready")
            #     break
        visa_write(oscilloscope, ':SINGle')
        times.sleep(0.0001)
        while(visa_query(oscilloscope, ':TRIGger:SWEep?') == "NORM\n"):
            continue
        read_data = read_data_byChannel(oscilloscope, channelInp)
        header_len = 2 + int(read_data[1:2].decode())
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
            
        if min(voltage) < float(threshold):
            # Filter voltage values within the range
            minValue = min(voltage)
            filtered_voltage = [v for v in voltage if 0.1 * float(minValue) > v >= float(minValue)]
            # Calculate the sum of the filtered voltage values
            sum_voltage = abs(sum(filtered_voltage))
            gain = sum_voltage * (time[1] - time[0]) / (50 * 1.6 * 10 ** (-19)) 
            gain = gain * 10 ** (-6)
            print(f"Gain: {gain} V")     
elif option == '6':
    
    channelInp = [int(x) for x in input("Enter the channel: ").split(' ')]
    #check channel is valid
    for i in channelInp:
        if i > 4 and i < 1:
            print('Channel(s) input is invalid')
            sys.exit(1)
    minThreshold = []
    maxThreshold = []
    stepThreshold = []
    for i in channelInp :
        minThreshold.append(float(input(f"Enter the min threshold for channel {i} (Volt): ")))
        maxThreshold.append(float(input(f"Enter the max threshold for channel {i} (Volt): ")))
        stepThreshold.append(float(input(f"Enter the step threshold channel {i} (Volt): ")))
    frequency = int(input("Enter the frequency (Hz) (it is for all channel(s)): "))
    intervalTime = int(input("Enter the interval time (second(s))  (it is for all channel(s)): "))
    for i in range(1, 5):
        visa_write(oscilloscope, f':BLANK CHANnel{i}')
    frequencies = []
    counts = []
    triggerValues = []
    visa_write(oscilloscope, ':TRIGger:SWEep AUTO')
    indexChn = 0
    for i in channelInp :
        visa_write(oscilloscope, f':VIEW CHANnel{i}')
        visa_write(oscilloscope, f':TRIGger:SOURce CHANnel{i}')
        f, c, triggerValue = auto_trigger(oscilloscope, i, minThreshold[indexChn], maxThreshold[indexChn], stepThreshold[indexChn], frequency, intervalTime)
        frequencies.append(f)
        counts.append(c)
        triggerValues.append(triggerValue)
        visa_write(oscilloscope, f':BLANK CHANnel{i}')
        indexChn += 1
    print(10*'-')
    for i in range(0, len(channelInp)):
        print(f'Frequency channels {channelInp[i]} is : {frequencies[i]}')
        print(f'Counts channels {channelInp[i]} is : {counts[i]}')
        print(f'Trigger values of channel {i} is {triggerValues[i]}')
elif option == '7':
    channelInp = [int(x) for x in input("Enter the channel: ").split(' ')]
    #check channel is valid
    for i in channelInp:
        if i > 4 and i < 1:
            print('Channel(s) input is invalid')
            sys.exit(1)
    threshold = []
    for i in channelInp :
        threshold.append(float(input(f"Enter the threshold for channel {i} (Volt): ")))
    intervalTime = int(input("Enter the interval time (second(s))  (it is for all channel(s)): "))
    for i in range(1, 5):
        visa_write(oscilloscope, f':BLANK CHANnel{i}')
    counts = []
    indexChn = 0
    folder_name = 'temporary'
    if not os.path.exists(folder_name):
        os.makedirs(folder_name)
    for i in channelInp :
        visa_write(oscilloscope, f':VIEW CHANnel{i}')
        visa_write(oscilloscope, f':TRIGger:SOURce CHANnel{i}')
        countSignal = 0
        #times.sleep(0.01)
        timebefore = times.time()
        isRun = 1
        count = 0
        counts = []
        while times.time() - timebefore < float(intervalTime):
            if isRun == 1:
                visa_write(oscilloscope, ':SINGle')
                isRun = 0
            #times.sleep(0.001)
            if visa_query(oscilloscope, ':TRIGger:SWEep?') == "AUTO\n":
                #print('is calculate')
                read_data = read_data_byChannel(oscilloscope, i)
                header_len = 2 + int(read_data[1:2].decode())
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
                isRun = 1
                if min(voltage) <= threshold[indexChn] :
                    countSignal += 1
                else :
                    continue

                # Save data to file
                originPath = os.path.join(os.getcwd(), folder_name + f'channel{i}_{count}.txt')
                count += 1
                # Save time and voltage to a txt file with two columns (no header)
                with open(originPath, 'w') as f:
                    for t, v in zip(voltage):
                        f.write(f"{v}\n") 
        counts.append(count)
        visa_write(oscilloscope, f':BLANK CHANnel{i}')
        print(f'Counts channel {i} is : {countSignal}')
        indexChn += 1
    
    # Read and display the saved txt files for each channel
    for i in channelInp:
        print(f"\nData for channel {i}:")
        for count in range(counts):
            print(f'Process file {count}/{len(counts)}')
            file_path = os.path.join(os.getcwd(), folder_name + f'channel{i}_{count}.txt')
            if os.path.exists(file_path):
                data = np.loadtxt(file_path)
                values = min(data)
                boundary = values * 0.9
            
                print(f"File: {file_path}")
                print(data)
            else:
                print(f"File {file_path} does not exist.")
    # Delete the folder and all files in it
    if os.path.exists(folder_name):
        shutil.rmtree(folder_name)
        print(f"Deleted folder '{folder_name}' and all its contents.")
    else:
        print(f"Folder '{folder_name}' does not exist.")
elif option == '8':
    sys.exit(1)



