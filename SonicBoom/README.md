# SonicBoom Robot Control

Welcome to the **SonicBoom Robot Control** project! This repository contains the complete codebase for a robotics project designed for the ERIL competition. Our robot uses an ESP32, an H-bridge motor driver with four DC motors, and a servo motor for cube manipulation. The project is organized with a modular architecture, and it features an artistic, nature-inspired web control panel powered by Tailwind CSS and jQuery.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Setup](#software-setup)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [License](#license)

## Project Overview

The **SonicBoom Robot Control** project is built for a thrilling robotics competition where speed and agility matter. The robot is controlled via an ESP32 microcontroller that:
- Drives four DC motors using an H-bridge for movement (forward, backward, left, right, stop).
- Uses a servo motor to grip and release cubes.
- Maintains its state using a dedicated state management module.
- Hosts a web server that provides a beautiful control panel with real-time feedback.

The control panel has been styled with Tailwind CSS to evoke a warm, nature-inspired feel—think coffee hues, lush greens, and an inviting aesthetic.

## Features

- **Modular Codebase:**  
  - **MotorControl:** Handles all movement functions (forward, backward, left, right, stop).
  - **ServoControl:** Offers full control over the servo for holding and releasing cubes.
  - **StateManager:** Keeps track of the robot’s current state (IDLE, MOVING, SERVO_ACTION).

- **Artistic Web UI:**  
  - The web interface is designed with Tailwind CSS for a modern, nature-inspired look.
  - Real-time state updates using jQuery and AJAX ensure you always know what your robot is doing.

- **Ease of Use:**  
  - A simple yet elegant control panel hosted on the ESP32.
  - Friendly and clear modular design for easy modification and extension.

## Hardware Requirements

- ESP32 development board
- H-bridge motor driver
- 4 DC motors
- Servo motor (compatible with ESP32 using the ESP32Servo library)
- Breadboard, wires, and an appropriate power supply

## Software Setup

1. **Install Arduino IDE:**  
   Download and install the latest version of the [Arduino IDE](https://www.arduino.cc/en/software).

2. **Install ESP32 Board Package:**  
   Follow the [ESP32 Arduino installation guide](https://github.com/espressif/arduino-esp32) to add ESP32 support in the Arduino IDE.

3. **Install Required Libraries:**  
   - Open the **Library Manager** in Arduino IDE via **Tools > Manage Libraries…**
   - Install the **ESP32Servo** library (instead of the default Servo library, which isn’t compatible with ESP32).
   - The **WiFi** and **WebServer** libraries are included with the ESP32 board package.

4. **Add Project Files:**  
   Create a new project in Arduino IDE and add the following files as separate tabs:
   - `SonicBoom.ino` (Main sketch)
   - `MotorControl.h` and `MotorControl.cpp`
   - `ServoControl.h` and `ServoControl.cpp`
   - `StateManager.h` and `StateManager.cpp`
   
   Copy the corresponding code into each file.

5. **Update WiFi Credentials:**  
   In `SonicBoom.ino`, update the `ssid` and `password` variables with your network details.

## Usage

1. **Compile and Upload:**  
   - Connect your ESP32 to your computer.
   - Select the appropriate board and port in **Tools**.
   - Click the **Verify** button to compile, and then **Upload** to flash your ESP32.

2. **Monitor Serial Output:**  
   Open the Serial Monitor (baud rate: 115200) to track WiFi connection progress and get your ESP32’s IP address.

3. **Access the Web UI:**  
   On any device connected to the same network (laptop, tablet, or phone), open a web browser and navigate to the ESP32’s IP address.
   - The control panel will display an artistic interface with buttons to move forward, backward, left, right, stop, hold cube, and release cube.
   - The robot’s current state is updated in real-time.

4. **Control Your Robot:**  
   Use the buttons to control the robot’s movements and cube manipulation. Experiment with the interface, tweak the design, and enjoy the process!

## Project Structure
SonicBoom/ ├── MotorControl.h ├── MotorControl.cpp ├── ServoControl.h ├── ServoControl.cpp ├── StateManager.h ├── StateManager.cpp └── SonicBoom.ino


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Thank you for checking out the SonicBoom Robot Control project! We hope you find it fun and inspiring. If you have any suggestions or run into issues, feel free to open an issue or submit a pull request. Happy coding, and may your robots move swiftly!

## Authors <img src="https://cdn-icons-png.flaticon.com/128/2463/2463510.png" width=50 align=center>

* AlMonther Abdulhafeez <a href="https://github.com/AlMonther9" a>
