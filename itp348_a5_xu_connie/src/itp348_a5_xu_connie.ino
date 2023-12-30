/*
 * Project itp348_a5_xu_connie
 * Description: Button Timers
 * Author: Connie Xu
 * Date: 2/12/23
 */

const int PIN_BUTTONR = D2;
const int PIN_BUTTONB = D3;
const int PIN_RED = D4;
const int PIN_GREEN = D5;
const int PIN_BLUE = D6;

// interveral for led red to blink
const unsigned long INTERVAL_LEDR = 500;
unsigned long prevMillisLedR = 0;

// interveral for led blue to blink
const unsigned long INTERVAL_LEDB = 500;
unsigned long prevMillisLedB = 0;

// interval for status
const unsigned INTERVAL_STATUS = 500;
unsigned long prevMillisStatus;

// interval for publish
const unsigned long INTERVAL_PUBLISH = 20000;
unsigned long prevMillisPublish = 0;

// light state
int ledr_state = LOW; // led is off
int ledb_state = LOW;

// flash check
bool ledr_flashing = false;
bool ledb_flashing = false;

// flash counter
int ledRCounter = 0;
int ledBCounter = 0;

// for toggle
int prevButtonStateR = HIGH;
int prevButtonStateB = HIGH;

// counter button
int buttonPressesRed = 0;
int buttonPressesBlue = 0;

// rand color func
void displayRandomColor()
{
  int r = random(0, 256);
  int b = random(0, 256);
  int g = random(0, 256);
  analogWrite(PIN_RED, r);
  analogWrite(PIN_GREEN, g);
  analogWrite(PIN_BLUE, b);
}

// red flashing colors func
void redFlash()
{
  digitalWrite(PIN_RED, HIGH);
  delay(100);
  displayRandomColor();
  delay(100);
  digitalWrite(PIN_RED, HIGH);
  delay(100);
  displayRandomColor();
  delay(100);
  digitalWrite(PIN_RED, HIGH);
  delay(100);
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, LOW);
}

// blue flashing colors func
void blueFlash()
{
  digitalWrite(PIN_BLUE, HIGH);
  delay(100);
  displayRandomColor();
  delay(100);
  digitalWrite(PIN_BLUE, HIGH);
  delay(100);
  displayRandomColor();
  delay(100);
  digitalWrite(PIN_BLUE, HIGH);
  delay(100);
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, LOW);
}

void setup()
{
  pinMode(PIN_BUTTONR, INPUT);
  pinMode(PIN_BUTTONB, INPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  unsigned long currMillis = millis();

  // current time for red counter
  unsigned long currMillisR = millis();

  // toggle code red
  int currButtonStateR = digitalRead(PIN_BUTTONR);

  if (currButtonStateR == LOW && prevButtonStateR == HIGH)
  { // rising edge
    ledRCounter = 0;
    ledb_flashing = false;

    ledr_flashing = !ledr_flashing;
    prevMillisLedR = currMillisR;
    if (ledr_flashing)
    {
      ledr_state = HIGH;
      digitalWrite(PIN_RED, HIGH);
    }
    else
    {
      ledr_state = LOW;
      digitalWrite(PIN_RED, LOW);
    }

    // test stage 1
    // Serial.println("button latch: " + String(ledr_flashing));
  }
  prevButtonStateR = currButtonStateR;

  if (ledr_flashing == true)
  {
    if (ledRCounter <= 12)
    {
      // test stage: 5
      // if (currMillis - prevMillisStatus > INTERVAL_STATUS)
      // {
      if (currMillisR - prevMillisLedR > INTERVAL_LEDR)
      {
        if (ledr_state == LOW)
        {
          ledr_state = HIGH;
          digitalWrite(PIN_RED, HIGH);
        }
        else
        {
          ledr_state = LOW;
          digitalWrite(PIN_RED, LOW);
        }

        // test stage 2
        // Serial.println("active and tracking: " + String(currMillisR));

        prevMillisLedR = currMillisR;
        ledRCounter++;
      }
      // }
    }
    else
    {
      redFlash();
      ledr_flashing = false;
      ledRCounter = 0;
      ledr_state = LOW;
      digitalWrite(PIN_RED, LOW);
      buttonPressesRed++;

      // test stage 3
      // Serial.println("red timer elapsed: " + String(buttonPressesRed));
    }
  }
  else
  {
    ledr_flashing = false;
    ledRCounter = 0;
    ledr_state = LOW;
    digitalWrite(PIN_RED, LOW);
  }

  // prevButtonState = currButtonState;

  // toggle code blue
  unsigned long currMillisB = millis();

  int currButtonStateB = digitalRead(PIN_BUTTONB);

  if (currButtonStateB == LOW && prevButtonStateB == HIGH)
  {
    ledBCounter = 0;

    ledb_flashing = !ledb_flashing;
    prevMillisLedB = currMillisB;
    if (ledb_flashing)
    {
      ledb_state = HIGH;
      digitalWrite(PIN_BLUE, HIGH);
    }
    else
    {
      ledb_state = LOW;
      digitalWrite(PIN_BLUE, LOW);
    }
  }
  prevButtonStateB = currButtonStateB;

  if (ledb_flashing == true)
  {
    if (ledBCounter <= 20)
    {
      // test stage: 5
      // if (currMillis - prevMillisStatus > INTERVAL_STATUS)
      // {
      if (currMillisB - prevMillisLedB > INTERVAL_LEDB)
      {
        if (ledb_state == LOW)
        {
          ledb_state = HIGH;
          digitalWrite(PIN_BLUE, HIGH);
        }
        else
        {
          ledb_state = LOW;
          digitalWrite(PIN_BLUE, LOW);
        }
        prevMillisLedB = currMillisB;
        ledBCounter++;
      }
      // }
    }
    else
    {
      blueFlash();
      ledb_flashing = false;
      ledBCounter = 0;
      ledb_state = LOW;
      digitalWrite(PIN_BLUE, LOW);
      buttonPressesBlue++;
    }
  }
  else
  {
    ledb_flashing = false;
    ledBCounter = 0;
    ledb_state = LOW;
    digitalWrite(PIN_BLUE, LOW);
  }

  if (currMillis - prevMillisPublish > INTERVAL_PUBLISH)
  {
    prevMillisPublish = currMillis;
    Particle.publish("Red timers elapsed:", String(buttonPressesRed));
    Particle.publish("Blue timers elapsed:", String(buttonPressesBlue));
  }
}