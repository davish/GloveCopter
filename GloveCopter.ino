const int LED = 3; // The LED
const int FREQ = 38000; // The carrier frequency
const int ROTATION_STATIONARY = 63;
const int CAL = -30 // Trim

long previousMicros = 0;

int pulse = 0;

int Throttle, LeftRight, ForwardBackward;

// Change the values below to control the copter
Throttle = 0; 
LeftRight = 0;
ForwardBackward = 0;

void setup() {
  pinMode(LED, OUTPUT); // Set pin to output
  Serial.begin(9600);
}

void loop() {
  Throttle = getZeroes();
  LeftRight = getZeroes();
  ForwardBackward = getZeroes();
  
  unsigned long currentMicros = micros();
  if(currentMicros - previousMicros >= 180000) {
    previousMicros = currentMicros;
    sendCommand(LeftRight, ForwardBackward, Throttle);
  }
}

int getZeroes() { return 0; }

void sendHeader() {
  pulseIR(2000);
  delayMicroseconds(2000); // Low another 2
}

void sendZero() {
  pulseIR(300);
  delayMicroseconds(300);
}

void sendOne() {
  pulseIR(300);
  delayMicroseconds(700);
}

void sendFooter() {
  pulseIR(300);
}


void sendCommand(int leftRight, int forwardBack, int throttle) {
  sendHeader();
  // Fancy Bitwise logic courtesy of Kerry Wong
  for (int i = 7; i >=0; i--) {
    int b = ((ROTATION_STATIONARY + leftRight + CAL) & (1 << i)) >> i;     
    if (b > 0) sendOne(); else sendZero();
  }
  for (int i = 7; i >=0; i--) {
    int b = ((ROTATION_STATIONARY + forwardBack) & (1 << i)) >> i; 
    if (b > 0) sendOne(); else sendZero();
  }
  for (int i = 7; i >=0; i--) {
    int b = ((throttle) & (1 << i)) >> i;
    if (b > 0) sendOne(); else sendZero();
  }
  
  sendFooter();
}

void pulseIR(long microsecs) {
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(LED, HIGH);  // this takes about 3 microseconds to happen
    delayMicroseconds(10);         // hang out for 10 microseconds
    digitalWrite(LED, LOW);   // this also takes about 3 microseconds
    delayMicroseconds(10);         // hang out for 10 microseconds
 
    // so 26 microseconds altogether
    microsecs -= 26;
 
  }
 
}


