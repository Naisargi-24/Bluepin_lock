# BluePin Lock 🔒

An embedded C++ security system utilizing Bluetooth and a physical matrix keypad for dual-factor authentication, built with a strictly modular, object-oriented architecture.

## 📌 Project Overview
The BluePin Lock is a smart hardware prototype designed to secure physical spaces. It requires users to authenticate via a 4-digit PIN, which can be entered locally through a 4x4 membrane keypad or remotely via a custom Bluetooth serial connection. 

Unlike standard monolithic Arduino scripts, this project is engineered using **Separation of Concerns (SoC)**. The firmware is split into dedicated C++ classes handling non-volatile memory (EEPROM), hardware abstractions (Solenoids/LEDs), and UI rendering (LCD), making the system highly scalable and maintainable.

## ⚙️ Core Features
* **Dual Authentication:** Unlocks via direct keypad input or wireless Bluetooth serial commands.
* **Non-Volatile Memory Management:** Utilizes the `EEPROM` library to securely store and retrieve the PIN, ensuring state persistence across power cycles.
* **Intrusion Detection & Lockout:** Tracks consecutive failed attempts. After 3 incorrect entries, the system locks out and triggers an automated protocol (with GSM SMS alert integration readiness).
* **Real-time Hardware Feedback:** Integrates a 16x2 LCD display, a piezo buzzer, and LED indicators for real-time status updates and countdown timers.
* **Dynamic Remote Configuration:** The security PIN can be dynamically updated via authenticated Bluetooth commands (e.g., `CHANGEPIN:1234`).

## 🗄️ Modular Architecture
The codebase is structured for enterprise-level readability and hardware abstraction:

* `BluePin_Lock.ino` - The main orchestrator managing the event loop and high-level logic.
* `Config.h` - Centralized configuration for all hardware pins, EEPROM addresses, and security constants.
* `Hardware.cpp / .h` - Abstraction layer for controlling the solenoid lock, buzzers, and status LEDs.
* `Storage.cpp / .h` - Manages EEPROM reads/writes and initial state setup.
* `Display.cpp / .h` - Encapsulates all LiquidCrystal rendering and UI formatting.

## 🛠️ Tech Stack & Hardware Specifications
* **Language:** C++ (Arduino Framework)
* **Core Libraries:** `Keypad.h`, `EEPROM.h`, `SoftwareSerial.h`, `LiquidCrystal.h`
* **Microcontroller:** Arduino / Compatible Board
* **Modules:** HC-05 Bluetooth, Serial GSM Module
* **Peripherals:** 4x4 Matrix Keypad, 16x2 LCD, Solenoid Lock, Piezo Buzzer, LEDs

> **⚠️ Hardware Engineering Note:** > The system logic and logic-level inputs are designed to run on a direct **3.3V Vcc connection**. Do not wire inline resistors to the main 3.3V input line, as this will drop the voltage below the required logic thresholds.

## 🚀 Setup & Installation (VS Code)

This project is optimized for development in Visual Studio Code using the Microsoft Arduino extension.

1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/YourUsername/BluePin_Lock.git](https://github.com/YourUsername/BluePin_Lock.git)
    ```
2.  **Open in VS Code:** Ensure you open the root `BluePin_Lock` folder directly.
3.  **Configure the Board:** * Open the Command Palette (`Cmd/Ctrl + Shift + P`).
    * Select `Arduino: Board Config` and choose your specific microcontroller.
4.  **Install Dependencies:** * Open the `Arduino: Library Manager` and ensure `Keypad` and `LiquidCrystal` are installed in your local environment.
5.  **Verify and Upload:** Connect your board via USB and use the Arduino extension to compile and upload the firmware.
