/*
This file aims to simplify the process of setting pins by exposing an easily understandable config
/

//LCD Config
#define lcdReset 0
#define lcdEnable 1
#define lcdDS4 2
#define lcdDS5 3
#define lcdDS6 4
#define lcdDS7 5
#define lcdColumns 20
#define lcdRows 4

//Soil Moisture Thresholds
float lowerInitialBound 652; //kind of a weird oxymoron but ima ignore that
float upperInitialBound 336;
float lowerFinalBound 2.6;
float upperFinalbound 6.1;

float fromLow = 652;
float fromHigh = 336;
float toLow = 2.6;
float toHigh = 6.1;
float sensorVal;
float moistureVal;


/*
TODO:
Move soil moisture thresholds to a menu that is configurable on the arduino
*/