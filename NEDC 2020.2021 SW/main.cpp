#include <Arduino.h>
void setup() {
  int sensorValue = analogRead(A0);
  float soilMoisture
}

void loop() {
 sensorValue = analogRead(A0);
 soilMoisture = map(sensorValue, 652, 336, 2.6, 6.1);
 Serial.printLn(soilMoisture)
}