/*
 * Project itp348_a4_xu_connie
 * Description: Dice
 * Author: Connie Xu
 * Date: 2/5/23
 */

const int PIN_BUTTON = D2;
const int PIN_LED1 = D3;
const int PIN_LED2 = D8;
const int PIN_LED3 = A2;
const int PIN_LED4 = D4;
const int PIN_LED5 = D7;
const int PIN_LED6 = A1;
const int PIN_LED7 = D5;
const int PIN_LED8 = D6;
const int PIN_LED9 = A0;

//gloabl vars
int LED1_STATE = LOW;
int lastButtonState = HIGH;
int currentButtonState = LOW;

//function to roll dice
void rollDice() {
  int randNum = random(1, 7);
  Serial.println(String(randNum));

  if (randNum == 1) {
    //1
    digitalWrite(PIN_LED1, LOW);
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, LOW);
    digitalWrite(PIN_LED4, LOW);
    digitalWrite(PIN_LED5, HIGH);
    digitalWrite(PIN_LED6, LOW);
    digitalWrite(PIN_LED7, LOW);
    digitalWrite(PIN_LED8, LOW);
    digitalWrite(PIN_LED9, LOW);
  }
  else if (randNum == 2) {
    //2
    digitalWrite(PIN_LED1, HIGH);
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, LOW);
    digitalWrite(PIN_LED4, LOW);
    digitalWrite(PIN_LED5, LOW);
    digitalWrite(PIN_LED6, LOW);
    digitalWrite(PIN_LED7, LOW);
    digitalWrite(PIN_LED8, LOW);
    digitalWrite(PIN_LED9, HIGH);
  }
  else if (randNum == 3) {
    //3
    digitalWrite(PIN_LED1, HIGH);
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, LOW);
    digitalWrite(PIN_LED4, LOW);
    digitalWrite(PIN_LED5, HIGH);
    digitalWrite(PIN_LED6, LOW);
    digitalWrite(PIN_LED7, LOW);
    digitalWrite(PIN_LED8, LOW);
    digitalWrite(PIN_LED9, HIGH);
  }
  else if (randNum == 4) {
    //4
    digitalWrite(PIN_LED1, HIGH);
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, HIGH);
    digitalWrite(PIN_LED4, LOW);
    digitalWrite(PIN_LED5, LOW);
    digitalWrite(PIN_LED6, LOW);
    digitalWrite(PIN_LED7, HIGH);
    digitalWrite(PIN_LED8, LOW);
    digitalWrite(PIN_LED9, HIGH);
  }
  else if (randNum == 5) {
    //5
    digitalWrite(PIN_LED1, HIGH);
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, HIGH);
    digitalWrite(PIN_LED4, LOW);
    digitalWrite(PIN_LED5, HIGH);
    digitalWrite(PIN_LED6, LOW);
    digitalWrite(PIN_LED7, HIGH);
    digitalWrite(PIN_LED8, LOW);
    digitalWrite(PIN_LED9, HIGH);
  }
  else {
    //6
    digitalWrite(PIN_LED1, HIGH);
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, HIGH);
    digitalWrite(PIN_LED4, HIGH);
    digitalWrite(PIN_LED5, LOW);
    digitalWrite(PIN_LED6, HIGH);
    digitalWrite(PIN_LED7, HIGH);
    digitalWrite(PIN_LED8, LOW);
    digitalWrite(PIN_LED9, HIGH);
  }
}

void setup() {
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
  pinMode(PIN_LED5, OUTPUT);
  pinMode(PIN_LED6, OUTPUT);
  pinMode(PIN_LED7, OUTPUT);
  pinMode(PIN_LED8, OUTPUT);
  pinMode(PIN_LED9, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);

  Serial.begin(9600);
}

void loop() {
  //read button
  int currentButtonState = digitalRead(PIN_BUTTON);

  if (currentButtonState == HIGH && lastButtonState == LOW) {  
    rollDice();
    delay(2000);
  }
  else {
    //off
    digitalWrite(PIN_LED1, LOW);
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, LOW);
    digitalWrite(PIN_LED4, LOW);
    digitalWrite(PIN_LED5, LOW);
    digitalWrite(PIN_LED6, LOW);
    digitalWrite(PIN_LED7, LOW);
    digitalWrite(PIN_LED8, LOW);
    digitalWrite(PIN_LED9, LOW);
  }

  lastButtonState = currentButtonState;
}