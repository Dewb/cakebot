// cakebot.cpp
//
// Arduino Uno code to drive stepper on a ZMorph paste extruder
// from an ABB robot with 24V digital data lines
// using the Adafruit Motor Shield 2.3
//
// Michael Dewberry 9/30/2016

#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include <Bounce2.h>

#include "robotIO.h"

// Set up the stepper driver and the AccelStepper speed control objects

Adafruit_MotorShield shield = Adafruit_MotorShield();
Adafruit_StepperMotor* pMotor = shield.getStepper(200, 1);

void forwardStepFn() { pMotor->onestep(FORWARD, SINGLE); }
void backwardStepFn() { pMotor->onestep(BACKWARD, SINGLE); }

AccelStepper stepper(forwardStepFn, backwardStepFn);

// Define pins and debounce object for the retract button

int pinRetractButton = 8;
Bounce retractButton = Bounce();

// Define state variables for speed control

float stepperSpeed = 800.0;
float retractSpeed = -200;

bool logging = true;

void setup() {

   shield.begin();

   // configure pins for reading 8 channels from ABB digital output
   initializeRobotPins();

   // configure input pin for the plunger retract button
   pinMode(pinRetractButton, INPUT_PULLUP);
   retractButton.attach(pinRetractButton);
   retractButton.interval(5);

   // start with stepper stationary
   stepper.setSpeed(0);

   if (logging) {
      Serial.begin(9600);
      Serial.print("Cakebot stepper controller initalized\n");
   }
}

void loop() {
   /*
   char robotSignal = readRobotSignal();

   retractButton.update();
   if (retractButton.read()) {
      stepperSpeed = retractSpeed;
   } else {
      stepperSpeed = (float)robotSignal;
   }
   */

   stepper.setSpeed(stepperSpeed);
   stepper.runSpeed();
}
