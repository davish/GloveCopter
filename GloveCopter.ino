
const int LED = 3; // The LED
const int FREQ = 38000; // The carrier frequency
const int ROTATION_STATIONARY = 63;
const int CAL = -5; // Trim
// const int TRIMPOT = 0;

// Now the min and max on the accelerometer
const int XMIN = 330;
const int XMAX = 340;

const int YMIN = 330;
const int YMAX = 340;

long previousMicros = 0;

int pulse = 0;


// Change the values below to control the copter
int Throttle = 0; 
int LeftRight = 0;
int ForwardBackward = 0;

void setup() {
  pinMode(LED, OUTPUT); // Set pin to output
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMicros = micros();
  if(currentMicros - previousMicros >= 180000) {
    previousMicros = currentMicros;
    sendCommand(LeftRight, ForwardBackward, Throttle);
  }
  Throttle = map(analogRead(5), 0, 1023, 0, 127);
  LeftRight = getTiltY(1) + CAL;
  ForwardBackward = getTiltX(0);
  
  if (LeftRight > 62)
    LeftRight = 62;
  else if (LeftRight < -62)
    LeftRight = -62;
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
    int b = ((leftRight + ROTATION_STATIONARY) & (1 << i)) >> i;     
    if (b > 0) sendOne(); else sendZero();
  }
  for (int i = 7; i >=0; i--) {
    int b = ((forwardBack + ROTATION_STATIONARY) & (1 << i)) >> i; 
    if (b > 0) sendOne(); else sendZero();
  }
  for (int i = 7; i >=0; i--) {
    int b = ((throttle) & (1 << i)) >> i;
    if (b > 0) sendOne(); else sendZero();
  }
  
  sendFooter();
}

int getTiltY(int pin) {
  int reading = analogRead(pin);
  if (reading <= 330) // Less than lower threshold
    reading = -5;
  else if (reading >= 340) // Greater than upper threshold
    reading = 5;
  else
    reading = reading - 335; // just get it within
  if (reading == 1 || reading == -1)
    reading = 0;
  int r = floor(map(reading, -5, 5, -62, 62));
  if (r > 62)
    r = 62;
  if (r < -62)
    r = -62;
  return r;
}

int getTiltX(int pin) {
    int reading = analogRead(pin);
  if (reading <= 335) // Less than lower threshold
    reading = -5;
  else if (reading >= 345) // Greater than upper threshold
    reading = 5;
  else
    reading = reading - 340; // just get it within
  if (reading == 1 || reading == -1)
    reading = 0;
  int r;
  r = floor(map(reading, -5, 5, 62, -62)); // Pitch needs to be flipped
  if (r > 62)
    r = 62;
  if (r < -62)
    r = -62;
  return r;
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


