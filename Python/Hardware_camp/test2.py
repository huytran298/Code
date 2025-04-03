import pandas as pd 
import matplotlib.pyplot as plot 

# It's should be your full path 
fileCsv = '/home/huyhuy/Documents/Code-1/Python/Hardware_camp/SDS00001.csv'
dataCsv = pd.read_csv(fileCsv)

# Get the time for the X-labels 
time = []
# I use Channels 1 to 4 (exepct 3) so i created the 2d array that include data of 3 channel
ch = [[], [], [], []]
# Because the data too small (the x in 10^x is negative) so i had multiple all the data for "beutiful" data.
factor = 1000
# Get all the element data from time column
for data in range(1, len(dataCsv["Source"])):
    time.append(float(dataCsv["Source"][data]) * factor)

# First for loop to go to each channel to get the data
for channels in range(0, 4): 
    # Because the second row of the csv will be describe the data so i will get data from the third row
    # (because the second row is the first data of column so it due to that the third row is the 2nd element in array it's the dataCsv[1] (the array start from 0)) 
    for data in range(1, len(dataCsv["CH" + str(channels + 1)])):
        #Because in each channel from my data that had each scale so i had to scale it again from the code (the data you get not scale like it show on the display but you can try not to scale if it fit)
        if channels == 3:
            ch[channels].append(float(dataCsv["CH" + str(channels + 1)][data]) * 0.005 * factor)
        elif channels == 1 :
            ch[channels].append(float(dataCsv["CH" + str(channels + 1)][data]) * 0.1 * factor)
        elif channels == 2:
            continue # Just remove the channel i don't want to plot
        else :
            ch[channels].append(float(dataCsv["CH" + str(channels + 1)][data]) * factor)

# Setting of the color for each data 
# (i set right the same of my oscilloscope, you can set it right to your data or anything you want)

colors = ['y', 'm', 'c', 'g']
for channels in range(0, 4):
    if channels == 2: 
        continue
    plot.plot(time, ch[channels], color = colors[channels], label = "Channel " + str(channels + 1))

# Set the name for the label and title  
plot.xlabel('uS')
plot.ylabel('V')
plot.title('Channel data')

# Show legend
plot.legend()
# Show the grid
plot.grid()

#Just plot it =))
plot.show()

