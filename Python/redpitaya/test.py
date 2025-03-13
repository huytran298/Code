import sys
import redpitaya_scpi as scpi

import numpy
import matplotlib.pyplot as plot
import time

IP = 'rp-f0cc52.local'

rp = scpi.scpi(IP)

while 1:
    rp.tx_txt('LED:HB?')
    buff_string = rp.rx_txt()
    print(buff_string)