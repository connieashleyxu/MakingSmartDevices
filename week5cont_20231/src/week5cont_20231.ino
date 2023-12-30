/*
 * Project week5cont_20231
 * Description: Etch a Sketch
 * Author: Connie Xu
 * Date: 2/8/23
 */

#include "SparkFunMicroOLED.h"

MicroOLED oled(MODE_I2C, 9, 1);

const int PIN_BUTTON = D2;
const int PIN_POT0 = A0;
const int PIN_POT1 = A1;

int buttonVal;

int xPos = 0;
int yPos = 0;

const int X_MAX = oled.getLCDWidth();
const int Y_MAX = oled.getLCDHeight();

void setup()
{
  Serial.begin(9600);

  oled.begin();
  oled.clear(ALL);
  oled.display();
  delay(1000);
  oled.clear(PAGE);

  xPos = oled.getLCDWidth() / 2;
  yPos = oled.getLCDHeight() / 2;

  pinMode(PIN_BUTTON, INPUT);
}

void loop()
{
  int xValue = analogRead(PIN_POT0);
  int yValue = analogRead(PIN_POT1);

  xPos = map(xValue, 0, 4095, 0, X_MAX);
  yPos = map(yValue, 0, 4095, 0, Y_MAX);

  if (xPos > X_MAX)
  {
    xPos = X_MAX;
  }
  if (xPos < 0)
  {
    xPos = 0;
  }

  if (yPos > Y_MAX)
  {
    yPos = Y_MAX;
  }
  if (yPos < 0)
  {
    yPos = 0;
  }

  oled.pixel(xPos, yPos);
  oled.display();

  buttonVal = digitalRead(PIN_BUTTON);
  if (buttonVal == LOW)
  {
    Serial.println("button clicked");
    oled.clear(PAGE);
  }
}