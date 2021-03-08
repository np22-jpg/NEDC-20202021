#include <LiquidCrystal.h>
#include <config.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


LiquidCrystal lcd(lcdReset, lcdEnable, lcdDS4, lcdDS5, lcdDS6, lcdDS7);
DHT_Unified dht(DHTPIN, DHTTYPE);

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//got this one off the forums 

int brightnessSensor;
int brightnessReading;

void setup() {
  lcd.begin(20,4);
  lcd.begin(lcdColumns,lcdRows);
  Serial.begin(9600);
  dht.begin();
  lcd.setCursor(0,0);
  lcd.print("Soil Moisture: ");
  lcd.setCursor(0,1);
  lcd.print("Soil Type: ");
  lcd.setCursor(0,2);
  lcd.print("Temp: ");
  lcd.setCursor(12, 2);
  lcd.print("Sun: ");
  lcd.setCursor(0,3);
  lcd.print("RH: ");

}

void loop() {
  dht.temperature();
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  Serial.print(event.temperature);
  Serial.println("*C");
  lcd.setCursor(6, 2);
  lcd.print(event.temperature);
  dht.humidity().getEvent(&event);
  Serial.print(event.relative_humidity);
  Serial.println("%");
  lcd.setCursor(4,3);
  lcd.print(event.relative_humidity);
  sensorVal = analogRead(A0);
  moistureVal = mapf(sensorVal, lowerInitialBound, upperInitialBound, lowerFinalBound, upperFinalbound);

  lcd.setCursor(17,2);
  brightnessSensor = analogRead(A5);
  brightnessReading = map(brightnessSensor, 0, 1023, 0, 100);
  lcd.print(brightnessReading);

  if(moistureVal>3.5) {
    lcd.setCursor(15,0);
    lcd.print(moistureVal);
    lcd.setCursor(14,1);
    lcd.print("(Good)");
    delay(100);
  }
  else {
    lcd.setCursor(15,0);
    lcd.print(moistureVal);
    lcd.setCursor(14,1);
    lcd.print("(Dry)");
    delay(100);
  }

//Serial.println(moistureVal);
delay(150);
}