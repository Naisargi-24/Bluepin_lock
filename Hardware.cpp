#include "Hardware.h"
#include "Config.h"

void HardwareController::begin() {
    pinMode(PIN_SOLENOID, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);
    
    lockSolenoid();
    digitalWrite(PIN_BUZZER, LOW);
    resetLEDs();
}

void HardwareController::setLEDStatus(bool granted) {
    digitalWrite(PIN_LED_GREEN, granted ? HIGH : LOW);
    digitalWrite(PIN_LED_RED, granted ? LOW : HIGH);
}

void HardwareController::resetLEDs() {
    digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LED_RED, LOW);
}

void HardwareController::beep(int count) {
    for (int i = 0; i < count; i++) {
        digitalWrite(PIN_BUZZER, HIGH);
        delay(100);
        digitalWrite(PIN_BUZZER, LOW);
        delay(100);
    }
}

void HardwareController::unlockSolenoid() {
    digitalWrite(PIN_SOLENOID, HIGH);
}

void HardwareController::lockSolenoid() {
    digitalWrite(PIN_SOLENOID, LOW);
}