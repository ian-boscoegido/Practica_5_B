# 🚀 ESP32 Wireless Networking Project

Development of wireless communication functionalities on ESP32 using WiFi networking and Bluetooth Classic serial communication.

---

## 📖 Project Overview

This project explores different communication capabilities available on the ESP32 platform by implementing:

* A lightweight HTTP web server over WiFi
* A Bluetooth serial communication interface for mobile devices

The system demonstrates how embedded devices can exchange information wirelessly using common IoT communication protocols.

---

## 🧩 Implemented Functionalities

### 🌐 WiFi Server

* Connection to a local WiFi network in STA mode
* HTTP server running on port 80
* Dynamic webpage generation using embedded HTML
* Browser access through local IP address

### 📶 Bluetooth Communication

* Bluetooth Classic initialization
* Wireless serial communication bridge
* Bidirectional message transfer
* Mobile device pairing support

---

## 🛠️ Technologies & Libraries

| Technology            | Purpose                        |
| --------------------- | ------------------------------ |
| **ESP32**             | Main microcontroller platform  |
| **WiFi.h**            | Wireless network management    |
| **WebServer.h**       | HTTP server handling           |
| **BluetoothSerial.h** | Bluetooth serial communication |
| **Arduino IDE**       | Development environment        |

---

## 💻 Hardware Requirements

| Component       | Description                     |
| --------------- | ------------------------------- |
| **ESP32 Board** | Main processing unit            |
| **USB Cable**   | Programming and power           |
| **WiFi Router** | Local wireless connection       |
| **Smartphone**  | Bluetooth communication testing |

---

## 🌍 WiFi HTTP Server

The ESP32 connects to a predefined wireless network using SSID credentials stored in the source code.

After a successful connection:

1. The board receives a local IP address
2. An HTTP server is initialized
3. The ESP32 starts listening for browser requests

When a client accesses the assigned IP address, the ESP32 sends an HTML page directly generated from the firmware.

### Expected Output

```cpp id="lgslc0"
WiFi connected successfully
HTTP server started
IP Address: 192.168.X.X
```

### Web Features

* Embedded webpage hosting
* HTTP request processing
* Serial debugging information
* Real-time browser access

---

## 📡 Bluetooth Serial Interface

The project also implements Bluetooth Classic communication using the Serial Port Profile (SPP).

The ESP32 creates a Bluetooth device that can be paired with a smartphone using any serial terminal application.

### Bluetooth Device Name

```cpp id="jlwmr9"
ESP32test
```

### Communication Features

* Real-time wireless serial communication
* Data forwarding between Serial Monitor and smartphone
* Bidirectional message exchange
* Bluetooth pairing support

### Expected Output

```cpp id="i0cw8h"
The device started, now you can pair it with bluetooth!
```

---

## ⚙️ Upload Instructions

1. Connect the ESP32 board through USB
2. Open the project in Arduino IDE
3. Configure WiFi credentials
4. Select:

   ```cpp
   ESP32 Dev Module
   ```
5. Upload the code to the board
6. Open the Serial Monitor at:

   ```cpp
   115200 baud
   ```

---

## 📁 Repository Structure

```bash id="h3m2jf"
project/
│
├── wifi_server/
│   └── wifi_server.ino
│
├── bluetooth_serial/
│   └── bluetooth_serial.ino
│
└── README.md
```

---

## ✅ Results

The implemented system successfully demonstrates:

* Wireless network connectivity using WiFi
* Local webpage hosting from ESP32
* Bluetooth serial communication with external devices
* Stable real-time data transmission

---

## 🔮 Future Improvements

Possible upgrades for the project include:

* BLE (Bluetooth Low Energy) implementation
* ESP32 Access Point mode
* Sensor integration
* Interactive web dashboard
* REST API support

---

## 📚 Applications

This type of implementation can be used in:

* IoT systems
* Embedded monitoring devices
* Wireless sensor networks
* Remote control applications
* Smart home projects

---

*Educational project focused on embedded systems and wireless communication using ESP32.*
