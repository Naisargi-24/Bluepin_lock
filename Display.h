#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class DisplayManager {
private:
    LiquidCrystal lcd;
public:
    DisplayManager(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    void begin();
    void showMessage(String line1, String line2);
    void showCountdown(int seconds);
};

#endif