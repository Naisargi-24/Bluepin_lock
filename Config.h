#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// --- Hardware Pins ---
const int PIN_SOLENOID  = 8;
const int PIN_BUZZER    = 9;
const int PIN_LED_GREEN = A6;
const int PIN_LED_RED   = A7;

// --- Security Settings ---
const int PIN_LENGTH       = 4;
const int MAX_ATTEMPTS     = 3;
const int EEPROM_PIN_ADDR  = 0;
const int EEPROM_INIT_ADDR = 100;
const String DEFAULT_PIN   = "1234";

// --- GSM Settings ---
const String OWNER_NUMBER = "+919XXXXXXXXX";

#endif