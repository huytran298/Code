import pandas as pd
import matplotlib.pyplot as plt
import math
# Offset and delta values
offset = 0.0013
delta = -0.00082
deltaY = -1*10**-3 # -1.88mV + 0.2mV
# Directory path
dirPath = 'C:\\Users\\as\\Documents\\Code\\Python\\Hardware_camp\\Channel_2\\'
time = [[], [], [], [], [], [], [], [], [], []]
data = [[], [], [], [], [], [], [], [], [], []]
for i in range(1, 11):
    file_name = dirPath + f'channel_data_{i}.xlsx'
    df = pd.read_excel(file_name)
    df = df[['Time (s)', 'Channel 2 (V)']]
    
    for j in range(2, df['Channel 2 (V)'].size - 2):
        data[i - 1].append(df['Channel 2 (V)'][j] + 0.0004)
        time[i - 1].append(df['Time (s)'][j])

print(time)
# Loop through 10 files
figure, axis = plt.subplots(2, 4)
cnt = 0
tmp = 0
for i in range(1, 11):
    minV = 0
    
    V = 0
    for x in data[i - 1]:
        if x < minV:
            minV = x
        V += x
    
    #print(f'{minV >= deltaY} {minV} {deltaY}')
    if minV < deltaY:
        continue
    Gain = (-V * 2 * 10**-9)/(50*1.6*(10**-19))
    Gain = round(Gain, 2)
    #round(data[i - 1], 2)

    for j in range(len(data[i - 1])):
        data[i - 1][j] = data[i - 1][j] * 10 ** 3
        time[i - 1][j] = time[i - 1][j] * 10 ** 9
      
    axis[tmp, cnt].plot(time[i - 1], data[i - 1])
    #axis[tmp, cnt].set_title(f'Da {i}')
    axis[tmp, cnt].set_title(f'Gain {Gain / (10**6)} x 10^6')
    
    axis[tmp, cnt].grid()
    cnt += 1
    
    if cnt >= 4:
        cnt = 0
        tmp += 1
plt.show()   

