#include <LiquidCrystal.h>
#include <config.h>
LiquidCrystal lcd(lcdReset, lcdEnable, lcdDS4, lcdDS5, lcdDS6, lcdDS7);
/*
int floatMap(value1, fromLow1, fromHigh1, toLow1, toHigh1) {
  return (float)(value1 - fromLow1) * (toHigh1 - toLow1) / (float)(fromHigh1 - fromLow1) + toLow1;
}
*/
void setup() {
  lcd.begin(20,4);
  lcd.begin(lcdColumns,lcdRows);
  Serial.begin(9600);
}

void loop() {
  sensorVal = analogRead(A0);
//  moistureVal = floatMap(sensorVal, lowerInitialBound, upperIntialBound,lowerFinalBound, upperFinalBound);
  moistureVal = toLow + (sensorVal - fromLow) * ((toHigh - toLow)/(fromHigh - fromLow));
  if(moistureVal>3.5) {
    lcd.setCursor(0,0);
    lcd.print(moistureVal);
    lcd.setCursor(0,1);
    lcd.print("No need to water");
    delay(100);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print(moistureVal);
    lcd.setCursor(0,1);
    lcd.print("Time to Irrigate");
    delay(100);
  }

Serial.println(moistureVal);
delay(150);
}