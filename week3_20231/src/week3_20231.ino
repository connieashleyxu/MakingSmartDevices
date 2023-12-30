/*
 * Project week3_20231
 * Description: Week 3 In-Class Exercise
 * Author: Connie Xu
 * Date: 1/23/23
 */

const int PIN_RED = D2;
const int PIN_GREEN = D3;
const int PIN_BLUE = D4;
const int PIN_POT = A0;

//function
void changeRgbColor(int r, int g, int b) {
  analogWrite(PIN_RED, r);
  analogWrite(PIN_GREEN, g);
  analogWrite(PIN_BLUE, b);
}

void changeRgbColorString(String color) {
  if(color.toLowerCase() == "red") {
    changeRgbColor(255, 0, 0);
  }
  else if(color.toLowerCase() == "green") {
    changeRgbColor(0, 255, 0);
  }
  else if(color.toLowerCase() == "blue") {
    changeRgbColor(0, 0, 255);
  }
  else if(color.toLowerCase() == "magenta") {
    changeRgbColor(255, 0, 255);
  }
  else if(color.toLowerCase() == "yellow") {
    changeRgbColor(255, 255, 0);
  }
  else if(color.toLowerCase() == "orange") {
    changeRgbColor(255, 130, 0);
  }
  else {
    changeRgbColor(255, 255, 255); // white
  }
}

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_POT, INPUT);
  Serial.begin(9600);
}

void loop() {

//THIRD PART OF CLASS -- POTENTIOMETER TO CHANGE BRIGHTNESS

  //input ADC: 0-4095
  //output PWM: 0-255

  //read the potentiometer
  int potVal = analogRead(PIN_POT);
  // float voltage = float(potVal) / 4095 * 3.3;
  int pwnVal = float(potVal) / 4095 * 255;

  //show color white
  analogWrite(PIN_RED, pwnVal);
  analogWrite(PIN_GREEN, pwnVal);
  analogWrite(PIN_BLUE, pwnVal);

  // use potentiometer to change brightness


//SECOND PART OF CLASS -- FUNCTIONS

//   //show red on LED for 1/2 sec
//   //changeRgbColor(255, 0, 0);
//   changeRgbColorString("red");
//   delay(500); // 500ms or 1/2 sec

//   //show green on LED for 1/2 sec
//   //changeRgbColor(0, 255, 0);
//   changeRgbColorString("green");
//   delay(500); // 500ms or 1/2 sec

//   //show blue on LED for 1/2 sec
//   //changeRgbColor(0, 0, 255);
//   changeRgbColorString("blue");
//   delay(500); // 500ms or 1/2 sec

//   //show magenta on LED for 1/2 sec
//   //changeRgbColor(255, 0, 255);
//   changeRgbColorString("magenta");
//   delay(500); // 500ms or 1/2 sec

//   //show white on LED for 1/2 sec
//   //changeRgbColor(255, 255, 255);
//   changeRgbColorString("white");
//   delay(500); // 500ms or 1/2 sec

//   //show yellow on LED for 1/2 sec
//   //changeRgbColor(255, 255, 0);
//   changeRgbColorString("yellow");
//   //high is 3.3V and 0 is ground
//   delay(500); // 500ms or 1/2 sec
  
//   //show orange on LED for 1/2 sec
//   //changeRgbColor(255, 130, 0);
//   changeRgbColorString("orange");
//   delay(500); // 500ms or 1/2 sec
// }

// FIRST PART OF CLASS -- FLASHING LIGHTS

// const int PIN_RED = D2;
// const int PIN_GREEN = D3;
// const int PIN_BLUE = D4;
// const int PIN_POT = A0;

// void setup() {
//   pinMode(PIN_RED, OUTPUT);
//   pinMode(PIN_GREEN, OUTPUT);
//   pinMode(PIN_BLUE, OUTPUT);
//   pinMode(PIN_POT, INPUT);
//   Serial.begin(9600);
// }

// void loop() {
//   //show red on LED for 1/2 sec
//   digitalWrite(PIN_RED, HIGH); //digitalWrite(PIN, HIGH or LOW)
//   digitalWrite(PIN_GREEN, LOW);
//   digitalWrite(PIN_BLUE, LOW);
//   //high is 3.3V and 0 is ground
//   delay(500); // 500ms or 1/2 sec

//   //show green on LED for 1/2 sec
//   digitalWrite(PIN_GREEN, HIGH); //digitalWrite(PIN, HIGH or LOW)
//   digitalWrite(PIN_RED, LOW);
//   digitalWrite(PIN_BLUE, LOW);
//   //high is 3.3V and 0 is ground
//   delay(500); // 500ms or 1/2 sec

//   //show blue on LED for 1/2 sec
//   digitalWrite(PIN_BLUE, HIGH); //digitalWrite(PIN, HIGH or LOW)
//   digitalWrite(PIN_GREEN, LOW);
//   digitalWrite(PIN_RED, LOW);
//   //high is 3.3V and 0 is ground
//   delay(500); // 500ms or 1/2 sec

//   //show magenta on LED for 1/2 sec
//   digitalWrite(PIN_BLUE, HIGH); //digitalWrite(PIN, HIGH or LOW)
//   digitalWrite(PIN_GREEN, LOW);
//   digitalWrite(PIN_RED, HIGH);
//   //high is 3.3V and 0 is ground
//   delay(500); // 500ms or 1/2 sec

//   //show white on LED for 1/2 sec
//   digitalWrite(PIN_BLUE, HIGH); //digitalWrite(PIN, HIGH or LOW)
//   digitalWrite(PIN_GREEN, HIGH);
//   digitalWrite(PIN_RED, HIGH);
//   //high is 3.3V and 0 is ground
//   delay(500); // 500ms or 1/2 sec

//   //show yellow on LED for 1/2 sec
//   digitalWrite(PIN_BLUE, LOW); //digitalWrite(PIN, HIGH or LOW)
//   digitalWrite(PIN_GREEN, HIGH);
//   digitalWrite(PIN_RED, HIGH);
//   //high is 3.3V and 0 is ground
//   delay(500); // 500ms or 1/2 sec
  
//   //show orange on LED for 1/2 sec
//   analogWrite(PIN_RED, 255); //also ok is digitalWrite(PIN_RED, HIGH)
//   analogWrite(PIN_GREEN, 130);
//   analogWrite(PIN_BLUE, 0); //also ok is digitalWrite(PIN_RED, LOW)
//   //high is 3.3V and 0 is ground
//   delay(500); // 500ms or 1/2 sec
// }