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

void lcdSleepWake () {
  switch (lcdIndex) {
    case 'A':
    lcdIndex = 'B';
    break;

    case 'B':
    lcdIndex = 'A';
    break;
  }
}

void lcdRefresh () {
  lcd.setCursor(0,0);
  lcd.print("Soil M: ");
  lcd.setCursor(0,1);
  lcd.print("Soil Type: ");
  lcd.setCursor(0,2);
  lcd.print("Temp: ");
  lcd.setCursor(12, 2);
  lcd.print("Sun: ");
  lcd.setCursor(0,3);
  lcd.print("RH: ");
}

void setup() {
  pinMode (lcdRelayPin, OUTPUT);
  digitalWrite(lcdRelayPin, HIGH);
//  Serial.begin(9600); //Only enable for logging purposes
//This point downward sets the UI for the LCD
  dht.begin();
  lcdRefresh();
//  lcd.setCursor(14, 3); Theres no reason to set this as the LCD will be off
//  lcd.print("On");
  //Creating pin interrupts
  attachInterrupt(digitalPinToInterrupt(buttonPin), lcdSleepWake, RISING);
  delay(50);
  lcd.begin(lcdColumns,lcdRows);
}

void loop() {
  //DHT22 stuffs
  dht.temperature();
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  lcd.setCursor(6, 2);
  lcd.print(event.temperature);
  dht.humidity().getEvent(&event);
  lcd.setCursor(4,3);
  lcd.print(event.relative_humidity);
  sensorVal = analogRead(A0);
  moistureVal = mapf(sensorVal, lowerInitialBound, upperInitialBound, lowerFinalBound, upperFinalbound);
  //Brightness sensor stuffs
  lcd.setCursor(17,2);
  brightnessSensor = analogRead(A5);
  brightnessReading = map(brightnessSensor, 0, 1023, 0, 100);
  lcd.print(brightnessReading);
  //Soil Moisture sensor stuffs (Thanks Kulani!)
  if(moistureVal>3.5) {
    lcd.setCursor(8,0);
    lcd.print(moistureVal);
    lcd.setCursor(13,0);
    lcd.print("(Good)");
    delay(100);
  }
  else {
    lcd.setCursor(8,0);
    lcd.print(moistureVal);
    lcd.setCursor(13,0);
    lcd.print("(Dry)  ");
    delay(100);
  }
  if (lcdIndex == 'A') {
  digitalWrite(lcdRelayPin, HIGH);
  lcdRefresh();
  }
  else {
    digitalWrite(lcdRelayPin, LOW);
  }


/*
//For logging stuffs in le terminal
Serial.print(lcdIndex);
Serial.print(event.temperature);
Serial.println("*C");
Serial.println(moistureVal);
Serial.print(event.relative_humidity);
Serial.println("%");
*/
delay(150);
}