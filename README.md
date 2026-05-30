# ESP32 Phone Battery Sync Gauge 🔋

A DIY physical desktop gauge that displays your Android phone's real-time battery percentage using an ESP32 and a 10-segment LED bar graph. 

Unlike Bluetooth solutions, this project uses an HTTP web server on the ESP32 and background automation on Android to push updates instantly over your local Wi-Fi network.

## 🛠️ Hardware Requirements
* 1x ESP32 Development Board (NodeMCU / DevKit V1)
<img width="1600" height="1039" alt="ESP 32" src="https://github.com/user-attachments/assets/e2fe6719-c775-4af8-93cb-a69a1c029554" />

* 1x 10-Segment LED Bar Graph (or 10 discrete LEDs)
* 10x 330Ω or 220Ω Resistors
* Jumper wires and a Breadboard
* An Android Smartphone

## 🔌 Wiring Diagram
Connect the Anodes (long legs) of the LEDs to the ESP32 GPIO pins below. 

| Battery Level | ESP32 GPIO Pin |
| :--- | :---: |
| 10% | `D13` |
| 20% | `D27` |
| 30% | `D26` |
| 40% | `D25` |
| 50% | `D33` |
| 60% | `D32` |
| 70% | `D21` |
| 80% | `D22` |
| 90% | `D19` |
| 100% | `D18` |

<img width="1600" height="1584" alt="CCT" src="https://github.com/user-attachments/assets/3a95e9bf-9723-4ef1-918c-dbab213dfd76" />
&nbsp;
&nbsp;

Connect the Cathodes (short legs) through the 330Ω resistors to the ESP32 GND pin.
&nbsp;
<img width="1198" height="959" alt="GND" src="https://github.com/user-attachments/assets/928eb445-db0c-4f3f-aa7c-9c4bfdabecbb" />



## 🚀 Software Setup

### Part 1: The ESP32
1. Open the `.ino` file in the Arduino IDE.
2. Replace `Your Wifi SSID` and `Your Wifi Password` with your network credentials.
3. Upload the code to your ESP32.
4. Open the Serial Monitor (115200 baud) to get the ESP32's local IP address.

### Part 2: The Android Automation (MacroDroid)
Since Android restricts direct battery polling from external network devices, we use the free MacroDroid app to push the data to the ESP32.
1. Download **MacroDroid** from the Google Play Store.
2. Create a new Macro using Add Macro.
3. **Trigger:** `Battery/Power` -> `Battery Level` -> `Any Change` then OK.
4. **Action:** `Applications` -> `Open Website`
   * URL: `http://<YOUR_ESP32_IP>/battery?level=[battery]` then OK.
5. Save the Macro. Test actions. Your phone will now update the physical bar graph every time the battery percentage changes!
<img width="1600" height="1164" alt="30% Display" src="https://github.com/user-attachments/assets/baf4ef40-4e64-4203-9d91-15eb8bcb8222" />
<img width="1080" height="316" alt="Mobile SS" src="https://github.com/user-attachments/assets/ce53c566-7715-49b9-8fbe-38476925d00e" />![Uploading CCT.jpeg…]()

<img width="910" height="381" alt="Serial Monitor 2" src="https://github.com/user-attachments/assets/479424b8-1c6a-408f-8266-400cd2e05a96" />
