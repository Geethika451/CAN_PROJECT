🚗CAN-Based Vehicle Safety & Monitoring System
📌 Project Overview
The CAN-Based Vehicle Safety & Monitoring System is an automotive embedded system designed using the Controller Area Network (CAN) protocol.

The system uses multiple LPC2129-based nodes to monitor vehicle parameters and provide safety-related alerts.

The main node monitors the engine temperature, controls vehicle indicators, and processes reverse sensor information. Communication between the nodes is performed using the CAN protocol.

🎯 Aim
To design and develop an automotive safety and monitoring system using the CAN protocol, where a central/main node monitors engine temperature, controls vehicle indicators, and processes reverse sensor data to provide real-time safety alerts through coordinated communication with multiple nodes.

✨ Features
Engine temperature monitoring
Vehicle indicator control
Reverse obstacle detection
CAN-based communication between multiple nodes
LCD-based information display
External interrupt-based indicator control
Forward and reverse operating modes
Reverse safety alert using ultrasonic sensor
LED/buzzer-based safety indication
🔧 Hardware Requirements
LPC2129 Microcontroller
CAN Transceiver – MCP2551
LEDs
LCD
HC-SR05 Ultrasonic Sensor
Switches
DS18B20 Temperature Sensor
USB-to-UART Converter
💻 Software Requirements
Embedded C, Keil C Compiler, Flash Magic.

📡 CAN Communication
CAN is used for communication between the Main Node, Indicator Node, and Reverse Alert Node.

         CAN BUS
            │
   ┌────────┼────────┐
   │        │        │
   ▼        ▼        ▼
Main Node Indicator Reverse Node Alert Node

The Main Node communicates indicator commands to the Indicator Node.

The Reverse Alert Node sends obstacle detection information to the Main Node.

CAN ID's for Nodes
MAIN_ID 0x100
IND_ID 0x200
MODE_ID(Reverse) 0x300
🧩 Block Diagram
                ┌──────────────────────┐
                │      MAIN NODE       │
                │       LPC2129        │
                │                      │
                │  DS18B20             │
                │  LCD                 │
                │  Switches            │
                │  Mode Control        │
                └──────────┬───────────┘
                           │
                           │ CAN
                           │
             ┌─────────────┴─────────────┐
             │                           │
             ▼                           ▼
   ┌──────────────────┐       ┌──────────────────┐
   │ INDICATOR NODE   │       │ REVERSE ALERT    │
   │     LPC2129      │       │      NODE        │
   │                  │       │     LPC2129      │
   │ CAN Receiver     │       │                  │
   │ LED Indicators   │       │ HC-SR05 Sensor   │
   └──────────────────┘       └──────────────────┘
🏗️ System Architecture
The project consists of three major nodes:

1. Main Node
The Main Node acts as the central controller.

Functions:

Reads engine temperature using the DS18B20 temperature sensor
Displays temperature on LCD
Detects external switch interrupts
Sends indicator control commands through CAN
Selects forward/reverse operating mode
Receives reverse-alert information through CAN
Activates an alert using LED/buzzer when required
2. Indicator Node
The Indicator Node continuously waits for CAN data from the Main Node.

Functions:

Receives indicator control information through CAN
Processes the received CAN data
Controls left/right indicator LEDs according to the received command
3. Reverse Alert Node
The Reverse Alert Node continuously monitors the distance using the HC-SR05 ultrasonic sensor.

Functions:

Measures distance from an obstacle
Compares the measured distance with a predefined limit
Sends Logic 1 to the Main Node when the distance is below the limit
Sends Logic 0 when the distance is above the limit
🔄 Working Principle
Forward Mode
Initially, the vehicle operates in Forward Mode.

The Main Node:

Reads engine temperature.
Displays the temperature on LCD.
Monitors external switches.
Generates an interrupt when an indicator switch is pressed.
Sends the appropriate indicator command through CAN.
The Indicator Node receives the CAN message.
The corresponding indicator LED is activated.
Reverse Mode
When the mode switch is pressed, the system changes from Forward Mode to Reverse Mode.

The Reverse Alert Node continuously reads the HC-SR05 ultrasonic sensor.

If an obstacle is detected within the configured limit:

HC-SR05 Distance > Limit ↓ Logic 0 ↓ CAN Message ↓ Main Node ↓ Safety Alert OFF

System Flow
                START
                  │
                  ▼
          Initialize LPC2129
                  │
                  ▼
          Initialize CAN/LCD
                  │
                  ▼
         Read Engine Temperature
                  │
                  ▼
             Display LCD
                  │
                  ▼
          Check Operating Mode
             /          \
            /            \
      FORWARD            REVERSE
         │                  │
         ▼                  ▼
  Check Switches       Read HC-SR05
         │                  │
         ▼                  ▼
  CAN Indicator         Compare Distance
    Command                 │
         │                  ▼
         ▼             Send CAN Data
   Indicator Node           │
         │                  ▼
         ▼              Main Node
 LED Indicator            │
                            ▼
                       Safety Alert
Applications
This system can be used as a prototype for:

Automotive safety systems
Vehicle indicator control
Reverse parking assistance
Engine temperature monitoring
CAN-based automotive networks
Vehicle monitoring systems
📌 Future Enhancements
Possible future improvements include:

Add vehicle speed monitoring
Add battery voltage monitoring
Add GPS-based vehicle tracking
Add GSM/IoT connectivity 5.Store sensor data for analysis
Add CAN error monitoring
Add more automotive sensor nodes
