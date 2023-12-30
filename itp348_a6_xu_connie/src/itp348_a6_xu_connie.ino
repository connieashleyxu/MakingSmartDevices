/*
 * Project itp348_a6_xu_connie
 * Description: Environment Monitor and Dashboard
 * Author: Connie Xu
 * Date: 2/19/23
 */

#include "DHT20.h"
#include "SparkFunMicroOLED.h"

DHT20 dht;
MicroOLED oled(MODE_I2C, 9, 1);

const int PIN_BUTTON = D2;

// global vars
int prevButtonState = HIGH;

int buttonPresses = 0;

float highTemp = 0.0;
float lowTemp = 0.0;
float highHum = 0.0;
float lowHum = 0.0;

const unsigned long INTERVAL_PUBLISH = 2500;
unsigned long prevMillis = 0;

enum Display
{
  current,
  history
};

void setup()
{
  dht.begin();

  oled.begin();
  oled.clear(ALL);
  oled.display();

  Serial.begin(9600);

  delay(1000);

  oled.clear(PAGE);

  pinMode(PIN_BUTTON, INPUT);
}

void loop()
{
  int currButtonState = digitalRead(PIN_BUTTON);
  int stat = dht.read();
  Display status = current;

  if (highTemp <= dht.getTemperatureF())
  {
    highTemp = dht.getTemperatureF();
  }

  if (lowTemp == 0.0)
  {
    lowTemp = dht.getTemperatureF();
  }
  else if (lowTemp >= dht.getTemperatureF())
  {
    lowTemp = dht.getTemperatureF();
  }

  if (highHum <= dht.getHumidity())
  {
    highHum = dht.getHumidity();
  }

  if (lowHum == 0.0)
  {
    lowHum = dht.getHumidity();
  }
  else if (lowHum >= dht.getHumidity())
  {
    lowHum = dht.getHumidity();
  }

  if (currButtonState == LOW && prevButtonState == HIGH)
  {
    if (buttonPresses == 0)
    {
      status = current;
    }
    else if (buttonPresses == 1)
    {
      status = history;
    }

    Serial.println(String(status));

    if (status == current)
    {
      Serial.println("entered current");
      Serial.println(String(stat));
      Serial.println("dht20: " + String(DHT20_OK));
      if (0 == DHT20_OK) // if (stat == DHT20_OK)
      {
        Serial.println("Temp");
        Serial.println(String(dht.getTemperatureF()) + " F");
        Serial.println("Hum");
        Serial.println(String(dht.getHumidity()) + " %");

        oled.setCursor(0, 0);
        oled.setFontType(0);

        oled.println("Temp");
        oled.println(String(dht.getTemperatureF(), 1) + " F");
        oled.println("Hum");
        oled.println(String(dht.getHumidity(), 1) + " %");

        oled.display();

        oled.clear(PAGE);
      }
      else
      {
        Serial.println("Invalid read");
      }

      if (buttonPresses == 0)
      {
        buttonPresses++;
        Serial.println("button read: " + String(buttonPresses));
      }
      else if (buttonPresses == 1)
      {
        buttonPresses--;
        Serial.println("button read: " + String(buttonPresses));
      }

      // delay(1000);
    }
    else if (status == history)
    {
      Serial.println("entered history");
      if (0 == DHT20_OK) // if (stat == DHT20_OK)
      {
        oled.setCursor(0, 0);
        oled.setFontType(0);

        Serial.println("Temp");
        Serial.println("H: " + String(highTemp, 1) + " F");
        Serial.println("L: " + String(lowTemp, 1) + " F");
        Serial.println("Hum");
        Serial.println("H: " + String(highHum, 0) + " %");
        Serial.println("L: " + String(lowHum, 0) + " %");

        oled.println("Temp");
        oled.println("H: " + String(highTemp, 1) + " F");
        oled.println("L: " + String(lowTemp, 1) + " F");
        oled.println("Hum");
        oled.println("H: " + String(highHum, 0) + " %");
        oled.println("L: " + String(lowHum, 0) + " %");

        oled.display();

        oled.clear(PAGE);
      }
      else
      {
        Serial.println("Invalid read");
      }

      if (buttonPresses == 0)
      {
        buttonPresses++;
        Serial.println("button read: " + String(buttonPresses));
      }
      else if (buttonPresses == 1)
      {
        buttonPresses--;
        Serial.println("button read: " + String(buttonPresses));
      }
      // delay(1000);
    }
  }
  prevButtonState = currButtonState;

  unsigned long currMillis = millis();
  if (currMillis - prevMillis > INTERVAL_PUBLISH)
  {
    Particle.publish("temp", String(dht.getTemperatureF()));
    Particle.publish("hum", String(dht.getHumidity()));
    prevMillis = currMillis;
  }
}