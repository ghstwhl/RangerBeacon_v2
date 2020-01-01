/* Black Sheep Ranger Beacon v2
*  
*  This creates a constant, or pulsing, green light using a 100px strand of APA102 LEDs
*  The mode is switched between pulsing and constant by turning it off, and then on again.
*  This is accomplished by storing the mode in EEPROM and flipping it in the setup() function.
*  
*  Copyright 2020 - Chris Knight - merlin@ghostwheel.com
*  
*  Released under the CC BY-NC-SA license: https://creativecommons.org/licenses/by-nc-sa/4.0/
*/


#include <APA102.h> // https://github.com/pololu/apa102-arduino
#include <EEPROM.h> // https://github.com/Chris--A/EEPROM

// Data and Clock pins:
//attiny85
#define DATAPIN 0
#define CLOCKPIN 1
/* 
// Arduino
#define DATAPIN 11
#define CLOCKPIN 13
*/


// Initialize the APA102 object
APA102<DATAPIN, CLOCKPIN> ledStrip;

// Set the number of LEDs to control.
#define LEDS  100

int mode = 0; //Default mode 0 = constant on.

void setup()
{
  //Read eeprom to get the mode
  EEPROM.get(0, mode);

  // flip the mode on boot
  if (0 == mode) {
    EEPROM.put(0, 1);
  }
  else {
    EEPROM.put(0, 0);
  }

}

// Simple loop that pulses the strand between green values 127 and 255
// The specific APA102 LEDs I am using from Cool Neon are already gamma
// corrected, so this should be between 100% and 50% intensity.
void pulse() {
  for (int G = 255; 127 <= G; G -= 8 ) {
    ledStrip.startFrame();
    for(int i = 0; i < LEDS; i++) {
      ledStrip.sendColor(G, 0, 0, 31);
    }
    ledStrip.endFrame(LEDS);
    delay(10);
  }

  for (int G = 127; G <= 255; G += 8) {
    ledStrip.startFrame();
    for(int i = 0; i < LEDS; i++) {
      ledStrip.sendColor(G, 0, 0, 31);
    }
    ledStrip.endFrame(LEDS);
    delay(10);
  }
}

// Light them up, and then put the delay forever.
void constant() {
  ledStrip.startFrame();
  for(int i = 0; i < LEDS; i++) {
    ledStrip.sendColor(255, 0, 0, 31);
  }
  ledStrip.endFrame(LEDS);

  while ( 1 == 1 ) {
    delay(4294967295);
  }
}

void loop()
{
  if ( 0 == mode ) {
    constant();
  }
  else {
    pulse();
  }
}
