#include <LiquidCrystal.h>
#include <config.h>
LiquidCrystal lcd(lcdReset, lcdEnable, lcdDS4, lcdDS5, lcdDS6, lcdDS7);

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//got this one off the forums 
void setup() {
  lcd.begin(20,4);
  lcd.begin(lcdColumns,lcdRows);
  Serial.begin(9600);
  
}

void loop() {
  sensorVal = analogRead(A0);
  moistureVal = mapf(sensorVal, lowerInitialBound, upperInitialBound, lowerFinalBound, upperFinalbound);
//  moistureVal = toLow + (sensorVal - fromLow) * ((toHigh - toLow)/(fromHigh - fromLow));
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