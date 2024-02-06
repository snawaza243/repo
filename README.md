# Smart Parking System Project

## Overview

This project implements a Smart Parking System using ESP32 microcontroller, integrating various sensors and actuators to monitor and manage parking spaces effectively.

I led the development of an IoT-based Smart Parking System aimed at efficiently managing parking spaces and enhancing user experience. This system utilized advanced sensor technologies and microcontrollers to automate parking space monitoring and facilitate real-time updates for users.

## Key Features:

- **Parking Slot Management:** Implemented a system to monitor and manage available parking slots in real-time. Integrated proximity sensors to detect incoming and outgoing vehicles.
  
- **LED Display Integration:** Integrated LED displays at the entry point of the parking lot to provide clear indications of available parking spaces. The display dynamically updated to reflect the current status of the parking lot, indicating the number of available slots or displaying a "Slot Full" message when all slots were occupied.

- **LCD Feedback:** Employed Liquid Crystal Displays (LCDs) to provide additional feedback within the parking area. The LCD displayed the current count of available parking slots, offering instant information to users.

- **Light Sensing:** Integrated Light Dependent Resistors (LDRs) to detect ambient light conditions. When the light level dropped below a specified threshold, indicating dim lighting conditions, an LED was automatically illuminated to enhance visibility within the parking area.

- **Servo Control:** Utilized servo motors to control the barrier gate, allowing for automated opening and closing based on vehicle presence and slot availability.


## Components Used

- ESP32 microcontroller
- Camera module
- Proximity sensor
- Servo motor
- LDR (Light Dependent Resistor)
- LED (Light Emitting Diode)
- LCD (Liquid Crystal Display)
- Adafruit IO for cloud-based data retrieval

## Features

- **Parking Slot Management:** The system monitors parking slots in real-time using proximity sensors and updates the availability status on an LCD display.
  
- **Barrier Control:** A servo motor controls the barrier gate, allowing entry and exit of vehicles based on slot availability.

- **Light Sensing:** LDRs detect ambient light conditions, triggering LED illumination in low-light environments for enhanced visibility.

- **Cloud Integration:** Utilizing Adafruit IO, the system stores and retrieves parking data for remote monitoring and analysis.

## Implementation

- **Firmware Development:** C++ programming language is used to develop firmware for ESP32, managing sensor data acquisition, actuator control, and cloud communication.

- **Integration and Deployment:** The components are integrated and deployed in a real-world parking environment, providing an efficient solution for parking space management.

## Achievements

- Successfully deployed and tested the Smart Parking System, receiving positive feedback for its reliability and effectiveness in optimizing parking operations.

- Demonstrated proficiency in IoT development, sensor integration, and cloud-based data management through the implementation of this project.

## Future Enhancements

- Implement license plate recognition for automated entry and exit management.
- Integrate mobile application for user interaction and real-time parking updates.
- Enhance data analytics and reporting capabilities for better parking space utilization.
