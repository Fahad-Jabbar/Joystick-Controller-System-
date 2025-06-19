# Wireless Joystick Controller System 

A robust, low-latency wireless joystick controller system built using microcontrollers and RF communication. This project enables remote control of a mobile robot or machinery using a handheld transmitter that sends directional and command signals to a receiver unit via 433MHz RF signals.

---

## Project Objective

The goal of this project was to develop a **simple, cost-effective wireless joystick controller** for a robotic platform, such as an RC vehicle or custom-built rover. The system is designed to be modular, expandable, and responsive, making it suitable for real-world applications such as:

- Prototyping autonomous or manually operated robots
- Educational robotics projects
- Hobbyist RC vehicles
- Industrial remote control tools

---

## Features

- Modular transmitter and receiver design
- RF wireless communication using the RCSwitch protocol
- Joystick and button-based user interface
- LED feedback with Adafruit NeoPixel (on transmitter)
- Auto-fire mechanism using non-blocking `millis()`-based timing
- Customizable for any GPIO-driven actuators or motor drivers
- Simple, low-cost hardware components

---

##  Getting Started

### Hardware Requirements

#### Transmitter Unit:
- Arduino-compatible board (e.g., Nano, Pro Mini)
- 433 MHz RF Transmitter module
- Buttons (momentary switches) – for direction & actions
- Joystick module or analog potentiometer (optional)
- Adafruit NeoPixel ring/strip (optional)
- Power source (e.g., 9V battery or LiPo)

#### Receiver Unit:
- Arduino-compatible board (e.g., Pro Micro, Uno)
- 433 MHz RF Receiver module
- Motor driver (L298N, BTS7960, or relays)
- Actuators or motors
- Status LED

---

### Library Dependencies

Install these libraries from the Arduino Library Manager:

- `RCSwitch` – [https://github.com/sui77/rc-switch](https://github.com/sui77/rc-switch)
- `Adafruit_NeoPixel` – [https://github.com/adafruit/Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- `Joystick` (optional) – for PC HID joystick emulation

---

## Setup and Upload

1. Clone this repository and open the respective `.ino` files in Arduino IDE.
2. Upload `Transmitter_NEW.ino` to the transmitter Arduino board.
3. Upload `Receiver_NEW.ino` to the receiver board.
4. Wire the buttons, RF modules, motors, and LEDs as per pin definitions in the code.
5. Power up both units and test signal transmission.

---

## System Architecture

```
[Joystick + Buttons] --analog/digital--> [Arduino Transmitter] --433MHz RF--> [Arduino Receiver] --GPIO--> [Motors / LEDs / Relays]
```

- The transmitter encodes input events into numerical signals and transmits them wirelessly.
- The receiver listens continuously and maps incoming codes to directional or actuator control.

---

## Code Overview

### `Transmitter_NEW.ino`
- Reads inputs from defined digital pins (buttons) and analog pin (`A0`)
- Implements an auto-fire mechanism using `millis()` to repeatedly send signals
- Controls a NeoPixel for visual feedback
- Uses `RCSwitch.send()` to transmit codes representing specific commands

### `Receiver_NEW.ino`
- Listens for signals using `RCSwitch.available()`
- Maps received codes to specific GPIO pin outputs
- Each command activates a direction or motor action for the robot
- A pin is used to blink an LED for connection/status indication

---

## Example Use Case

- Pressing "Forward" on the transmitter sends a signal code (e.g., `101`), which the receiver interprets to activate the `Forward` pin.
- A continuous press may result in auto-fire (repeating signal) for smooth motor response.
- Adding more buttons or remapping signal codes can extend the controller’s capabilities.

---

## Customization Tips

- Add more buttons and assign unique codes for new features (lights, servos, horns, etc.)
- Integrate sensors like accelerometers or gyroscopes on the transmitter for gesture-based control
- Enhance receiver safety using signal timeout or watchdog mechanisms

---

- Developed as part of an industrial project for a client requiring a custom wireless control solution for robotic or mobile platforms

---


