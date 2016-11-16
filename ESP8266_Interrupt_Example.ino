/* 
Example Timer1 Interrupt
Flash LED every second
*/

#define ledPin LED_BUILTIN
#define timer0_preload 40161290

#define my_delay 2 // Set interrupt time in secs. Value = 2 x Number of Seconds, so 10-Secs = 10 x 2 = 20


volatile int toggle;

void inline handler (void){
  toggle = (toggle == 1) ? 0 : 1;
  digitalWrite(BUILTIN_LED, toggle);
  timer0_write(ESP.getCycleCount() + timer0_preload * my_delay); // 
}
 
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH); // Turn OFF LED to start with
  noInterrupts();
  timer0_isr_init();
  timer0_attachInterrupt(handler);
  timer0_write(ESP.getCycleCount() + timer0_preload * my_delay);
  interrupts();
}

void loop() {
  // Do some work here
} 
