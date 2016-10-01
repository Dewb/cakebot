# cakebot
Glue to use ZMorph paste extruder on an ABB IRB robot

# build instructions

* install PlatformIO 3.1.0 from http://platformio.org/ or use

  ```
  $ pip install platformio
  ```

* build in PlatformIO IDE or via 
  
  ```
  $ cd cakebot
  $ pio run
  ```
  
# dependencies

cakebot uses the following libraries, which should be installed automatically by the PlatformIO build system.

* [Adafruit Motor Shield V2](https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library)
* [AccelStepper (Adafruit V2 fork)](https://github.com/adafruit/AccelStepper)
* [Bounce2](https://github.com/thomasfredericks/Bounce2)
