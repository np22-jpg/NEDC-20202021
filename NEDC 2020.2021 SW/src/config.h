/*
This file aims to simplify the process of setting pins by exposing an easily understandable config
*/

//LCD Config
//protip: It's a really bad idea to use pins 0 and 1 when using Serial
#define lcdReset 8
#define lcdEnable 9
#define lcdDS4 4
#define lcdDS5 5
#define lcdDS6 6
#define lcdDS7 7
#define lcdColumns 20
#define lcdRows 4
#define buttonPin 2
#define lcdRelayPin 11
#define encoderPin 3

//DHT Config
#define DHTPIN 12
#define DHTTYPE 22

//Soil Moisture Thresholds
float lowerInitialBound = 652; //kind of a weird oxymoron but ima ignore that
float upperInitialBound = 336; //I can't come up with better naming pls help
float lowerFinalBound = 2.6;
float upperFinalbound = 6.1;
int sensorVal;
float moistureVal;
float moistureThreshold = 3.5;

/*
float fromLow = 652;
float fromHigh = 336;
float toLow = 2.6;
float toHigh = 6.1;
float sensorVal;
float moistureVal;
keeping this here since idk if the stuff I referenced/created actually works or not
*/

/*
TODO:
Move soil moisture thresholds to a menu that is configurable on the arduino
Get a DHT22 that actually works
*/

//no touchie, will break literally everything
char lcdIndex = 'A';
char soilType = 'A';
