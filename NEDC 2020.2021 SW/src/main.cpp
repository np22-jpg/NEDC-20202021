#include <LiquidCrystal.h>
#include <Wire.h>
//int Contrast=75;  Contrast is handled on my LCD itself
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

float fromLow = 652;
float fromHigh = 336;
float toLow = 2.6;
float toHigh = 6.1;
float sensorVal;
float moistureVal;

void setup() {
//  Serial.begin(9600);
//  analogWrite(6, Contrast);
  lcd.begin(20,4);
}

void loop() {
  sensorVal = analogRead(A0);
//delay(5000);
  moistureVal = toLow + (sensorVal - fromLow) * ((toHigh - toLow)/(fromHigh - fromLow));
// lcd.print(moistureVal + " ");
  if(moistureVal>3.5){
//    Serial.println(moistureVal);
//    Serial.println("No Irrigation");
//    delay(2000);
//    Wire.setClock(10000);
    lcd.setCursor(0,0);
    lcd.print(moistureVal);
//    delay(5000);
    lcd.setCursor(0,1);
    lcd.print("No Irrigation");
    delay(50000);
    lcd.clear();
    //delay(15000);
  }
    else {
//     Serial.println(moistureVal);
//     Serial.println("Time to Irrigate");
//    delay(10000);
//    Wire.setClock(10000);
      lcd.setCursor(0,0);
      lcd.print(moistureVal);
//      delay(15000);
      lcd.setCursor(0,1);
      lcd.print("Time to Irrigate");
      delay(15000);
      lcd.clear();
//      delay(1500);
  }

delay(2000);
}
