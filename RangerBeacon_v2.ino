/* Black Sheep Ranger Beacon v2
*  
*  This creates a constant, or pulsing, green light using a 100px strand of APA102 LEDs
*  The mode is switched between pulsing and constant by turning it off, and then on again.
*  This is accomplished by storing the mode in EEPROM and flipping it in the setup() function.
*  
*  While developed on a more traditional Arduino device, the production deployment of this
*  code would be to an ATTiny85 in the form of a DigiSpark USB development board(1).  For 
*  that you need to add http://digistump.com/package_digistump_index.json to the "Additional
*  Board Manager URLs" in preferences in the Arduino IDE and then add the DigiStump AVR
*  Boards package under Tools/Board/Boards Manager.  If your having problems with LED
*  brightness or inconsistent LED behavior, you might need to compensate for design issues
*  with the DigiSpark(2).
*  
*  
*  (1) The original (http://digistump.com/products/1) is out of production, but knock-offs 
*      abound on AliExpress, TradeMe, eBay, etc.
*  (2) The VIN pin on the DigiSpark isn't diretly connected to the 5V USB connector.  While
*      the official schematic(3) has the pinout of a USB-A connector incorrect, it looks like
*      there is a diode on the 5V pin, and a MC78M05BDTRKG voltage regulator on the VIN pin,
*      which makes both the 5V and VIN pins a bad choice for powering a string of LEDs.  For
*      that reason I connected my APA102 data line to D0, the clock line to D1, and the LEDs 
*      5V and GND directly to the USB traces.  It's hacky, but it works.  Pic coming soon.
*  (3) https://s3.amazonaws.com/digispark/DigisparkSchematicFinal.pdf
*  
*  Copyright 2020 - Chris Knight - merlin@ghostwheel.com
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

#define GREENMAX 127
#define GREENMIN 63


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
  for (int G = GREENMAX; GREENMIN <= G; G -= 8 ) {
    ledStrip.startFrame();
    for(int i = 0; i < LEDS; i++) {
      ledStrip.sendColor(G, 0, 0, 31);
    }
    ledStrip.endFrame(LEDS);
    delay(10);
  }

  for (int G = GREENMIN; G <= GREENMAX; G += 8) {
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
    ledStrip.sendColor(GREENMAX, 0, 0, 31);
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
