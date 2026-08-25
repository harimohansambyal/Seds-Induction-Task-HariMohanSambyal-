# Seds-Induction-Task-HariMohanSambyal-
This repository contains my solutions for induction tasks 1 and 2

## Task 1 : Finding the sea floor

- libraries used > matplotlib, pandas

- In python created a function with the following structure :
  
  > Part 1: Data Parsing
  read csv file using pandas
  "pd.to_numeric(errors='coerce')" to parse out invalid  strings (like `#VALUE!`) into `NaN`, followed by
  '.ffill().bfill()` to reconstruct continuous values.
  fixes missing values, non numerical values before sending data to statistical filter
  
  > Part 2: Outlier Detection & LWMA Noise Filtering
  Used a Mean Absolute Deviation window check made with For loops and If else statements to catch sensor spikes and extreme
  outlier values, replacing outliers with a linearly weighted moving average of last 15 data entries to reduce noise.
  
  > Part 3: Real-Time Data Animation
  Rendered the depth data using Matplotlib's `FuncAnimation`.
  
  > For Testing Live Plotting Capability from CSV file > created a live_csv_generator using built CSV module, which reads
  given depth data file, and writes it to a new csv file in intervals of 1 seconds, mimicing the inputs given by a sensor
  for testing the live data plotting code.



