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

  
  - For Testing Live Plotting Capability from CSV file > created a live_csv_generator using built-in CSV module, which reads
  given depth data file, and writes it to a new csv file in intervals of 1 seconds, mimicking the inputs given by a sensor
  for testing the live data plotting code.

  
  > Resultant graph contains significantly less noise than raw data plot and doesn't contain missing/erroneous or outlier
  values

## Task 2 : Keeping Watch Over Odysseus

- Code written in Arduino C++, using LiquidCrystal library.
- circuit built in TinkerCAD.
- dummy on vessel navigation system with manual safety protocol.

>Finite State Machine with 5 States:
- 1.Open Sea : default state
- 2.Storm : activated when LDR sensor drops below half (voltage from voltage divider circuit<550V),triggers blinking led.
- 3.Charybdis : activated when distance sensor detects object closer than 100cm, triggers buzzer.
- 4.Wrecked : triggered when timer reaches 5 seconds in Storm/Charybdis ; requires restart.
- 5.Anchor Dropped : stops the timer in Charybdis and Storm states and resets it to 0 when button pressed, works in open sea aswell.

## Hardware and Wiring 

| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **16x2 LCD Display** | RS:12,RW:GND, EN:11, D4:5, D5:4, D6:3, D7:2 | UI Status Display |
| **Centre Tap in LDR Photoresistor circuit** | Analog A1 | Storm Detection Threshold (< 550V) |
| **LED Anode** | Analog A0 | Gives Flashing Visual Alert in Storm|
| **Ping))) Ultrasonic Distance Sensor** | Digital 6 | Proximity threshold (< 100 cm) |
| **Buzzer** | Digital 7 | Dual-Frequency Siren (1000Hz / 500Hz) activates in Charybdis state|
| **Pushbutton** | Analog A2 | State-Toggle Safety Override |

##Code Logic
- imported relevant library(Liquid Crystal), declared relevant variables 
- defined a function to get distance input from Ping))) distance sensor
- defined a function to toggle button ON and OFF
- in void setup(), set relevant pinmode, initiated lcd screen
- in void loop() start with an if else statement, if wrecked state is detected from previous loop, sets machine to wrecked mode again and loops back to start, making it a lockout state essentially.
- else sets the state to open sea, defines variable which read and store data from the sensor. 
followed by two while loops with conditions measuring sensor data against threshold values, starts a timer, activates led or buzzer depending on state, checks for push button toggle and enters another nested while loop initiating the Anchor dropped state, which remains until push button is toggled off. 
- if timer exceeds 5 seconds set state to wrecked and exits to end of void loop() using goto, after which the initial if statements become perpetually true.

- NOTE: out of Storm and Charybdis, whichever state is entered first remains active and its timer continues until sensor data becomes greater than threshold values. during this time the other state cannot override the current ongoing state.(excluding anchor dropped)




