# 🌎 Air & Water Quality Monitoring System

## 📌 Overview
This project monitors **air pollution** and **water quality** using sensors connected to an **ESP8266 (NodeMCU)**. The collected data is displayed on an **OLED screen** and sent to the **Blynk IoT dashboard** for remote monitoring. The system also provides **real-time alerts** based on environmental conditions.

---

## 🚀 How It Works
1️⃣ Sensors detect air and water quality parameters.  
2️⃣ Data is processed by **ESP8266** and displayed on an **OLED screen**.  
3️⃣ Readings are sent to the **Blynk IoT Dashboard** for remote monitoring.  
4️⃣ If air or water quality exceeds safe levels, the system **triggers alerts**.  

---

## 🛠 What You Need
### 🔹 **Hardware Components**
- **ESP8266 (NodeMCU)** – Microcontroller for data processing & Wi-Fi  
- **MQ-135 Sensor** – Measures air pollution (CO2, NH3, Benzene)  
- **pH Sensor** – Checks water acidity/alkalinity  
- **TDS Sensor** – Measures Total Dissolved Solids in water  
- **DHT11 Sensor** – Reads temperature & humidity  
- **OLED Display** – Shows real-time readings  
- **Relay Module** – Controls external devices (e.g., water pump, alarm)  

### 🔹 **Software Requirements**
- **Arduino IDE** (https://www.arduino.cc/en/software)  
- **Blynk IoT App** (https://blynk.io)  
- **Required Libraries:** ESP8266WiFi, Blynk, Adafruit_SSD1306, DHT, MQ135, TDS  

---

## 📂 Project Structure
📂 AirWaterMonitor/ ├── 📜 air_water_quality.ino # Main Arduino Code ├── 📜 README.md # Project Documentation ├── 📜 libraries.txt # List of required libraries ├── 📜 Blynk_Dashboard.json # Blynk App Configuration ├── 📂 hardware/ # Hardware-related files │ ├── 📜 components_list.md # List of components │ ├── 📜 pcb_design.fzz # (Optional) PCB Design ├── 📂 firmware/ # Firmware-related files │ ├── 📜 flash_instructions.txt # Firmware flashing guide

---

## ⚙️ Setting Up the Project

### 🔹 **1️⃣ Connect the Hardware**
| **Component** | **ESP8266 Pin** |
|--------------|---------------|
| MQ-135 Sensor  | A0 |
| pH Sensor  | A0 |
| TDS Sensor  | A1 |
| DHT11 Sensor  | D2 |
| OLED Display  | SDA → D3, SCL → D4 |
| Relay Module  | D5 |

### Resolving A0 Pin Conflict

Both the **MQ Gas Sensor** and **Turbidity Sensor** use the same A0 pin.  
To fix this, we use a **relay module** to switch between them.

**Steps:**
1. Connect the **relay module’s control pin** to **D6 (GPIO12)**.
2. Connect the **MQ Sensor & Turbidity Sensor** to the relay’s switching terminals.
3. The code will **toggle the relay** to read each sensor separately.


### 🔹 **2️⃣ Install Required Software**
1. **Install Arduino IDE** (https://www.arduino.cc/en/software).  
2. **Install Libraries** by adding `libraries.txt` dependencies in Arduino.  
3. **Set Up Blynk IoT Dashboard**:  
   - Create an account on **Blynk Cloud** (https://blynk.cloud).  
   - Import the provided **`Blynk_Dashboard.json`** file.  
   - Copy the **Auth Token** and replace it in `air_water_quality.ino`.  

### 🔹 **3️⃣ Upload Code to ESP8266**
1. Open **`air_water_quality.ino`** in **Arduino IDE**.  
2. Select **ESP8266 (NodeMCU)** as the board.  
3. Connect your ESP8266 via USB and **upload the code**.  

---

## 📊 Monitoring & Alerts
- **View Real-Time Data** on OLED & Blynk App.  
- **Receive Alerts** if pollution or water contamination is detected.  
- **Automate Actions** like turning on filters, fans, or alarms.  

---

## 🔧 Troubleshooting
❌ **No Wi-Fi Connection?**  
➡️ Ensure correct SSID & Password in `air_water_quality.ino`.  

❌ **No Sensor Readings?**  
➡️ Check wiring & power supply for sensors.  

❌ **Blynk Not Receiving Data?**  
➡️ Verify Blynk Auth Token & Internet connection.  

---

## 📢 Conclusion
This **IoT-based Air & Water Monitoring System** helps in detecting environmental pollution in real time. By using **ESP8266, sensors, and Blynk**, it provides a **cost-effective, automated, and remote monitoring solution**.  

---