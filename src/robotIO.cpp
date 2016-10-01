// robotIO.cpp

#include "Arduino.h"

// Define pins and state variables for robot input

int pinRobotDO2 = 0;
int pinRobotDO3 = 1;
int pinRobotDO4 = 2;
int pinRobotDO5 = 3;
int pinRobotDO6 = 4;
int pinRobotDO7 = 5;
int pinRobotDO8 = 6;
int pinRobotDO9 = 7;

char robotSignalArray[8];
char robotSignal;

void initializeRobotPins() {
    pinMode(pinRobotDO2, INPUT);
    pinMode(pinRobotDO3, INPUT);
    pinMode(pinRobotDO4, INPUT);
    pinMode(pinRobotDO5, INPUT);
    pinMode(pinRobotDO6, INPUT);
    pinMode(pinRobotDO7, INPUT);
    pinMode(pinRobotDO8, INPUT);
    pinMode(pinRobotDO9, INPUT);
}

inline char GetBitArrayAsByte(const char inputArray[8])
{
    char result = 0;
    for (int idx = 0; idx < 8; ++idx)
    {
        result |= (inputArray[7-idx] << idx);
    }
    return result;
}

char readRobotSignal() {
    robotSignalArray[0] = digitalRead(pinRobotDO2);
    robotSignalArray[1] = digitalRead(pinRobotDO3);
    robotSignalArray[2] = digitalRead(pinRobotDO4);
    robotSignalArray[3] = digitalRead(pinRobotDO5);
    robotSignalArray[4] = digitalRead(pinRobotDO6);
    robotSignalArray[5] = digitalRead(pinRobotDO7);
    robotSignalArray[6] = digitalRead(pinRobotDO8);
    robotSignalArray[7] = digitalRead(pinRobotDO9);
    return GetBitArrayAsByte(robotSignalArray);
}
