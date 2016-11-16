/* 
Example Timer1 Interrupt
Flash LED every second
*/

#define ledPin LED_BUILTIN
#define timer0_preload 40161290
#include <Adafruit_NeoPixel.h>

#define my_delay   1 // Set interrupt time in secs. Value = 2 x Number of Seconds, so 10-Secs = 10 x 2 = 20

// Which pin on the ESP8266 is connected to the NeoPixels?
#define PIN        D4

// How many NeoPixels are attached to the ESP8266?
#define NUMPIXELS  16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
byte R,G,B;
volatile int toggle;

int i = 0;

void inline interrupt_handler (void){
  R = random(0,20);
  G = random(0,20);
  B = random(0,20);
  pixels.setPixelColor(i, pixels.Color(R,G,B)); // Moderately bright LED's
  pixels.show(); // This sends the updated pixel color to the hardware.
  i = i + 1;
  if (i > NUMPIXELS) i = 0; 
  timer0_write(ESP.getCycleCount() + timer0_preload * my_delay); // 
}
 
void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  noInterrupts();
  timer0_isr_init();
  timer0_attachInterrupt(interrupt_handler);
  timer0_write(ESP.getCycleCount() + timer0_preload * my_delay);
  interrupts();
}

void loop() {
  // Do some work here if you want!
} 
