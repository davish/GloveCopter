/*
  License: 
*/

const int LED = 3; // The LED
const int FREQ = 38000; // The carrier frequency


unsigned long t;

void setup() {
  pinMode(LED, OUTPUT); // Set pin to output
  t = millis();
}

void loop() {
  if (t - millis() == 180) {
    exampleController();
    t = millis();
  }
}

void header() {
  tone(LED, FREQ);
  delayMicroseconds(2000); // Delay 2 milliseconds
  noTone(LED); // stop the tone
  delayMicroseconds(2000); // Low another 2
}

void zero() {
  tone(LED, FREQ);
  delayMicroseconds(300);
  noTone(LED);
  delayMicroseconds(300);
}

void one() {
  tone(LED, FREQ);
  delayMicroseconds(300);
  noTone(LED);
  delayMicroseconds(700);
}

void footer() {
  tone(LED, FREQ);
  delayMicroseconds(300);
  noTone(LED);
}


// Example controler that just turns the throttle on 50%
// 00111111 00111111 00111111
void exampleController() {
  header();
  zero(); zero(); one(); one(); one(); one(); one(); one();
  zero(); zero(); one(); one(); one(); one(); one(); one();
  zero(); zero(); one(); one(); one(); one(); one(); one();
  footer();
}


void sendCommand(int throttle, ) {
  for (int i = 7; i >=0; i--) {
    // Fancy Bit-shifting courtesy of Kerry Wong
    b = ((ROTATION_STATIONARY + leftRight) & (1 << i)) >> i;    
    if (b > 0) sendOne(); else sendZero();
  }
}
