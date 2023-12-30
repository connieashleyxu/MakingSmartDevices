/*
 * Project itp348_a12_xu_connie
 * Description: Final Project - DIY Sunset Lamp
 * Author: Connie Xu
 * Date: 5/5/23
 */

// Initial State web app access key
// https://groker.init.st/api/events?accessKey=ist_SuQ5B6oyhqeWIA4-GBNsC46wvxamxK25&bucketKey=V9YHDAKPV3FC

// Blynk mobile app
#define BLYNK_TEMPLATE_ID "TMPLK7Er6NAh"
#define BLYNK_TEMPLATE_NAME "FinalProject"
#define BLYNK_AUTH_TOKEN "QN91iC7Bn_mZ2CbeX8KR9_XYgGiTuHbb"
#define BLYNK_PRINT Serial
#define BLYNK_IP IPAddress(64, 225, 16, 22)
#include <blynk.h>

// DHT22 temperature
#include "DHT20.h"
DHT20 dht;

const unsigned long INTERVAL_PUBLISH = 2500;
unsigned long prevMillis = 0;

// RGB LED
const int PIN_RED = D2;
const int PIN_GREEN = D3;
const int PIN_BLUE = D4;

// button
const int PIN_BUTTON = D5;

// potentiometer
const int PIN_POT = A0;

// photoresistor
const int PIN_PHOTORESISTOR = A5;

// GLOBAL VARIABLES
////////////////////////////////////////////////////////////////////////
//  variables for button
int curButtonVal = HIGH;
int prevButtonVal = HIGH;
int modeSequence = 0; // 0 is off, 1 is mode 1, 2 is mode 2, and 3 is mode 3
String modeSequenceName = "0: Off";
bool isOn; // is the lamp on

// variables for lamp color
int redVal;
int greenVal;
int blueVal;

// array for mode 3: random color change
String randColor[] = {"red", "rose", "magenta", "violet", "blue", "azure", "cyan", "aquamarine", "green", "chartreuse", "yellow", "orange"};

// variable for photoresistor
int brightnessLevel;
// constant for photoresistor thresholds
const int THRESHOLD_DARK = 1200;
const unsigned long INTERVAL_PHOTO = 5000;

// variables for Blynk
unsigned long blynkUpdateInterval = 1000;
unsigned long prevBlynkMillis = 0;
////////////////////////////////////////////////////////////////////////

// FUNCTIONS
////////////////////////////////////////////////////////////////////////
// function to display RGB LED color for mode 1: single color light
void displayColor(int r, int g, int b)
{
  redVal = r;
  greenVal = g;
  blueVal = b;

  digitalWrite(PIN_RED, r);
  digitalWrite(PIN_GREEN, g);
  digitalWrite(PIN_BLUE, b);
}

// function to display random RGB LED color for mode 3: random color changing light
void displayRandomColor()
{
  // int r = random(0, 256);
  // int b = random(0, 256);
  // int g = random(0, 256);

  // Serial.println("Random Red: " + String(r));
  // Serial.println("Random Green: " + String(g));
  // Serial.println("Random Blue: " + String(b));

  int i = random(0, 13);

  if (randColor[i] == "red")
  {
    displayColor(255, 0, 0);
  }
  else if (randColor[i] == "rose")
  {
    displayColor(255, 0, 127);
  }
  else if (randColor[i] == "magenta")
  {
    displayColor(255, 0, 255);
  }
  else if (randColor[i] == "violet")
  {
    displayColor(127, 0, 255);
  }
  else if (randColor[i] == "blue")
  {
    displayColor(0, 0, 255);
  }
  else if (randColor[i] == "azure")
  {
    displayColor(0, 127, 255);
  }
  else if (randColor[i] == "cyan")
  {
    displayColor(0, 255, 255);
  }
  else if (randColor[i] == "aquamarine")
  {
    displayColor(0, 255, 127);
  }
  else if (randColor[i] == "green")
  {
    displayColor(0, 255, 0);
  }
  else if (randColor[i] == "chartreuse")
  {
    displayColor(127, 255, 0);
  }
  else if (randColor[i] == "yellow")
  {
    displayColor(255, 255, 0);
  }
  else if (randColor[i] == "orange")
  {
    displayColor(255, 127, 0);
  }
  else
  {
    displayColor(255, 255, 255); // white
  }

  Serial.println(String(randColor[i]));

  delay(2000);
}

// function to display color based on temperature for mode 2: ambient color changing light
void displayTempColor()
{
  //  DHT temperature
  int status = dht.read();

  // only publish temperature to Initial State when mode 2 is active
  unsigned long currMillis = millis();
  if (currMillis - prevMillis > INTERVAL_PUBLISH)
  {
    Particle.publish("temperature", String(dht.getTemperature()));
    prevMillis = currMillis;
  }

  Serial.println("DHT Temp: " + String(dht.getTemperature()));

  if (status == DHT20_OK)
  { // valid read
    if (dht.getTemperature() < 16)
    {
      displayColor(0, 0, 255); // blue
    }
    else if (dht.getTemperature() >= 16 && dht.getTemperature() < 20)
    {
      displayColor(0, 255, 255); // blue green (cyan)
    }
    else if (dht.getTemperature() >= 20 && dht.getTemperature() <= 22)
    {
      displayColor(255, 255, 0); // yellow
    }
    else if (dht.getTemperature() >= 22)
    {
      displayColor(255, 0, 0); // red
    }
  }
  else
  {
    Serial.println("Invalid read");
  }

  delay(1000);
}

// Blynk on/off button widget
BLYNK_WRITE(V7)
{
  int buttonVal = param.asInt();

  Serial.println("Blynk Button: " + String(buttonVal));

  if (buttonVal == HIGH)
  {
    isOn = true;
  }
  else
  {
    isOn = false;
    modeSequence = 0;
    modeSequenceName = "0: Off";
    displayColor(0, 0, 0);
  }
}

// Blynk zeRGBa widget
BLYNK_WRITE(V0) // red
{
  redVal = param.asInt();

  if (modeSequence == 1)
  {
    digitalWrite(PIN_RED, redVal);

    Serial.println("Blynk Red: " + String(redVal));
  }
}

BLYNK_WRITE(V1) // green
{
  greenVal = param.asInt();

  if (modeSequence == 1)
  {
    digitalWrite(PIN_GREEN, greenVal);

    Serial.println("Blynk Green: " + String(greenVal));
  }
}

BLYNK_WRITE(V2) // blue
{
  blueVal = param.asInt();

  if (modeSequence == 1)
  {
    digitalWrite(PIN_BLUE, blueVal);

    Serial.println("Blynk Blue: " + String(blueVal));
  }
}
////////////////////////////////////////////////////////////////////////

void setup()
{
  dht.begin();

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);

  pinMode(PIN_BUTTON, INPUT);

  pinMode(PIN_POT, INPUT);

  pinMode(PIN_PHOTORESISTOR, INPUT);

  Serial.begin(9600);

  delay(1000);

  Blynk.begin(BLYNK_AUTH_TOKEN, BLYNK_IP);
}

void loop()
{
  // button to change mode if lamp is on
  if (isOn == true)
  {
    curButtonVal = digitalRead(PIN_BUTTON);

    if (prevButtonVal == HIGH && curButtonVal == LOW)
    {
      // lamp modes
      modeSequence = (modeSequence + 1) % 4;
      Serial.println("Mode: " + String(modeSequence));

      if (modeSequence == 0)
      { // off
        displayColor(0, 0, 0);
        modeSequenceName = "0: Off";
      }
      else if (modeSequence == 1)
      { // mode 1: single color light
        displayColor(255, 0, 0);
        modeSequenceName = "1: Single Color";
      }
      else if (modeSequence == 2)
      { // mode 2: ambient color changing light (based on temperature)
        displayColor(0, 0, 255);
        modeSequenceName = "2: Ambient Color";
      }
      else if (modeSequence == 3)
      { // mode 3: random color changing light
        displayColor(0, 255, 0);
        modeSequenceName = "3: Random Color";
      }
    }

    prevButtonVal = curButtonVal;

    // potentiometer to change brightness
    int potVal = analogRead(PIN_POT);
    int pwmVal = map(potVal, 0, 4095, 0, 255);
    float brightness = float(pwmVal) / 255.0;

    digitalWrite(PIN_RED, redVal * brightness);
    digitalWrite(PIN_GREEN, greenVal * brightness);
    digitalWrite(PIN_BLUE, blueVal * brightness);

    // Serial.println("Potentiometer: " + String(potVal));
    // Serial.println("Pot Brightness: " + String(brightness));
  }
  else
  { // button to change mode is off
    modeSequence = 0;
    displayColor(0, 0, 0);
  }

  if (modeSequence == 2)
  { // mode 2: ambient color changing light (based on temperature)
    Serial.println("display temp color called");
    displayTempColor();
  }

  if (modeSequence == 3)
  { // mode 3: random color changing light
    Serial.println("display rand color called");
    displayRandomColor();
  }

  // photoresistor to turn on lamp when dark
  unsigned long currMillis = millis();
  if (currMillis - prevMillis > INTERVAL_PHOTO)
  {
    prevMillis = currMillis;
    brightnessLevel = analogRead(PIN_PHOTORESISTOR);
    Serial.println("Photoresistor: " + String(brightnessLevel));

    if (brightnessLevel >= 0 && brightnessLevel <= THRESHOLD_DARK)
    { // dark
      isOn = true;
      Serial.println("Photoresistor is on.");
    }
  }

  // Blynk app
  Blynk.run();

  unsigned long curMillis = millis();
  if (curMillis - prevBlynkMillis > blynkUpdateInterval)
  {
    // data sent from argon to Blynk app
    Blynk.virtualWrite(V6, modeSequenceName);
    Blynk.virtualWrite(V7, isOn);
    prevBlynkMillis = curMillis;
  }
}