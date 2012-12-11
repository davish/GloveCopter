/*
  License: 
*/

const int LED = 3; // The LED
const int FREQ = 38000; // The carrier frequency
const int ROTATION_STATIONARY = 63;

long previousMicros = 0;


void setup() {
  pinMode(LED, OUTPUT); // Set pin to output
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMicros = micros();

  if(currentMicros - previousMicros >= 180000) {
    previousMicros = currentMicros;
    sendCommand(63, 63, 63);
    Serial.println(currentMicros - previousMicros);
  }
}

void header() {
  pulseIR(2000)
  delayMicroseconds(2000); // Low another 2
}

void zero() {
  pulseIR(300);
  delayMicroseconds(300);
}

void one() {
  pulseIR(300);
  delayMicroseconds(700);
}

void footer() {
  tone(LED, FREQ);
  delayMicroseconds(300);
  noTone(LED);
}


// Example controler that just turns the throttle on 50%
// 00111111 00111111 00111111 00111000
void exampleController() {
  header();
  zero(); zero(); one(); one(); one(); one(); one(); one();
  
  zero(); zero(); one(); one(); one(); one(); one(); one();
  
  zero(); zero(); one(); one(); one(); one(); one(); one();
  
  zero(); zero(); one(); one(); one(); zero(); zero(); zero();
  footer();
  Serial.println("Transmitted.");
}


void sendCommand(int leftRight, int forwardBack, int throttle) {
  header();
  
  for (int i = 7; i >=0; i--) {
    int b = ((ROTATION_STATIONARY + leftRight) & (1 << i)) >> i; // Fancy Bit-shifting courtesy of Kerry Wong    
    b > 0 ? one() : zero();
    // if (b > 0) sendOne(); else sendZero();
  }
  for (int i = 7; i >=0; i--) {
    int b = ((ROTATION_STATIONARY + forwardBack) & (1 << i)) >> i; // Fancy Bit-shifting courtesy of Kerry Wong    
    b > 0 ? one() : zero();
    // if (b > 0) sendOne(); else sendZero();
  }
  for (int i = 7; i >=0; i--) {
    int b = ((throttle) & (1 << i)) >> i; // Fancy Bit-shifting courtesy of Kerry Wong    
    b > 0 ? one() : zero();
    // if (b > 0) sendOne(); else sendZero();
  }
  
  footer();
}

void pulseIR(long microsecs) {
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(3, HIGH);  // this takes about 3 microseconds to happen
    delayMicroseconds(10);         // hang out for 10 microseconds
    digitalWrite(3, LOW);   // this also takes about 3 microseconds
    delayMicroseconds(10);         // hang out for 10 microseconds
 
    // so 26 microseconds altogether
    microsecs -= 26;
 
  }
 
}
