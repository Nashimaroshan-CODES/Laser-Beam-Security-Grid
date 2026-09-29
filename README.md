# Laser Beam Security Grid

## IoT-Based Laser Beam Security System using ESP8266, LDR and Blynk

The Laser Beam Security Grid is an IoT-based security system designed to detect unauthorized entry by monitoring laser beams using LDR sensors.

When a laser beam is interrupted, the ESP8266 detects the change through the LDR sensor and activates an alarm. The system can also send real-time alerts through the Blynk IoT platform.

## Features

- Laser beam based intrusion detection
- LDR-based beam monitoring
- ESP8266 NodeMCU controller
- Instant buzzer alarm
- LED status indication
- Blynk IoT integration
- Real-time mobile monitoring
- Two-zone security monitoring
- Alert counter
- Low-cost and scalable design

## Components Required

- ESP8266 NodeMCU
- 2 × Laser modules
- 2 × LDR sensor modules
- Buzzer
- LED
- Jumper wires
- Breadboard / PCB
- 3.3V / suitable power supply
- Wi-Fi connection
- Smartphone with Blynk IoT

## Working Principle

1. Laser modules continuously transmit laser beams toward the LDR sensors.
2. The LDR sensors monitor the laser light.
3. When a beam is interrupted, the sensor output changes.
4. The ESP8266 detects the interruption.
5. The buzzer is activated to indicate an intrusion.
6. The LED changes its status to indicate the alarm condition.
7. The Blynk IoT platform displays the security status.
8. A Blynk notification can be generated when an intrusion is detected.

## Pin Connections

| Component | ESP8266 Pin |
|---|---|
| Laser 1 | D1 |
| Laser 2 | D2 |
| LDR 1 DO | D5 |
| LDR 2 DO | D6 |
| Buzzer | D7 |

### LDR Power

- LDR VCC → 3.3V
- LDR GND → GND

### Buzzer

- Buzzer + → D7
- Buzzer - → GND

## Blynk Virtual Pins

| Virtual Pin | Purpose |
|---|---|
| V0 | Overall security status |
| V1 | Zone 1 status |
| V2 | Zone 2 status |
| V3 | Alert count |

## Software

- Arduino IDE
- ESP8266 Board Package
- Blynk IoT
- Embedded C / Arduino C++
- Wi-Fi

## Project Structure

```text
Laser-Beam-Security-Grid/
│
├── laser-beam-security-grid.ino
├── laser-beam-security-grid-diagram.png
└── README.md
