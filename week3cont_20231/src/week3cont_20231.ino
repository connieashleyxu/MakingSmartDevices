/*
 * Project week3cont_20231
 * Description: Week 3 Day 2 Lab
 * Author: Connie Xu
 * Date: 1/25/23
 */

const int PIN_RED = D2;
const int PIN_GREEN = D3;
const int PIN_BLUE = D4;
const int PIN_BUTTON = D5;

//global vars
//store current and prev button vals
int curButtonVal = HIGH;
int prevButtonVal = HIGH;

//counter has to be a global var
int counter = 0;
bool redOn = false;

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  Serial.begin(9600);
}

void loop() {
  //V1
  //read button (digital because either on/off)
  // int buttonVal = digitalRead(PIN_BUTTON);
  // Serial.println("Button value = " + String(buttonVal));
  // delay(100);

  // //turn red LEB on only while button pressed
  // if (buttonVal == HIGH) {
  //   digitalWrite(PIN_RED, LOW);
  // }
  // else {
  //   digitalWrite(PIN_RED, HIGH);
  // }

  //V2
  //toggle red LED on/off after each time button is pressed
  //read button
  curButtonVal = digitalRead(PIN_BUTTON);

  //looking for falling edge -- press down
  // if (prevButtonVal == HIGH && curButtonVal == LOW) { //button pressed
  //   //need to know if light is on or off
  //   counter = counter + 1;
  //   Serial.println("button presses " + String(counter));

  //   if (redOn == true) { //red light is on
  //     redOn = false; //change state
  //     digitalWrite(PIN_RED, LOW);
  //   }
  //   else { //red light is off
  //     redOn = true;
  //     digitalWrite(PIN_RED, HIGH);
  //   }
  // }
  // prevButtonVal = curButtonVal;

  //V3
  //generate 1 new random color each time button is pressed
  // if (prevButtonVal == HIGH && curButtonVal == LOW) { //button pressed
  //   if (redOn == true){ //red light on
  //     redOn = false;
  //     digitalWrite(PIN_RED, LOW);
  //     digitalWrite(PIN_GREEN, LOW);
  //     digitalWrite(PIN_BLUE, LOW);
  //   }

  //   else { //red light is off
  //     redOn = true;
  //     analogWrite(PIN_RED, rand() % 255 + 0);
  //     analogWrite(PIN_GREEN, rand() % 255 + 0);
  //     analogWrite(PIN_BLUE, rand() % 255 + 0);
  //   }
  // }

  //V4
  //make each button press move LED through a sequence of colors
  if (prevButtonVal == HIGH && curButtonVal == LOW) { //button pressed
    if (redOn == true){ //red light on
        redOn = false;
        digitalWrite(PIN_RED, LOW);
        digitalWrite(PIN_GREEN, LOW);
        digitalWrite(PIN_BLUE, LOW);
      }

      else { //red light is off
        redOn = true;
        analogWrite(PIN_RED, rand() % 255 + 0);
        analogWrite(PIN_GREEN, rand() % 255 + 0);
        analogWrite(PIN_BLUE, rand() % 255 + 0);
        delay(100);
        analogWrite(PIN_RED, rand() % 255 + 0);
        analogWrite(PIN_GREEN, rand() % 255 + 0);
        analogWrite(PIN_BLUE, rand() % 255 + 0);
        delay(100);
        analogWrite(PIN_RED, rand() % 255 + 0);
        analogWrite(PIN_GREEN, rand() % 255 + 0);
        analogWrite(PIN_BLUE, rand() % 255 + 0);
      }
  }   
}