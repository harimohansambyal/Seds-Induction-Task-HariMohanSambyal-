# Seds-Induction-Task-HariMohanSambyal-
This repository contains my solutions for induction tasks 1 and 2

## Task 1 : Finding the sea floor

- libraries used > matplotlib, pandas

- In python created a function with the following 3 parts :
  
  > Part 1: Data Parsing
   - read csv file using pandas
   - "pd.to_numeric(errors='coerce')" to parse out invalid  strings (like `#VALUE!`) into `NaN`, followed by '.ffill().bfill()` to reconstruct continuous values.
   - fixes missing values, non numerical values before sending data to statistical filter
   
  
  > Part 2: Outlier Detection & LWMA Noise Filtering
  - Used a Mean Absolute Deviation window check made with For loops and If else statements to catch sensor spikes and extreme
  outlier values, replacing outliers with a linearly weighted moving average of last 15 data entries to reduce noise.

  
  > Part 3: plotting
  - Using pyplot, plot the line graph and format its style, adds title, labels, legends etc

  
  > Real-Time Data Animation
  - Executed this function with  Matplotlib's `FuncAnimation` to plot a live line graph updating every second.

  
  > For Testing Live Plotting Capability from CSV file > created a live_csv_generator using built-in CSV module, which reads
  given depth data file, and writes it to a new csv file in intervals of 1 seconds, mimicking the inputs given by a sensor
  for testing the live data plotting code.

  
  > Resultant graph contains significantly less noise than raw data plot and doesn't contain missing/erroneous or outlier
  values

## Task 2 : Keeping Watch Over Odysseus




