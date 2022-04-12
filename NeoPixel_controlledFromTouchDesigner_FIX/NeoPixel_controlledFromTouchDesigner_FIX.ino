// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int numOfBytes = NUMPIXELS * 3;
char inputBuffer[numOfBytes];

int bytesReceived;

int red, green, blue;

char inChar;

void setup() {
  Serial.begin(115200);

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
}

void loop() {
  while (Serial.available()) {
    inChar = (char)Serial.read();
  }
  Serial.println(inChar);
  if (inChar == 'f') {
    int bytesReceived = Serial.readBytes(inputBuffer, numOfBytes);

    if (bytesReceived == numOfBytes) {
      pixels.clear();
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

        pixels.setPixelColor(i, pixels.Color(inputBuffer[3 * i], inputBuffer[3 * i + 1], inputBuffer[3 * i + 2]));

      }
      pixels.show();   // Send the updated pixel colors to the hardware.
    }

  }

}
