import pyvisa

def read_oscilloscope_data():
    # Initialize VISA resource manager
    rm = pyvisa.ResourceManager()

    # Connect to the oscilloscope using its IP address (replace 'TCPIP0::192.168.1.100::INSTR' with your oscilloscope's IP address)
    oscilloscope = rm.open_resource('TCPIP0::192.168.1.100::INSTR')

    # Read data from each channel
    channels_data = {}
    for channel in range(1, 5):
        oscilloscope.write(f':WAV:SOUR CHAN{channel}')
        oscilloscope.write(':WAV:MODE RAW')
        oscilloscope.write(':WAV:FORM BYTE')
        data = oscilloscope.query_binary_values(':WAV:DATA?', datatype='B')
        channels_data[f'Channel {channel}'] = data

    # Close the connection
    oscilloscope.close()

    return channels_data

if __name__ == "__main__":
    data = read_oscilloscope_data()
    for channel, values in data.items():
        print(f"{channel} data: {values[:10]}...")  # Print first 10 data points for each channel