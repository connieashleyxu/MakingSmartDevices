/*
 * Project itp348_a8_xu_connie
 * Description: State Machine Tea Brewer with Blynk
 * Author: Connie Xu
 * Date: 3/12/23
 */

// ✅ stage 1
// ✅ stage 2
// ✅ stage 3
// ✅ stage 4
// ✅ stage 5

#define BLYNK_TEMPLATE_ID "TMPLBiC_Eyki"
#define BLYNK_TEMPLATE_NAME "Assignment8"
#define BLYNK_AUTH_TOKEN "i6TOZHGaZuOT06n2k-_oUIJZ4MOJl9dg"

#define BLYNK_PRINT Serial
#define BLYNK_IP IPAddress(64, 225, 16, 22)
#include <blynk.h>
#include "pitches.h"

const int PIN_SPEAKER = D2;
const int PIN_SWITCH = D3;

enum State
{
  Idle,
  Heat,
  Steep,
  Hold,
  Pour
};

enum Cup
{
  Present,
  Missing
};

// global vars
State currentState = Idle;
Cup cupStatus = Missing;

String stateString = "";
String cupString = "";

bool brewActive = false;
bool cupPresent = false;

const int GOAL_HEAT_TIME = 6000;
const int GOAL_STEEP_TIME = 3000;
const int GOAL_POUR_TIME = 4000;

unsigned long prevMillisState = 0;
unsigned long stateDuration = 0;

unsigned long blynkUpdateInterval = 1000;
unsigned long prevBlynkMillis = 0;

int buttonVal = 0;      // blynk button start brew
int soundButtonVal = 0; // blynk button sound

// song at the end of brew
int melody[] = {
    NOTE_F2,
    NOTE_F2,
    NOTE_F2,
    NOTE_G2,
    NOTE_F2,
    NOTE_C2,
    NOTE_D2,
    NOTE_DS2,
    NOTE_D2,
    NOTE_C2,
    NOTE_AS1,
    NOTE_F2,
    NOTE_F2,
    NOTE_F2,
    NOTE_G2,
    NOTE_F2,
    NOTE_C2,
    NOTE_D2,
    NOTE_DS2,
    NOTE_D2,
    NOTE_C2,
    NOTE_AS1,
};
int duration[] = {4, 4, 4, 4, 4,
                  4, 4, 4, 4, 4, 4,
                  4, 4, 4, 4, 4,
                  4, 4, 4, 4, 4, 4};

// function to display current state as string
String getStateString()
{
  String output = "";

  switch (currentState)
  {
  case Idle:
    output = "Idle";
    break;
  case Heat:
    output = "Heat";
    break;
  case Steep:
    output = "Steep";
    break;
  case Hold:
    output = "Hold";
    break;
  case Pour:
    output = "Pour";
    break;
  }
  return output;
}

// function to display current cup as string
String getCupString()
{
  String output = "";

  switch (cupStatus)
  {
  case Present:
    output = "Present";
    break;
  case Missing:
    output = "Missing";
    break;
  }
  return output;
}

// function for display all state information
void displayAllStateInfo()
{
  stateString = getStateString();
  cupString = getCupString();

  Serial.println(stateString);
  Serial.println(cupString);
}

// function for check cup status
void checkCupStatus()
{
  if (digitalRead(PIN_SWITCH) == HIGH)
  {
    cupPresent = false;

    cupStatus = Missing;
    cupString = getCupString();
    Serial.println(cupString);
  }
  else if (digitalRead(PIN_SWITCH) == LOW)
  {
    cupPresent = true;

    cupStatus = Present;
    cupString = getCupString();
    Serial.println(cupString);
  }
}

// function for check set brew active button
void checkButtonStatus()
{
  if (buttonVal == 0)
  {
    brewActive = false;

    currentState = Idle;
    updateNextStateDuration();
    stateString = getStateString();
    Serial.println(stateString);
  }
  else if (buttonVal == 1)
  {
    brewActive = true;
  }
}

// function for update next state (transition to different states)
void updateNextState()
{
  unsigned long currMillis = millis();

  switch (currentState)
  {
  case Idle:
    checkButtonStatus();
    checkCupStatus();
    // if brewing active is true, then heat
    if (brewActive == true)
    {
      currentState = Heat;
      prevMillisState = currMillis;
      updateNextStateDuration();
      displayAllStateInfo();
    }
    // else idle
    // if brew button off, stop brew and reset to idle
    else
    {
      currentState = Idle;
      stateString = getStateString();
      Serial.println(stateString);
    }
    break;
  case Heat:
    checkButtonStatus();
    Serial.println(String(brewActive));
    checkCupStatus();
    // if brewing is active && heat time >= goal heat time, heat for 6 seconds, then steep
    if ((brewActive == true) && (currMillis - prevMillisState >= stateDuration))
    {
      prevMillisState = currMillis;
      currentState = Steep;
      updateNextStateDuration();
      displayAllStateInfo();
    }
    // if brew is not active, idle
    else if (brewActive == false)
    {
      prevMillisState = currMillis;

      currentState = Idle;
      stateString = getStateString();
      Serial.println(stateString);
    }
    break;
  case Steep:
    checkButtonStatus();
    checkCupStatus();
    // if brewing is active && brew time >= goal brew time, steep for 3 seconds, then hold
    if ((brewActive == true) && (currMillis - prevMillisState > stateDuration))
    {
      prevMillisState = currMillis;
      currentState = Hold;
      updateNextStateDuration();
      displayAllStateInfo();
    }
    // if brew is not active, idle
    else if (brewActive == false)
    {
      prevMillisState = currMillis;

      currentState = Idle;
      stateString = getStateString();
      Serial.println(stateString);
    }
    break;
  case Hold:
    checkButtonStatus();
    checkCupStatus();
    // if brewing is active && cup is present, then pour
    if ((brewActive == true) && cupPresent == true)
    {
      prevMillisState = currMillis;

      currentState = Pour;
      updateNextStateDuration();
      displayAllStateInfo();
    }
    // if brewing is active && cup is not present, then hold
    else if ((brewActive == true) && cupPresent == false)
    {
      prevMillisState = currMillis;

      currentState = Hold;
      updateNextStateDuration();
      displayAllStateInfo();
    }
    // if brew is not active, idle
    else if (brewActive == false)
    {
      prevMillisState = currMillis;

      currentState = Idle;
      stateString = getStateString();
      Serial.println(stateString);
    }
    break;
  case Pour:
    checkButtonStatus();
    checkCupStatus();
    // if brewing is active && pour time >= goal pour time, pour for 4 seconds, then idle
    if ((brewActive == true) && (currMillis - prevMillisState > stateDuration))
    {
      prevMillisState = currMillis;
      // if sound button on, play melody
      if (soundButtonVal == HIGH)
      {
        for (int i = 0; i < arraySize(melody); i++)
        {
          int noteTime = 1000 / duration[i];
          tone(PIN_SPEAKER, melody[i], noteTime);
          delay(noteTime * 1.2);
        }
      }

      // TODO: once complete, turn blynk button off
      brewActive = false;
      buttonVal = 0;
      Blynk.virtualWrite(V3, brewActive);
      checkButtonStatus();

      currentState = Idle;
      updateNextStateDuration();
      displayAllStateInfo();
    }
    break;
  }
}

// function for update next state duration (sets duration for next state every time a transition is about to happen)
void updateNextStateDuration()
{
  switch (currentState)
  {
  case Idle:
    stateDuration = 0;
    break;
  case Heat:
    stateDuration = GOAL_HEAT_TIME;
    break;
  case Steep:
    stateDuration = GOAL_STEEP_TIME;
    break;
  case Hold:
    stateDuration = 0;
    break;
  case Pour:
    stateDuration = GOAL_POUR_TIME;
    break;
  }
}

// from blynk app to argon

// button start brew
BLYNK_WRITE(V3)
{
  buttonVal = param.asInt(); // this is virtual pin V3 which a button
}

// button sound
BLYNK_WRITE(V5)
{
  soundButtonVal = param.asInt(); // this is virtual pin V5 which a button
}

void setup()
{
  pinMode(PIN_SPEAKER, OUTPUT);
  pinMode(PIN_SWITCH, INPUT); // configure
  Serial.begin(9600);

  delay(5000);
  Blynk.begin(BLYNK_AUTH_TOKEN, BLYNK_IP); // initial setup
}

void loop()
{
  Blynk.run();
  updateNextState();

  unsigned long currBlynkMillis = millis();
  if (currBlynkMillis - prevBlynkMillis > blynkUpdateInterval)
  {
    // from argon to app

    // string cup status
    Blynk.virtualWrite(V2, cupString);

    // string text state
    Blynk.virtualWrite(V4, stateString);

    prevBlynkMillis = currBlynkMillis;
  }
}