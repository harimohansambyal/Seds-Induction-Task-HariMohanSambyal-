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

Vessel Navigation & Hazard Control System
Arduino C++ embedded navigation simulation that monitors environmental hazards (Storms, Charybdis) with automated alarm timers and a manual safety system (Anchor dropped).

## Hardware and Wiring 

| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **16x2 LCD Display** | RS:12, EN:11, D4:5, D5:4, D6:3, D7:2 | UI Status Display |
| **LDR Photoresistor** | Analog A1 | Storm Detection Threshold (< 550) |
| **Storm Warning LED** | Analog A0 | Flashing Visual Alert |
| **Ultrasonic Ping Sensor** | Digital 6 | Proximity Detection (< 100 cm) |
| **Charybdis Buzzer** | Digital 7 | Dual-Frequency Siren (1000Hz / 500Hz) |
| **Anchor Pushbutton** | Analog A2 | State-Toggle Safety Override |

## System State Logic

* **OPEN SEA (Default):** Baseline operational state.
* **ANCHOR DROPPED:** Triggered via button toggle. Overrides all active hazards, resets timers, and locks vessel in safe mode.
* **!STORM! Hazard:** Low ambient light detection. LED flashes; initiates 5-second countdown to **SHIP WRECKED**.
* **!CHARYBDIS! Hazard:** Proximity obstacle detection. Buzzer siren sounds; initiates 5-second countdown to **SHIP WRECKED**.
* **SHIP WRECKED:** Critical lockout state reached if hazard timer expires.

## Getting Started

1. Wire your hardware according to the pinout table above.
2. Open `vessel_system.ino` in the Arduino IDE.
3. Select your microcontroller board and upload the code.




