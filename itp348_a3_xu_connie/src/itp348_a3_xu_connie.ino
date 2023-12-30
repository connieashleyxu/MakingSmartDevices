/*
 * Project itp348_a3_xu_connie
 * Description: Scanning Light Homework 3
 * Author: Connie Xu
 * Date: 1/29/23
 */

// create a global const to represent each pin in project
const int PIN_POT = A0;
const int PIN_LED1 = D2;
const int PIN_LED2 = D3;
const int PIN_LED3 = D4;
const int PIN_LED4 = D5;
const int PIN_LED5 = D6;

//global var to store LEDs
int Leds[5] = {PIN_LED1, PIN_LED2, PIN_LED3, PIN_LED4, PIN_LED5};

//function to flash LEDs
void flashLed (int led, float p) {
    analogWrite(led, 255 - p);
    delay(p);
    analogWrite(led, 0);
    delay(p);

    Serial.println("LED PIN: " + String(led));
    Serial.println("delay: " + String(p));
    Serial.println("brightness: " + String(255 - p));
}

void setup() {
  pinMode(PIN_POT, INPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
  pinMode(PIN_LED5, OUTPUT);
  Serial.begin(9600);
}

// infinite loop
void loop() {
  int potVal = analogRead(PIN_POT);
  float pwm = float(potVal) / 16.2 + 2; // dimmest will be 2

  // 0 - 3.3v analog
  // 0 - 4095 voltage

  int counter = 0;

  if(counter >= 0 && counter < 5) {
    for(int i = 0; i < 5; i++) {
      counter++;
      flashLed(Leds[i], pwm);

      Serial.println("counter++: " + String(counter));
    }
  }  

  if(counter >= 5) { // loop back and forth
    for(int i = 4; i > -1; i--) {
      counter--;
      flashLed(Leds[i], pwm);

      Serial.println("counter--: " + String(counter));
    }
  }  

  // for(int i = 0; i < 5; i++) {
  //   flashLed(Leds[i], pwm);
  //   for(i = 4; i > -1; i--) {
  //     flashLed(Leds[i], pwm);
  //   }
  // }

}