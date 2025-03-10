import sys
import redpitaya_scpi as scpi
import numpy
import matplotlib.pyplot as plot
import time

IP = 'rp-f0cc52.local'

rp = scpi.scpi(IP)

rp.tx_txt('ACQ:RST')

rp.tx_txt('ACQ:DEC 4')
rp.tx_txt('ACQ:START')
rp.tx_txt('ACQ:TRig NOW')

while 1:
    rp.tx_txt('ACQ:TRig:STAT?')
    if rp.rx_txt() == 'TD':
        break

## ! OS 2.00 or higher only ! ##
while 1:
    rp.tx_txt('ACQ:TRig:FILL?')
    if rp.rx_txt() == '1':
        break

while 1:
    rp.tx_txt('ACQ:SOUR1:DATA?')
    buff_string = rp.rx_txt()
    buff_string = buff_string.strip('{}\n\r').replace("  ", "").split(',')
    buff = list(map(float, buff_string))

    plot.plot(buff)
    plot.ylabel('Voltage')
    plot.show()
    sleep(50)