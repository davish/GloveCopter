const int LED = 3; // The LED
const int FREQ = 38000; // The carrier frequency
const int ROTATION_STATIONARY = 63;
const int CAL = -5; // Trim

// const int TRIMPOT = 0;

// Now the min and max on the accelerometer
const int XMIN = 325;
const int XMAX = 345;
const int XMID = XMIN + (XMAX - XMIN) / 2;

const int YMIN = 325;
const int YMAX = 345;
const int YMID = YMIN + (YMAX - YMIN) / 2;

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
    Throttle = getThrottle(5, Throttle);
    if(Throttle != 0) {
      // LeftRight, ForwardBackward, Throttle
      sendCommand(LeftRight, ForwardBackward  , Throttle);
    }
//    Serial.println(LeftRight);
//    Serial.println(ForwardBackward);
    Serial.println(Throttle);
  }
//  Throttle = map(analogRead(5), 0, 1023, 0, 127);
  LeftRight = getTiltY(0) + CAL;
  ForwardBackward = getTiltX(1);
  
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
  if (reading <= YMIN) // Less than lower threshold
    reading = 0 - (YMID - YMIN);
    // if ymid is 335, I want this to be 0 - (ymid - ymin)
  else if (reading >= YMAX) // Greater than upper threshold
    reading = YMID - YMIN;
  else
    reading = reading - YMID; // just get it within
  if (reading == 1 || reading == -1)
    reading = 0;
  int r = floor(map(reading, 0 - (YMID - YMIN), YMID - YMIN, -62, 62));
  if (r > 62)
    r = 62;
  if (r < -62)
    r = -62;
  return r;
}

int getTiltX(int pin) {
    int reading = analogRead(pin);
  if (reading <= XMIN) // Less than lower threshold
    reading = 0 - (XMID - XMIN);
  else if (reading >= XMAX) // Greater than upper threshold
    reading = XMID - XMIN;
  else
    reading = reading - 335; // just get it within
  if (reading == 1 || reading == -1)
    reading = 0;
  int r;
  r = floor(map(reading, 0 - (XMID - XMIN), XMID - XMIN, 62, -62)); // Pitch needs to be flipped
  if (r > 62)
    r = 62;
  if (r < -62)
    r = -62;
  return r;
}

int getThrottle(int pin, int throttle) {
  int a = analogRead(pin);
  if (a > 460 && a < 530)
    a = 530;
  int change = map(a, 167, 810, -5, 5);
  
  int newThrottle = throttle + (change * 2);
  
  if (newThrottle > 127)
    newThrottle = 127;
  if (newThrottle < 0)
    newThrottle = 0;
  
  return newThrottle;
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


