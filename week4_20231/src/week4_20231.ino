/*
 * Project week4_20231
 * Description: Photoresistors Lab
 * Author: Connie Xu
 * Date: 1/30/23
 */

const int PIN_PHOTORESISTOR = A5;
const int PIN_RGB_RED = D2;
const int PIN_RGB_GREEN = D3;
const int PIN_RGB_BLUE = D4;

// global var
int brightnessLevel = 0;

// const
const int THRESHOLD_DARK = 1200;
const int THRESHOLD_AMBIENT = 2500;

// function to change led color based on lighting
void changeLedColor(int r, int g, int b)
{
  analogWrite(PIN_RGB_RED, r);
  analogWrite(PIN_RGB_GREEN, g);
  analogWrite(PIN_RGB_BLUE, b);
}

void setup()
{
  pinMode(PIN_PHOTORESISTOR, INPUT);
  pinMode(PIN_RGB_RED, OUTPUT);
  pinMode(PIN_RGB_GREEN, OUTPUT);
  pinMode(PIN_RGB_BLUE, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  brightnessLevel = analogRead(PIN_PHOTORESISTOR);
  Serial.println("brightness: " + String(brightnessLevel));

  if (brightnessLevel >= 0 && brightnessLevel <= THRESHOLD_DARK)
  {
    Serial.println("dark");
    Particle.publish("Light quality", "dark");
    changeLedColor(0, 0, 0);
  }
  else if (brightnessLevel > THRESHOLD_DARK && brightnessLevel <= THRESHOLD_AMBIENT)
  {
    Serial.println("ambient");
    Particle.publish("Light quality", "ambient");
    changeLedColor(255, 255, 0);
  }
  else
  {
    Serial.println("bright");
    Particle.publish("Light quality", "bright");
    changeLedColor(255, 255, 255);
  }

  // delay(10000);
  delay(5000);
}