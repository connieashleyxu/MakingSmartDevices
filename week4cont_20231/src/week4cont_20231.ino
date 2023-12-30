/*
 * Project week4cont_20231
 * Description: Multi-Tasking Delay Lab
 * Author: Connie Xu
 * Date: 2/1/23
 */

const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_BUTTON = D2;

//global vars
const unsigned long INTERVAL_LED1 = 300;
unsigned long prevMillisLed1 = 0;

const unsigned long INTERVAL_PUBLISH = 1000;
unsigned long prevMillisPublish = 0;

int led1_state = LOW;  // led is off
int led2_state = LOW;

int prevButtonState = HIGH;

int buttonPresses = 0;

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //millis
  unsigned long currMillis = millis();

  if (currMillis - prevMillisLed1 > INTERVAL_LED1) {
    if (led1_state == LOW) {
      led1_state = HIGH; 
      digitalWrite(PIN_LED1, HIGH);
    } else { 
      led1_state = LOW;
      digitalWrite(PIN_LED1, LOW);
    }

    prevMillisLed1 = currMillis;
  }

  //toggle
  int currButtonState = digitalRead(PIN_BUTTON);
  if (currButtonState == LOW && prevButtonState == HIGH) {
    buttonPresses = buttonPresses + 1;

    if (led2_state == LOW) {
      led2_state = HIGH;
    } else {
      led2_state = LOW;
    }
      
    digitalWrite(PIN_LED2, led2_state);  // same as above, but shorter
  }

  prevButtonState = currButtonState;

  //publish
  if (currMillis - prevMillisPublish > INTERVAL_PUBLISH) {
    prevMillisPublish = currMillis; //always remember to update time
    Particle.publish("Current Button Presses", String(buttonPresses));
  }
}