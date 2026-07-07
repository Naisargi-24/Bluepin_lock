#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>

class StorageManager {
public:
    void initializeSystem();
    String getStoredPIN();
    void storePIN(String newPIN);
};

#endif