// robotIO.cpp

#include "Arduino.h"
#include "RobotIO.h"

#define USE_DIRECT_PORT

#ifndef USE_DIRECT_PORT

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

inline char GetBitArrayAsByte(const char inputArray[8])
{
    char result = 0;
    for (int idx = 0; idx < 8; ++idx)
    {
        result |= (inputArray[7-idx] << idx);
    }
    return result;
}

#endif


void RobotIO::start() {
#ifndef USE_DIRECT_PORT
   pinMode(pinRobotDO2, INPUT);
   pinMode(pinRobotDO3, INPUT);
   pinMode(pinRobotDO4, INPUT);
   pinMode(pinRobotDO5, INPUT);
   pinMode(pinRobotDO6, INPUT);
   pinMode(pinRobotDO7, INPUT);
   pinMode(pinRobotDO8, INPUT);
   pinMode(pinRobotDO9, INPUT);
#else
   // set all port D pins to input, disabling serial
   DDRD = B00000000;
   // turn off pullup resistors
   PORTD = B00000000;
#endif
}

void RobotIO::stop() {
   // set all port D pins to input except pin 1, re-enabling serial
#ifndef USE_DIRECT_PORT
   pinMode(pinRobotDO2, INPUT);
   pinMode(pinRobotDO3, OUTPUT);
   pinMode(pinRobotDO4, INPUT);
   pinMode(pinRobotDO5, INPUT);
   pinMode(pinRobotDO6, INPUT);
   pinMode(pinRobotDO7, INPUT);
   pinMode(pinRobotDO8, INPUT);
   pinMode(pinRobotDO9, INPUT);
#else
   DDRD = B00000010;
#endif
}

unsigned char RobotIO::readByte() {
#ifndef USE_DIRECT_PORT
    robotSignalArray[0] = digitalRead(pinRobotDO2);
    robotSignalArray[1] = digitalRead(pinRobotDO3);
    robotSignalArray[2] = digitalRead(pinRobotDO4);
    robotSignalArray[3] = digitalRead(pinRobotDO5);
    robotSignalArray[4] = digitalRead(pinRobotDO6);
    robotSignalArray[5] = digitalRead(pinRobotDO7);
    robotSignalArray[6] = digitalRead(pinRobotDO8);
    robotSignalArray[7] = digitalRead(pinRobotDO9);
    return GetBitArrayAsByte(robotSignalArray);
#else
    return PIND;
#endif
}
