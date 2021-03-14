#include <LiquidCrystal.h>
#include <config.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

int brightnessSensor;
int brightnessReading;

LiquidCrystal lcd(lcdReset, lcdEnable, lcdDS4, lcdDS5, lcdDS6, lcdDS7);
DHT_Unified dht(DHTPIN, DHTTYPE);

//got this one off the forums
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

class backlitLCD
{
  static const int amountOfScreens = 8; //amount of screens from 0 to n
  int initialScreen = 0;
  String screens[amountOfScreens] = {
      "mainScreen",
      "screenSelect",
      "claySoil",
      "loamySoil",
      "sandySoil",
      "soilSetup",
      "customSoil1",
      "otherData"
      };

public:
  void updateMenu()
  {
  };

private:
  void lcdMain()
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Soil M: ");
    lcd.setCursor(0, 1);
    lcd.print("Soil Type: ");
    lcd.setCursor(0, 2);
    lcd.print("Temp: ");
    lcd.setCursor(12, 2);
    lcd.print("Sun: ");
    lcd.setCursor(0, 3);
    lcd.print("RH: ");
  };
};

void
setup()
{
  pinMode(lcdRelayPin, OUTPUT);
  digitalWrite(lcdRelayPin, HIGH);
  //Serial.begin(9600); //Only enable for logging purposes
  dht.begin();
  lcd.begin(lcdColumns, lcdRows);
  //Creating pin interrupts
  // attachInterrupt(digitalPinToInterrupt(buttonPin), lcdSleepWake, RISING); //come back to this later
  // attachInterrupt(digitalPinToInterrupt(encoderPin), updateMenu, RISING);  //come back to this later
}

void loop()
{
  backlitLCD mainLCD;

  
  //DHT22 stuffs
  dht.temperature();
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  lcd.setCursor(6, 2);
  lcd.print(event.temperature);
  dht.humidity().getEvent(&event);
  lcd.setCursor(4, 3);
  lcd.print(event.relative_humidity);
  sensorVal = analogRead(A0);
  moistureVal = mapf(sensorVal, lowerInitialBound, upperInitialBound, lowerFinalBound, upperFinalbound);
  //Brightness sensor stuffs
  lcd.setCursor(17, 2);
  brightnessSensor = analogRead(A5);
  brightnessReading = map(brightnessSensor, 0, 1023, 0, 100);
  lcd.print(brightnessReading);
  //Soil Moisture sensor stuffs (Thanks Kulani!)
  if (moistureVal > moistureThreshold)
  {
    lcd.setCursor(8, 0);
    lcd.print(moistureVal);
    lcd.setCursor(13, 0);
    lcd.print("(Good)");
    delay(100);
  }
  else
  {
    lcd.setCursor(8, 0);
    lcd.print(moistureVal);
    lcd.setCursor(13, 0);
    lcd.print("(Dry)  ");
    delay(100);
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