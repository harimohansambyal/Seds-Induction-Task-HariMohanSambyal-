import pandas as pd
import time
import csv


#Writes the bulk data from provided file to a new csv file in intervals of 1 second
#simulating data from a real sensor

with open('./Data/depthdata.csv','r') as depthdata:
    read_depth_data=csv.reader(depthdata)
    with open('./Data/activedepthdata.csv','w') as activedepthdata:
        write_depth_data=csv.writer(activedepthdata,delimiter=',')

        for line in read_depth_data:
            write_depth_data.writerow(line)
            activedepthdata.flush()  # Forces immediate write to disk every second
            time.sleep(1)

# cannot write the plotting program here because python executes line by line so it will first
# write the entire csv then move to plotting which defeats the whole purpose





