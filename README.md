# Automatic-Gas-Booking-System-using-ESP8266

🔥 Automatic Gas Booking System using ESP8266
📌 Project Overview

The Automatic Gas Booking System is an IoT-based solution designed to automatically monitor LPG cylinder levels and detect gas leakage. When the gas level drops below a predefined threshold, the system automatically sends a booking alert through Telegram. In case of gas leakage, a buzzer alarm is triggered to ensure user safety.

This system reduces manual monitoring, prevents gas-related accidents, and ensures uninterrupted gas supply.

🎯 Key Features

📊 Real-time gas weight monitoring using Force Sensor

🛢️ Automatic LPG refill booking alert

🚨 Gas leakage detection using Gas Sensor

🔔 Audible alert using Buzzer

📩 Instant notification via Telegram Bot

🌐 WiFi-enabled control using ESP8266

⚡ Stable operation with regulated Power Supply

🛠️ Components Used

ESP8266 (NodeMCU)

Force Sensor (Load / Pressure Sensor)

Gas Sensor (MQ series)

Buzzer

Power Supply Module

Resistors & Connecting Wires

WiFi Network

Telegram Bot API

⚙️ Working Principle

The force sensor continuously measures the weight of the LPG cylinder.

When the gas level drops below a preset threshold, the ESP8266 triggers an automatic booking alert.

A Telegram message is sent to the registered user indicating low gas level.

The gas sensor monitors LPG leakage in real time.

If leakage is detected:

The buzzer is activated

A warning message is sent via Telegram

The entire system operates wirelessly using the ESP8266’s WiFi capability.

🔁 System Flow
Force Sensor → ESP8266 → Gas Level Check
                    ↓
           Telegram Notification

Gas Sensor → ESP8266 → Leak Detection
                    ↓
              Buzzer Alert

🌍 Applications

Smart homes

Residential LPG monitoring

Industrial gas safety systems

Automatic gas refill systems

IoT-based safety solutions

🚀 Advantages

Prevents gas shortage

Enhances safety with early leak detection

Fully automated booking alert

Low power and cost-effective solution

Real-time remote monitoring

📌 Future Enhancements

Mobile app integration

Cloud-based data logging

SMS alert backup

Multiple cylinder monitoring

Valve auto shut-off system

📂 Repository Contents

ESP8266 source code

Circuit diagram

Telegram bot configuration guide

Project documentation
