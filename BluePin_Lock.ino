#include <Keypad.h>
#include <SoftwareSerial.h>
#include "Config.h"
#include "Display.h"
#include "Storage.h"
#include "Hardware.h"

// --- Module Instantiations ---
DisplayManager display(12, 13, 5, 4, 3, 2);
StorageManager storage;
HardwareController hardware;

SoftwareSerial bluetoothSerial(10, 11);
SoftwareSerial gsmSerial(7, 6);

// --- Keypad Setup ---
char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[4] = {A0, A1, A2, A3};
byte colPins[4] = {A4, A5, 2, 3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

// --- Global State ---
String inputPIN = "";
int wrongAttempts = 0;

void setup() {
    Serial.begin(9600);
    bluetoothSerial.begin(9600);
    gsmSerial.begin(9600);
    
    display.begin();
    hardware.begin();
    storage.initializeSystem();
    
    delay(1000);
    display.showMessage("BluePin Lock", "System Ready");
    Serial.println("System Started");
}

void loop() {
    handleKeypad();
    handleBluetooth();
}

void handleKeypad() {
    char key = keypad.getKey();
    if (key) {
        if (key == '#') {
            display.showMessage("Verifying...", "");
            verifyPIN(inputPIN);
            inputPIN = "";
        } else if (key == '*') {
            inputPIN = "";
            display.showMessage("Enter PIN:", "____");
            hardware.beep(1);
        } else if (inputPIN.length() < PIN_LENGTH) {
            inputPIN += key;
            String displayPIN = "";
            for (int i = 0; i < inputPIN.length(); i++) displayPIN += "*";
            for (int i = inputPIN.length(); i < PIN_LENGTH; i++) displayPIN += "_";
            display.showMessage("Enter PIN:", displayPIN);
            hardware.beep(1);
        }
    }
}

void handleBluetooth() {
    if (bluetoothSerial.available()) {
        String btInput = bluetoothSerial.readStringUntil('\n');
        btInput.trim();

        if (btInput.startsWith("PIN:")) {
            String attempt = btInput.substring(4);
            display.showMessage("BT Auth...", "Verifying");
            if (attempt == storage.getStoredPIN()) {
                grantAccess();
                bluetoothSerial.println("Access granted.");
            } else {
                denyAccess();
                bluetoothSerial.println("Wrong PIN.");
            }
        } else if (btInput.startsWith("CHANGEPIN:")) {
            String newPIN = btInput.substring(10);
            if (newPIN.length() == PIN_LENGTH) {
                storage.storePIN(newPIN);
                display.showMessage("PIN Updated", "Successfully");
                hardware.beep(2);
                delay(2000);
                display.showMessage("Enter PIN:", "____");
            }
        }
    }
}

void verifyPIN(String enteredPIN) {
    if (enteredPIN == storage.getStoredPIN()) {
        grantAccess();
        wrongAttempts = 0;
    } else {
        denyAccess();
        wrongAttempts++;
        if (wrongAttempts >= MAX_ATTEMPTS) {
            display.showMessage("ALERT!", "Lockout Active");
            // Trigger GSM alert here
            wrongAttempts = 0;
            delay(3000);
        }
        display.showMessage("Enter PIN:", "____");
    }
}

void grantAccess() {
    display.showMessage("Access Granted", "Unlocking...");
    hardware.setLEDStatus(true);
    hardware.unlockSolenoid();
    hardware.beep(3);
    
    display.showCountdown(5);
    
    hardware.lockSolenoid();
    hardware.resetLEDs();
    display.showMessage("Door Locked", "Enter PIN");
}

void denyAccess() {
    display.showMessage("Wrong PIN", "Try Again");
    hardware.setLEDStatus(false);
    hardware.beep(2);
    delay(2000);
    hardware.resetLEDs();
    display.showMessage("Enter PIN:", "____");
}