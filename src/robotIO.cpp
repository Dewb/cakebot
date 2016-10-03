// robotIO.cpp

#include "Arduino.h"
#include "RobotIO.h"

void RobotIO::start() {
   // Use high six pins of PORTD (2-7) and two of PORTB (8-9)
   DDRD &= B00000011;
   DDRB &= B11111100;

   // turn off pullup resistors
   PORTD &= B00000011;
   PORTB &= B11111100;
}

void RobotIO::stop() {
}

unsigned char RobotIO::readByte() {
    return PIND >> 2 | ((PINB & 0x3) << 6);
}
