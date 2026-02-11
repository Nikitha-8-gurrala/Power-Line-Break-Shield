# ⚡ Power Line Break Shield

## 📌 Project Description
Power Line Break Shield is an IoT-based safety system that detects voltage loss in power lines and immediately sends an alert notification using the Blynk platform.

## 🚀 Features
- Voltage monitoring using ESP32
- Real-time data display on Blynk app
- Instant notification when power line breaks
- LED indication
- Buzzer alert system
- Automatic WiFi reconnection

## 🛠 Components Used
- ESP32
- Voltage sensing circuit
- Buzzer
- LED
- WiFi connection
- Blynk IoT platform

## ⚙ Working Principle
1. ESP32 continuously reads voltage.
2. If voltage drops below threshold (≤ 0.1V):
   - Buzzer turns ON
   - LED blinks
   - Blynk notification is sent
3. When voltage is restored:
   - Alarm turns OFF
   - System resets notification status

## 🌍 Location Alert
Includes Google Maps link for identifying the affected power line location.

## 🔮 Future Enhancements
- GPS module integration
- SMS alerts
- Cloud dashboard monitoring
- Multiple line monitoring system
