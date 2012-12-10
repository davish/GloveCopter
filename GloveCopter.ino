/*
  Syma S107 Helicopter controler
  Protocol spec: http://www.jimhung.co.uk/?p=901
  Binary conversion code: http://www.kerrywong.com/2012/08/27/reverse-engineering-the-syma-s107g-ir-protocol/
  License: https://raw.github.com/dbh937/files/master/license
  Author: Davis Haupt
  Date: 12/10/12
*/

const int LED = 3; // The LED
const int hi = // the duration, in us, of a pulse
const int FREQ = 38000 // The carrier frequency


void setup() {
  pinMode(LED, OUTPUT); // Set pin to output
}

void loop() {}

void preamble() {
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


