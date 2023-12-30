/*
 * Project week2_20231
 * Description: ITP 342 Week 2 In-Class
 * Author: Connie Xu
 * Date: 01/18/2022
 */

// create a global const to represent each pin in project
const int PIN_POT = A0;
const int PIN_ONBOARD_LED = D7;
const int PIN_LED = D2;
//int potVal = 0;

// this happens JUST ONCE
// configure serial monitor, setup pin modes
void setup() {
  Serial.begin(9600);
  pinMode(PIN_POT, INPUT);
  pinMode(PIN_ONBOARD_LED, OUTPUT);
  pinMode(PIN_LED, OUTPUT);

  Serial.println("This message is in setup and shows only once");
}

// infinite loop
void loop() {
  Serial.println("Now we are in loop()");

  int potVal = analogRead(PIN_POT);
  //potVal = analogRead(PIN_POT);

  float voltage = float(potVal) / (4095 * 3.3);

  // print out digital value and analog voltage
  // 0 - 3.3v analog
  // 0 - 4095 voltage

  Serial.println("The potentiometer value is " + String(potVal) + " and the voltage is " + String(voltage,2)); // convert int -> String
  //delay(500); // 500ms

  analogWrite(PIN_LED, 0); // off
  delay(500);
  analogWrite(PIN_LED, 127); // half bright
  delay(500);
  analogWrite(PIN_LED, 255); // full bright
  
}