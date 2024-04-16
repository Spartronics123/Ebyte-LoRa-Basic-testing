/*
 * LoRa E32
 * Start device or reset to send a message
 * https://mischianti.org
 *
 * E32        ----- esp32
 * M0         ----- GND
 * M1         ----- GND
 * TX         ----- RX2 (PullUP)
 * RX         ----- TX2 (PullUP)
 * AUX        ----- Not connected
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
 */
#include "Arduino.h"

const int M0 = 18;
const int M1 = 5;

void setup() {
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  Serial.begin(9600);
  delay(500);
 
  Serial.println("Hi, I'm going to send message!");
 
  Serial2.begin(9600);
  Serial2.println("Hello, world?");
}
 
void loop() {
  if (Serial2.available()) {
    Serial.write(Serial2.read());
  }
  if (Serial.available()) {
    Serial2.write(Serial.read());
  }
}