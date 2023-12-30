/*
 * Project itp348_a1_xu_connie
 * Description: Blink assignment 1
 * Author: Connie Xu
 * Date: 1/15/23
 */
 
void setup() {
  pinMode(D7, OUTPUT);
}


void loop() {
  digitalWrite(D7, HIGH);
    delay(1000);
	digitalWrite(D7, LOW);
    delay(1000);
}