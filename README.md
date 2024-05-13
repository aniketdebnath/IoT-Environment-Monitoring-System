# IoT Environmental Monitoring System

This repository hosts the code and documentation for an IoT-based environmental monitoring system designed to track and control indoor climate conditions via a web interface. This system utilizes an Arduino to collect temperature, humidity, and light data, which it sends to a Raspberry Pi for processing, display, and alert management through a Flask-based web application.

## Features

- **Sensor Data Collection**: Continuous monitoring of temperature, humidity, and light.
- **Actuator Control**: Uses LEDs and buzzers for visual and auditory alerts.
- **Web Interface**: Flask application for real-time data display and threshold management.
- **Real-Time Alerts**: Immediate updates and alerts based on user-defined thresholds.
- **Serial Communication**: Arduino communicates sensor readings to the Flask application via serial communication.

## Components

### Hardware

1. **Duinotech DHT11 Temperature and Humidity Sensor Shield (CAT.NO: XC-3856)**
   - **Purpose**: Monitors temperature and humidity to maintain comfortable indoor environments.
   - **Integration**: Mounted directly on the Arduino, sends data to the Raspberry Pi via serial communication.

2. **Duinotech Arduino Compatible Photosensitive LDR Sensor Module (CAT.NO: XC4446)**
   - **Purpose**: Automates lighting systems by measuring ambient light intensity.
   - **Integration**: Connected to an analog pin on the Arduino, data is processed and sent to the Raspberry Pi.

### Actuators

1. **LEDs (Red, Green, Yellow)**
   - **Purpose**: Provide visual feedback based on sensor readings.
   - **Integration**: Controlled via digital output pins on the Arduino, can be remotely managed through the web interface.

2. **Buzzer**
   - **Purpose**: Serves as an auditory alert system for critical environmental thresholds.
   - **Integration**: Operates through a digital pin, controlled by Arduino and Raspberry Pi logic.

### Software/Libraries

- **Arduino Sketch**: Utilizes libraries like `DHT.h` for the DHT11 sensor to manage data collection efficiently.
- **Raspberry Pi**: Runs a Flask application within Oracle VM VirtualBox for data handling and user interaction.
- **Database Management**: Uses PyMySQL to interact with a MySQL database for storing sensor readings.
- **Real-Time Web Updates**: AJAX calls within the Flask app fetch and update sensor data without page reloads.

## System Architecture

1. **Data Collection and Transmission**: Arduino collects sensor data, formats it, and transmits it to Raspberry Pi.
2. **Data Reception and Processing**: Raspberry Pi receives data via serial communication, processes it, and updates the MySQL database.
3. **User Interaction and Data Display**: Flask serves web pages that allow users to view data and manage settings.
4. **Alerts and Actuator Control**: Based on set thresholds, the system activates LEDs or buzzers to alert users.

## Setup and Installation

### Requirements

- Arduino IDE
- Python 3
- Flask
- PyMySQL
- MySQL Server
- Oracle VM Virtual Box
- Debian (64-bit)

### Configuration

1. **Arduino Setup**: Flash the Arduino with the provided sketch.
2. **Database Setup**: Initialize the MySQL database with the required schema.
3. **Server Setup**: Deploy the Flask app on Raspberry Pi, configure it to start on boot.

## Usage

1. Start the MySQL service and ensure the database and tables are set up as required.
2. Run the Flask application:
```
python app.py
```
2. Access the web interface at http://localhost:8080 to view and manage sensor data and actuator states.
3. Monitor alerts and control actuators through the dashboard.

## Web Interface

- Home Page: Displays the latest sensor readings and controls for updating actuation thresholds.
- Data Analysis: Provides statistical analysis of historical sensor data.
- Live Data Fetch: An AJAX-based feature to fetch the latest data without refreshing the page.

## Contributing

Contributions to the project are welcome! Feel free to fork the repository, make improvements or suggest new features by submitting a pull request or opening an issue.
