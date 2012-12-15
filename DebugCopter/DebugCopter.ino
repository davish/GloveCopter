/*
  Debug the commands being sent to the copter without actually sending them.
*/

const int LED = 3; // The LED
const int FREQ = 38000; // The carrier frequency
const int ROTATION_STATIONARY = 63;
const int CAL = 0; // Trim

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
//    Serial.println(Throttle);
    Serial.println(LeftRight);
    Serial.println(analogRead(1));
    Serial.println(ForwardBackward);
    Serial.println(analogRead(0));
    Serial.println(" ");
  }
  Throttle = analogRead(5);
  Throttle = map(Throttle, 0, 1023, 0, 127);
  LeftRight = getTilt(1);
  ForwardBackward = getTilt(0);
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
    int b = ((leftRight) & (1 << i)) >> i;     
    if (b > 0) sendOne(); else sendZero();
  }
  for (int i = 7; i >=0; i--) {
    int b = ((forwardBack) & (1 << i)) >> i; 
    if (b > 0) sendOne(); else sendZero();
  }
  for (int i = 7; i >=0; i--) {
    int b = ((throttle) & (1 << i)) >> i;
    if (b > 0) sendOne(); else sendZero();
  }
  
  sendFooter();
}

int getTilt(int pin) {
  int reading = analogRead(pin);
  if (reading <= 330) // Less than lower threshold
    reading = -5;
  else if (reading >= 340) // Greater than upper threshold
    reading = 5;
  else
    reading = reading - 335; // just get it within
  int r;
  if (pin == 1) {
    r = floor(map(reading, -5, 5, 0, 127));
  }
  else
    r = floor(map(reading, -5, 5, 127, 0)); // Pitch needs to be flipped
  if (r <= 80 && r >= 50)
    r = 63;
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


