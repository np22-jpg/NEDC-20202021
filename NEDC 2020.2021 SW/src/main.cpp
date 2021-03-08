#include <LiquidCrystal.h>
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

float fromLow = 652;
float fromHigh = 336;
float toLow = 2.6;
float toHigh = 6.1;
float sensorVal;
float moistureVal;

void setup() {
  lcd.begin(20,4);
}

void loop() {
  sensorVal = analogRead(A0);
  moistureVal = toLow + (sensorVal - fromLow) * ((toHigh - toLow)/(fromHigh - fromLow));
  if(moistureVal>3.5){
    lcd.setCursor(0,0);
    lcd.print(moistureVal);
    lcd.setCursor(0,1);
    lcd.print("No Irrigation");
    delay(50000);
    lcd.clear();
  }
    else {
      lcd.setCursor(0,0);
      lcd.print(moistureVal);
      lcd.setCursor(0,1);
      lcd.print("Time to Irrigate");
      delay(15000);
      lcd.clear();
  }

delay(2000);
}
