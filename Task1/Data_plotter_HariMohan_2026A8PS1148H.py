import pandas as pd
import csv
import matplotlib as mpl
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation

#creating a function to continuously read the the live csv file, clean errors, filter out noise and plot it 
def clean_n_plot(frameindex):
    read_depth_data = pd.read_csv('./Data/activedepthdata.csv')
    seconds_elapsed = read_depth_data['Point']
    raw_depth = read_depth_data['Depth (m)']

    # Filter1 
    #converts all entries in Depth column to numeric values
    #values that retuen errors are converted to nan
    #all nan value are filled forward, if no preceding value then filled backwards
    
    raw_depth = pd.to_numeric(raw_depth, errors='coerce')
    clean_depth = raw_depth.ffill().bfill()

    # Filter 2 : Noise Filter, linear weighted moving average
    # first two index values are appended to smooth_data list as is, because they return divide by 0 error in filter logic
    # from index 2 onwards, mean deviation about mean for last 15 (or less if index < 15) is calculated
    # we set an upper limt and a lower limit using this, if datapoint corresponding to given index lies
    # between these limits it is appended to the smooth_data list else it is considered an extreme outlier value
    # instead of the outlier value we append the Linearly Weighted Moving Average (LWMA) of preceding 15 values to the smooth_data list
    # this is a statistical estimate of what the original value might have been
    # this entire filter is placed in a for loop so it run from index 0 to the final index value of the csv file which is updating live 
    # all noise filtered values are appended to smooth_depth list which is plotted on y axis of plot

    smooth_depth = []
    x = 0
    for noisydata in clean_depth:
        if x < 2:
            smooth_depth.append(noisydata)
        else:
            last15 = clean_depth.iloc[:x].tail(15)
            m = sum(last15)/len(last15)
            meandevmean = sum(abs(k-m) for k in last15) / len(last15)
            threshold = max(meandevmean, 1)
            a = m + threshold
            b = m - threshold

            if b < noisydata < a:
                smooth_depth.append(noisydata)

            else:
                weighted_list = []
                total_weight = 0
                weight = 1
                for data in last15:
                    weighted_list.append(data*weight)
                    total_weight += weight
                    weight += 1
                if total_weight > 0:
                    smooth_value = sum(weighted_list)/total_weight
                else:
                    smooth_value = data
                smooth_depth.append(smooth_value)
        x += 1


    # In above part we read the csv file data and passed it through 2 filters to reduce noise and error values
    # now we plot our final filtered data from variables seconds_elapsed and smooth_depth
    # further customise the graph with title x label, y label, colour filletc
    plt.cla()
    plt.plot(seconds_elapsed, smooth_depth)
    plt.fill_between(seconds_elapsed, smooth_depth, alpha=0.1)
    plt.title('Filtered Sensor Data: Sea Floor Depth vs. Time')
    plt.xlabel('Time Elapsed (seconds)')
    plt.ylabel('Depth (from sea level')
    zero=0
    plt.fill_between(seconds_elapsed, smooth_depth, zero,color='#2750F5',alpha=0.25)
   
    plt.tight_layout()   


#finally we use FuncAnim to get the plot to update live in intervals of 1 second (1000ms)

plot=FuncAnimation(plt.gcf(), clean_n_plot ,interval=1000)
plt.show()
