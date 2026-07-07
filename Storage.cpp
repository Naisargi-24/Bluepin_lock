#include "Storage.h"
#include "Config.h"
#include <EEPROM.h>

void StorageManager::initializeSystem() {
    if (EEPROM.read(EEPROM_INIT_ADDR) != 123) {
        storePIN(DEFAULT_PIN);
        EEPROM.write(EEPROM_INIT_ADDR, 123);
        Serial.println("System Initialized with Default PIN.");
    }
}

String StorageManager::getStoredPIN() {
    String pin = "";
    for (int i = 0; i < PIN_LENGTH; i++) {
        char digit = EEPROM.read(EEPROM_PIN_ADDR + i);
        pin += digit;
    }
    return pin;
}

void StorageManager::storePIN(String newPIN) {
    for (int i = 0; i < PIN_LENGTH; i++) {
        EEPROM.write(EEPROM_PIN_ADDR + i, newPIN[i]);
    }
}