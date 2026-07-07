#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>

class HardwareController {
public:
    void begin();
    void setLEDStatus(bool granted);
    void resetLEDs();
    void beep(int count);
    void unlockSolenoid();
    void lockSolenoid();
};

#endif