#include <LiquidCrystal.h>
//#include <config.h>
#define lcdReset 0
#define lcdEnable 1
#define lcdDS4 2
#define lcdDS5 3
#define lcdDS6 4
#define lcdDS7 5
#define lcdColumns 20
#define lcdRows 4

float fromLow = 652;
float fromHigh = 336;
float toLow = 2.6;
float toHigh = 6.1;
float sensorVal;
float moistureVal;

LiquidCrystal lcd(lcdReset, lcdEnable, lcdDS4, lcdDS5, lcdDS6, lcdDS7);


/*
int floatMap(value1, fromLow1, fromHigh1, toLow1, toHigh1) {
  return (float)(value1 - fromLow1) * (toHigh1 - toLow1) / (float)(fromHigh1 - fromLow1) + toLow1;
}
*/

void setup() {
  lcd.begin(lcdColumns,lcdRows);
  Serial.begin(9600);
}

void loop() {
  sensorVal = analogRead(A0);
//  moistureVal = floatMap(sensorVal, lowerInitialBound, upperIntialBound,lowerFinalBound, upperFinalBound);
  moistureVal = toLow + (sensorVal - fromLow) * ((toHigh - toLow)/(fromHigh - fromLow));
  Serial.println(moistureVal)
/*
  if(moistureVal>3.5) {
    lcd.setCursor(0,0);
    lcd.print(moistureVal);
    lcd.setCursor(0,1);
    lcd.print("No Irrigation");
    lcd.clear();
  }
    else {
      lcd.setCursor(0,0);
      lcd.print(moistureVal);
      lcd.setCursor(0,1);
      lcd.print("Time to Irrigate");
      lcd.clear();
  }
  delay(2000);
*/
}
