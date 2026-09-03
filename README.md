                                     🚗**CAN-BASED VEHICLE SAFETY & MONITORING SYSTEM**



📌 **Project Overview**



The **CAN-Based Vehicle Safety & Monitoring System** is an automotive embedded system designed using the Controller Area Network (CAN) protocol.

The system uses multiple LPC2129-based nodes to monitor vehicle parameters and provide safety-related alerts.

The main node monitors the engine temperature, controls vehicle indicators, and processes reverse sensor information. Communication between the nodes is performed using the CAN protocol.

**🎯 Aim**



To design and develop an automotive safety and monitoring system using the CAN protocol, where a central/main node monitors engine temperature, controls vehicle indicators, and processes reverse sensor data to provide real-time safety alerts through coordinated communication with multiple nodes.

**✨ Features**



1.Engine temperature monitoring


2.Vehicle indicator control


3.Reverse obstacle detection


4.CAN-based communication between multiple nodes


5.LCD-based information display


6.External interrupt-based indicator control


7.Forward and reverse operating modes


8.Reverse safety alert using ultrasonic sensor


9.LED/buzzer-based safety indication

**🔧 Hardware Requirements**



1.LPC2129 Microcontroller


2.CAN Transceiver – MCP2551


3.LEDs


4.LCD


5.HC-SR05 Ultrasonic Sensor


6.Switches


7.DS18B20 Temperature Sensor


8.USB-to-UART Converter

**💻 Software Requirements**



Embedded C, Keil C Compiler, Flash Magic.

**📡 CAN Communication**



CAN is used for communication between the Main Node, Indicator Node, and Reverse Alert Node.
         CAN BUS
            │
   ┌────────┼────────┐
  
   
   │        |        |
   
   
   
   
   ▼        ▼        ▼














Main Node Indicator Reverse Node Alert Node

The Main Node communicates indicator commands to the Indicator Node.

The Reverse Alert Node sends obstacle detection information to the Main Node.

**CAN ID's for Nodes**



**MAIN_ID 0x100**



**IND_ID 0x200**



**MODE_ID(Reverse) 0x300**

**🧩 Block Diagram**



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


   
**🏗️ System Architecture**



The project consists of three major nodes:

**1. Main Node**


The Main Node acts as the central controller.



**Functions:**


1.Reads engine temperature using the DS18B20 temperature sensor


2.Displays temperature on LCD


3.Detects external switch interrupts


4.Sends indicator control commands through CAN


5.Selects forward/reverse operating mode


6.Receives reverse-alert information through CAN


7.Activates an alert using LED/buzzer when required

**2. Indicator Node**


The Indicator Node continuously waits for CAN data from the Main Node.



**Functions:**



1.Receives indicator control information through CAN


2.Processes the received CAN data


3.Controls left/right indicator LEDs according to the received command



**3. Reverse Alert Node**



The Reverse Alert Node continuously monitors the distance using the HC-SR05 ultrasonic sensor.



**Functions:**



1.Measures distance from an obstacle



2.Compares the measured distance with a predefined limit



3.Sends Logic 1 to the Main Node when the distance is below the limit


4.Sends Logic 0 when the distance is above the limit



**🔄 Working Principle**

**Forward Mode**



Initially, the vehicle operates in Forward Mode.

The Main Node:


1.Reads engine temperature.


2.Displays the temperature on LCD.


3.Monitors external switches.


4.Generates an interrupt when an indicator switch is pressed.


5.Sends the appropriate indicator command through CAN.


6.The Indicator Node receives the CAN message.


7.The corresponding indicator LED is activated.


**Reverse Mode**



When the mode switch is pressed, the system changes from Forward Mode to Reverse Mode.


1.The Reverse Alert Node continuously reads the HC-SR05 ultrasonic sensor.


2.If an obstacle is detected within the configured limit:
HC-SR05 Distance > Limit ↓ Logic 0 ↓ CAN Message ↓ Main Node ↓ Safety Alert OFF

**System Flow**
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
  Indicator Node            │
         │                  ▼
         ▼              Main Node
LED Indicator               │
                            ▼
                       Safety Alert

**Applications**



This system can be used as a prototype for:

1.Automotive safety systems

2.Vehicle indicator control

3.Reverse parking assistance

4.Engine temperature monitoring

5.CAN-based automotive networks

6.Vehicle monitoring systems

**📌 Future Enhancements**



Possible future improvements include:

1.Add vehicle speed monitoring

2.Add battery voltage monitoring

3.Add GPS-based vehicle tracking

4.Add GSM/IoT connectivity

5.Store sensor data for analysis

5.Add CAN error monitoring

6.Add more automotive sensor nodes

7.Add real-time data logging













