// based on
// https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40

/*
 * Project itp348_a9_xu_connie
 * Description: Bluetooth Car
 * Author: Connie Xu
 * Date: 3/26/23
 */

#include "argon_ble_setup.h"

/*
  Use Adafruit Bluefruit app
  (https://learn.adafruit.com/bluefruit-le-connect/controller)
  Connect to Argon -> controller

  CONFIGURATION
  Motor Controller
    PWMA    - D8
    AIN2    - D7
    AIN1    - D6
    BIN1    - D5
    BIN2    - D4
    PWMB    - D3

    VCC     - 3v3
    Standby - 3v3
    VM      - Li+
    Enable  - connect to switch

*/

// SYSTEM_MODE(MANUAL);  /* uncomment to disable wifi and use BT only */

/*
    forward
        leftMotor (forward)
        rightMotor (forward)
    backward
        leftMotor(backward)
        rightMotor (backward)
    left
    right
    --
    any motor with a motor to turn?
        three components you need to set
*/

/* onDataReceived()
    Event handler for incoming data via RX characteristic
    When the RXCharacteristic receives data, the event handler is called
    Note: uint8_t is a byte ("unsigned integer of length 8 bits")

    The command scheme is from the Adafruit Bluefruit app
    https://learn.adafruit.com/bluefruit-le-connect/controller

    ex: [‘!’] [‘B’] [‘4’] [‘1’] [CRC]
*/

// right motor
const int PWMA = D8;
const int AIN1 = D6;
const int AIN2 = D7;

// left motor
const int PWMB = D3;
const int BIN1 = D5;
const int BIN2 = D4;

int motorSpeed = 0;

void setup()
{
    argon_ble_setup();
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);

    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);

    pinMode(PWMA, OUTPUT);

    pinMode(PWMB, OUTPUT);

    Serial.begin(9600); // begin serial communication
}

void loop()
{
}

void onDataReceived(const uint8_t *data, size_t len, const BlePeerDevice &peer, void *context)
{
    // btSerialDebug(data, len); // uncomment for serial monitor debug
    if (len > 4)
    { // make sure there at least four bytes
        if (data[0] == '!' && data[1] == 'B' && data[2] == '5' &&
            data[3] == '1')
        // up (forwards) (both wheels forwards)
        {
            rightMotor(200);
            leftMotor(200);
        }
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '5' &&
                 data[3] == '0')
        // up (forwards) OFF
        {
            rightMotor(0);
            leftMotor(0);
        }
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '6' &&
                 data[3] == '1')
        // down (reverse) (both wheels backwards)
        {
            rightMotor(-200);
            leftMotor(-200);
        }
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '6' &&
                 data[3] == '0')
        // down (reverse) OFF
        {
            rightMotor(0);
            leftMotor(0);
        }
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '7' &&
                 data[3] == '1')
        // left (right wheel turn forwards, left wheel stagnant)
        {
            // rightMotor(255);
            // leftMotor(-200);
            rightMotor(150);
            leftMotor(-70);
        }
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '7' &&
                 data[3] == '0')
        // left OFF
        {
            rightMotor(0);
            leftMotor(0);
        }
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '8' &&
                 data[3] == '1')
        // right (left wheel turn forwards, right wheel stagnant)
        {
            // rightMotor(-200);
            // leftMotor(255);
            rightMotor(-70);
            leftMotor(150);
        }
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '8' &&
                 data[3] == '0')
        // right OFF
        {
            rightMotor(0);
            leftMotor(0);
        }
    }
}

void rightMotor(int motorSpeed)
{
    if (motorSpeed > 0)
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
    }
    else if (motorSpeed < 0)
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    }
    else
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
    }
    analogWrite(PWMA, abs(motorSpeed));
}

void leftMotor(int motorSpeed)
{
    if (motorSpeed > 0)
    {
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
    }
    else if (motorSpeed < 0)
    {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
    }
    else
    {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW);
    }
    analogWrite(PWMB, abs(motorSpeed));
}

/**********************************************************************/

/*
  btSerialDebug
      used for printing debug info to serial monitor
*/
void btSerialDebug(const uint8_t *data, size_t len)
{
    for (size_t ii = 0; ii < len; ii++)
    {
        Serial.print(data[ii]);
        Serial.print(" ");
    }
    Serial.println();
    for (size_t ii = 0; ii < len; ii++)
    {
        Serial.write(data[ii]);
        Serial.print(" ");
    }
    Serial.println();
}