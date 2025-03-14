import pyvisa 
import sys 
import time 

REMOTE_IP = '192.168.1.93'
PORT = 4884
def visa_connect():
    try:
        rm = pyvisa.ResourceManager('@py')
        oscilloscope = rm.open_resource(f'TCPIP0::{REMOTE_IP}::INSTR')
        oscilloscope.timeout = 100  # Set timeout to 0.1 seconds
        return oscilloscope
    except Exception as e:
        print(f'Failed to connect to oscilloscope: {e}')
        sys.exit(1)
visa_connect()


