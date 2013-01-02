void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("x: "); Serial.println(analogRead(1));
  Serial.print("y: "); Serial.println(analogRead(0));
//  Serial.print("z: "); Serial.println(analogRead(2));
  Serial.println(' ');
  delay(500);
}
