
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
# pip install matplotlib


REMOTE_IP = "192.168.1.160"
PORT = 5025

def visa_connect():
    try:
        rm = pyvisa.ResourceManager('@py')
        oscilloscope = rm.open_resource(f'TCPIP0::{REMOTE_IP}::INSTR')
        oscilloscope.timeout = 100  # Set timeout to 0.1 seconds
        return oscilloscope
    except Exception as e:
        print(f'Failed to connect to oscilloscope: {e}')
        sys.exit(1)

def visa_query(oscilloscope, cmd):
    try:
        response = oscilloscope.query(cmd)
        return response.strip()
    except Exception as e:
        print(f'Query failed: {e}')
        return None

def visa_write(oscilloscope, cmd):
    try:
        oscilloscope.write(cmd)
        time.sleep(0.1)
    except Exception as e:
        print(f'Failed to send the command: {e}')
        sys.exit(1)

def save_to_excel(all_channel_data, index):
    filename = f'channel_data_{index}.xlsx'
    data_dict = {"Time (s)": all_channel_data[0][0]}
    for ch in range(len(all_channel_data)):
        data_dict[f"Channel {ch+1} (V)"] = all_channel_data[ch][1]
    df = pd.DataFrame(data_dict)
    df.to_excel(filename, index=False)
    print(f"Data saved to {filename}")

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
        inr_response_1 = visa_query(oscilloscope, 'INR?')
        time.sleep(0.1)  # Slight delay before next query
        print("inr_response_1", inr_response_1)
        if inr_response_1 == '8193':
            break
        time.sleep(0.5)  # Wait before querying again

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

    # fig, axes = plt.subplots(4, 1, figsize=(10, 10))
    # for ch in range(4):
    #     time_values, volt_values = channel_data[ch]
    #     axes[ch].plot(time_values, volt_values, label=f"Channel {ch+1}")
    #     axes[ch].set_title(f"Channel {ch+1}")
    #     axes[ch].set_xlabel("Time (s)")
    #     axes[ch].set_ylabel("Voltage (V)")
    #     axes[ch].legend()
    #     axes[ch].grid()

    # plt.tight_layout()
    # plt.show()

    oscilloscope.close()

if __name__ == '__main__':
    try:
        for i in range(10):
            main(i+1)
    except KeyboardInterrupt:
        print("\nProgram terminated by user.")
        sys.exit(0)
