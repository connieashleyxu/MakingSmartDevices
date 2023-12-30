/*
 * Project week11_20231
 * Description: OLET + Ultrasonic Lab
 * Author: Connie Xu
 * Date: 5/29/23
 */

#include "SparkFunMicroOLED.h"
#include "bitmaps.h"

#define PIN_RESET 9
#define DC_JUMPER 1

MicroOLED oled(MODE_I2C, PIN_RESET, DC_JUMPER);

double SPEED_SOUND_CM_ROOM_TEMP_FAHR = 0.03444;
double CONV_FACTOR_CM_TO_IN = 0.3437;
int MAX_RANGE_CM = 78;
int MIN_RANGE_CM = 0;
int WARNING_RANGE_CM = 12;
const int PIN_TRIGGER = D6;
const int PIN_ECHO = D5;
double distanceCm;
double distanceIn;

void setup()
{
  Serial.begin(9600);
  oled.begin();
  oled.clear(ALL);
  oled.drawBitmap(itp348_bmp);
  oled.display();
  delay(1000);
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop()
{
  measureDistance();
  updateOLED();
  delay(500);
}

void measureDistance()
{
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);
  int timeRoundTrip = pulseIn(PIN_ECHO, HIGH);
  distanceCm = timeRoundTrip * SPEED_SOUND_CM_ROOM_TEMP_FAHR / 2;
  distanceIn = distanceCm * CONV_FACTOR_CM_TO_IN;
}

void updateOLED()
{
  Serial.print("Dist to object:");
  if (distanceCm >= MAX_RANGE_CM ||
      distanceCm <= MIN_RANGE_CM)
  {
    Serial.print("out of range: " + String(distanceIn, 2) + " in");
    oled.clear(PAGE);
    oled.drawBitmap(no_bmp);
    oled.display();
  }
  else if (distanceCm > 0 && distanceCm < WARNING_RANGE_CM)
  {
    Serial.print("Warning: " + String(distanceIn, 2) + " in");
    oled.clear(PAGE);
    oled.drawBitmap(warning_bmp_320x240);
    oled.setFontType(0);
    oled.setCursor(0, 40);
    oled.print(String(distanceIn, 2) + " in");
    oled.display();
  }
  else
  {
    Serial.print("OK distance: " + String(distanceIn, 2) + " in");
    oled.clear(PAGE);
    oled.drawBitmap(yes_bmp_320x240);
    oled.setFontType(0);
    oled.setCursor(0, 40);
    oled.print(String(distanceIn, 2) + " in");
    oled.display();
  }

  Serial.println();
}