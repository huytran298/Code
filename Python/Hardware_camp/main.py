#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pyvisa
import sys
import time
import pandas as pd
import matplotlib.pyplot as plt

# install library:
# python get-pip.py
# pip install pyvisa 
# pip install pyvisa pyvisa-py
# pip install pandas
# pip install openpyxl
# pip install matplotlib

def main(index):
    oscilloscope = visa_connect()

    idn = visa_query(oscilloscope, '*IDN?')
    if idn:
        print(idn)
    else:
        print("Failed to retrieve instrument ID. Aborting.")
        sys.exit(1)

    visa_write(oscilloscope, 'chdr off')

    channel_data = []

    vdiv = []
    ofst = []

    tdiv = visa_query(oscilloscope, 'tdiv?')
    if tdiv:
        print(f"Tdiv = {tdiv}")
    else:
        print("Failed to retrieve Tdiv value. Aborting.")
        sys.exit(1)

    sara = visa_query(oscilloscope, 'sara?')
    if sara:
        print(f"Sara = {sara}")
    else:
        print("Failed to retrieve Sara value. Aborting.")
        sys.exit(1)
    sara = float(sara) if sara else 1.0

    for ch in range(1, 5):
        vdiv_value = visa_query(oscilloscope, f'c{ch}:vdiv?')
        vdiv.append(float(vdiv_value) if vdiv_value else 1.0)
        print(f"Channel {ch}: Vdiv = {vdiv[-1]}")

        ofst_value = visa_query(oscilloscope, f'c{ch}:ofst?')
        ofst.append(float(ofst_value) if ofst_value else 0.0)
        print(f"Channel {ch}: Ofst = {ofst[-1]}")

    # visa_write(oscilloscope, 'TRIG_MODE SINGLE')
    visa_write(oscilloscope, 'ARM')
    start_time = time.time()

    # check status
    retries = 0
    while True:
        status = visa_query(oscilloscope, 'SAST?')
        time.sleep(0.1)  # Slight delay before next query
        print("status", status)
        if status == 'Stop':
            break
            
        time.sleep(0.1)  # Wait before querying again

        retries += 1
        if retries > 60:  # Retry 30 times before giving up
            print(f"Failed to get expected INR responses after {retries} retries.")
            sys.exit(1)

    # save data
    for ch in range(1, 5):
        try:
            oscilloscope.write(f'c{ch}:wf? dat2')
            time.sleep(0.1)
            
            header = oscilloscope.read_bytes(7)
            datalen_str = oscilloscope.read_bytes(9).decode()

            try:
                datalen = int(datalen_str)
            except ValueError:
                print(f"Error parsing data length for channel {ch}: {datalen_str}")
                continue

            data = oscilloscope.read_bytes(datalen + 2)
            
            volt_values = []
            for t in data:
                if t > 127:
                    t -= 256
                volt_values.append(float(t) / 25 * vdiv[ch-1] - ofst[ch-1])

            if ch == 1:
                time_values = [-(float(tdiv) * 14 / 2) + idx * (1 / sara) for idx in range(len(volt_values))]

            channel_data.append((time_values, volt_values))
        except Exception as e:
            print(f'Failed to retrieve data from channel {ch}: {e}')
            continue

    end_time = time.time()
    total_time = end_time - start_time
    print(f"Total data transfer time: {total_time:.2f} seconds")

    save_to_excel(channel_data, index)

    # Draw data

    fig, axes = plt.subplots(4, 1, figsize=(10, 10))

    for ch in range(4):
        time_values, volt_values = channel_data[ch]
        axes[ch].plot(time_values, volt_values, label=f"Channel {ch + 1}")
        axes[ch].set_title(f"Channel {ch + 1}")
        axes[ch].set_xlabel("Time (s)")
        axes[ch].set_ylabel("Voltage (V)")
        axes[ch].legend()
        axes[ch].grid()

    plt.tight_layout()
    plt.show()

    oscilloscope.close()

if __name__ == '__main__':
    try:
        for i in range(10):
            main(i+1)
    except KeyboardInterrupt:
        print("\nProgram terminated by user.")
        sys.exit(0)