/*
 * Project itp348_a2_xu_connie
 * Description: Assignment 2: Light Sculpture
 * Author: Connie Xu
 * Date: 01/18/22
 */

// create a global const to represent each pin in project
const int PIN_LED1 = D2;
const int PIN_LED2 = D3;
const int PIN_LED3 = D4;
const int PIN_LED4 = D5;
const int PIN_LED5 = D6;

// this happens JUST ONCE
// configure serial monitor, setup pin modes
void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
  pinMode(PIN_LED5, OUTPUT);
}

// infinite loop
void loop() {
  analogWrite(PIN_LED1, 0); // off
  delay(500);
  analogWrite(PIN_LED1, 127); // half bright
  delay(500);
  analogWrite(PIN_LED1, 255); // full bright
  delay(500);
  
  analogWrite(PIN_LED2, 0); // off
  delay(500);
  analogWrite(PIN_LED2, 127); // half bright
  delay(500);
  analogWrite(PIN_LED2, 255); // full bright
  delay(500);

  analogWrite(PIN_LED3, 0); // off
  delay(500);
  analogWrite(PIN_LED3, 127); // half bright
  delay(500);
  analogWrite(PIN_LED3, 255); // full bright
  delay(500);

  analogWrite(PIN_LED4, 0); // off
  delay(500);
  analogWrite(PIN_LED4, 127); // half bright
  delay(500);
  analogWrite(PIN_LED4, 255); // full bright
  delay(500);

  analogWrite(PIN_LED5, 0); // off
  delay(500);
  analogWrite(PIN_LED5, 127); // half bright
  delay(500);
  analogWrite(PIN_LED5, 255); // full bright
  delay(500);
  
}