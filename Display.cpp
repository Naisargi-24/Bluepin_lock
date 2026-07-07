#include "Display.h"

DisplayManager::DisplayManager(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) 
    : lcd(rs, en, d4, d5, d6, d7) {}

void DisplayManager::begin() {
    lcd.begin(16, 2);
}

void DisplayManager::showMessage(String line1, String line2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
}

void DisplayManager::showCountdown(int seconds) {
    for (int i = seconds; i > 0; i--) {
        lcd.setCursor(0, 1);
        lcd.print("Locking in: ");
        lcd.print(i);
        lcd.print("s  ");
        delay(1000);
    }
}