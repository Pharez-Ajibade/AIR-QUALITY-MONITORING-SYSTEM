# 🛰️ AQMS – Air Quality Monitoring System

AQMS (Air Quality Monitoring System) is a compact, low-cost, and portable device built to monitor harmful gases and airborne particles. It uses an ESP32 microcontroller, a set of MQ-series gas sensors, a dust sensor, and an OLED screen to provide real-time environmental readings. The system also connects to the Blynk IoT platform for remote monitoring, threshold alerts, and calibration settings.

The entire project is enclosed in a custom 3D-printed or acrylic case and powered by rechargeable 18650 LiPo batteries. It features an intuitive on-device UI for standalone use, along with visual and audible alerts through LEDs and a buzzer.

---
## YOUTUBE VIDEO LINK @ LOIGIENCE YOUTUBE CHANNEL : https://youtu.be/rIXYV3iFZdM
## 🔧 Features

- Real-time monitoring of:
  - Smoke
  - Carbon Monoxide (CO)
  - Ammonia
  - Benzene
  - Alcohol
  - Dust/Particulate Matter
- On-device OLED UI for:
  - Sensor selection
  - Wi-Fi status
  - Alarm control
- IoT app (Blynk) integration for:
  - Live data monitoring
  - Threshold configuration
  - Historical charts
- Audible buzzer alerts when gas levels exceed thresholds
- Rechargeable 18650 battery power with charge and protection module
- Compact design on Vero board inside a custom 3D-printed or acrylic enclosure

---

## 🧰 Components Used

| Component                             | Description                                      |
|--------------------------------------|--------------------------------------------------|
| MQ2 Sensor                            | Smoke, Methane, Butane detection                |
| MQ135 Sensor                          | Ammonia, Alcohol, Benzene, CO₂ detection        |
| MQ7 Sensor                            | Carbon Monoxide detection                       |
| GP2Y1010AU0F                          | Dust sensor                                     |
| ESP32 / C3 Mini                       | Microcontroller                                 |
| ADS1115                               | Analog-to-digital converter (ADC)               |
| 1.3" OLED Display                     | User interface (I2C)                            |
| 5mm LEDs (Red, Green, Yellow)         | Status indicators                               |
| SFM-10B Active Buzzer                 | Audible alarm                                   |
| Tactile Push Buttons                  | UI navigation                                   |
| 2N2222A Transistor + 2kΩ Resistor     | Buzzer control                                  |
| MT3608 Boost Converter                | 3.7V to 5V boost                                |
| 18650 LiPo Batteries                  | Rechargeable power source                       |
| USB Type-C Port                       | Charging and data                               |
| Battery Protection Module             | Charge/discharge controller                     |
| Vero Board                            | Final soldered circuit                          |
| Jumpers, Connectors, M3 Screws        | Wiring and assembly                             |

---

## 📲 IoT Integration – Blynk App

The Blynk app allows:
- Real-time monitoring of sensor data
- Historical data graphing
- Threshold configuration for buzzer alarms
- Remote calibration of sensors

> **Note:** Free version of Blynk supports up to 5 data streams.

---
