/*
 * Project week6cont_20231
 * Description: Blynk App ZeRGBa Lab
 * Author: Connie Xu
 * Date: 2/15/23
 */

// individual
#define BLYNK_TEMPLATE_ID "TMPLppzIOyLk"
#define BLYNK_TEMPLATE_NAME "Week6Lab"
#define BLYNK_AUTH_TOKEN "deEY9E6rJ6XyntMuIzZ52wIrSQ89kbr-"

// same
#define BLYNK_PRINT Serial
#define BLYNK_IP IPAddress(64, 225, 16, 22)
#include <blynk.h>

const int PIN_LED = D7;
const int PIN_RED = D3;
const int PIN_GREEN = D4;
const int PIN_BLUE = D5;
const int PIN_SWITCH = D2;

unsigned long blynkUpdateInterval = 1000;
unsigned long prevBlynkMillis = 0;

// app to argon
BLYNK_WRITE(V0) // red
{
    int redVal = param.asInt();
    analogWrite(PIN_RED, redVal);
}

BLYNK_WRITE(V1) // green
{
    int greenVal = param.asInt();
    analogWrite(PIN_GREEN, greenVal);
}

BLYNK_WRITE(V2) // blue
{
    int blueVal = param.asInt();
    analogWrite(PIN_BLUE, blueVal);
}

BLYNK_WRITE(V4)
{
    int buttonVal = param.asInt();

    if (buttonVal == 1)
    {
        int randNum = random(0, 4); // 0-3
        if (randNum == 0)
        {
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 255);
            Blynk.virtualWrite(V7, "white");
        }
        else if (randNum == 1)
        {
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 0);
            Blynk.virtualWrite(V7, "yellow");
        }
        else if (randNum == 2)
        {
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 255);
            Blynk.virtualWrite(V7, "magenta");
        }
        else if (randNum == 3)
        {
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 0);
            Blynk.virtualWrite(V7, "red");
        }
    }
}

void setup()
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);

    delay(5000);                             // gives time to connect to device
    Blynk.begin(BLYNK_AUTH_TOKEN, BLYNK_IP); // init setup

    // Blynk.syncAll();
}

// argon to app
void loop()
{
    Blynk.run(); // refreshes app

    unsigned long curMillis = millis();

    if (curMillis - prevBlynkMillis > blynkUpdateInterval)
    {
        // send data to blynk here
        prevBlynkMillis = curMillis;
        int switchVal = digitalRead(PIN_SWITCH);
        if (switchVal == HIGH)
        {
            Blynk.virtualWrite(V3, "open");
        }
        else
        {
            Blynk.virtualWrite(V3, "closed");
        }
    }
}