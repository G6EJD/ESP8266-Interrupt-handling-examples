/* 
Example Timer0 Interrupt
Flash LED every second
*/

#define ledPin LED_BUILTIN // or define ledPin 5
#define timer0_preload 40161290

#define my_delay 2 // Set interrupt time in secs. Value = 2 x Number of Seconds, so 10-Secs = 10 x 2 = 20


volatile int toggle;

void inline handler (void){
  toggle = (toggle == 1) ? 0 : 1;
  digitalWrite(ledPin, toggle);
  timer0_write(ESP.getCycleCount() + timer0_preload * my_delay); // 
}
 
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // Turn OFF LED to start with
  noInterrupts();
  timer0_isr_init();
  timer0_attachInterrupt(handler);
  timer0_write(ESP.getCycleCount() + timer0_preload * my_delay);
  interrupts();
}

void loop() {
  // Do some work here
} 
