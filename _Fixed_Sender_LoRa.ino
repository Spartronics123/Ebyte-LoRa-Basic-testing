/*
 * LoRa E32-TTL-100
 * Send fixed transmission message to a specified point.
 * https://mischianti.org
 *
 * E32-TTL-100----- Arduino UNO or esp8266
 * M0         ----- 3.3v (To config) GND (To send) 7 (To dinamically manage)
 * M1         ----- 3.3v (To config) GND (To send) 6 (To dinamically manage)
 * TX         ----- PIN 2 (PullUP)
 * RX         ----- PIN 3 (PullUP & Voltage divider)
 * AUX        ----- Not connected (5 if you connect)
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
 */
#include "Arduino.h"
#include "LoRa_E32.h"
 
// ---------- esp8266 pins --------------
//LoRa_E32 e32ttl(D2, D3, D5, D7, D6);
//LoRa_E32 e32ttl(D2, D3, D5, D7, D6); // Config without connect AUX and M0 M1
// #include <SoftwareSerial.h>
// SoftwareSerial mySerial(D2, D3); // e32 TX e32 RX
LoRa_E32 e32ttl(&Serial2, 21, 18, 5);
 
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(D2, D3);/   / e32 TX e32 RX
//LoRa_E32 e32ttl(&mySerial, D5, D7, D6);
// -------------------------------------
 
// ---------- Arduino pins --------------
//LoRa_E32 e32ttl(2, 3, 5, 7, 6);
//LoRa_E32 e32ttl(2, 3); // Config without connect AUX and M0 M1
 
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(2, 3); // e32 TX e32 RX
//LoRa_E32 e32ttl(&mySerial, 5, 7, 6);
// -------------------------------------
 
ResponseStructContainer c;
Configuration configuration;
String g = "";

void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);
//The setup function is called once at startup of the sketch
void setup()
{
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }
    delay(100);
 
    e32ttl.begin();
 
    // After set configuration comment set M0 and M1 to low
    // and reboot if you directly set HIGH M0 and M1 to program
    ResponseStructContainer c;
    c = e32ttl.getConfiguration();
    configuration = *(Configuration*) c.data;
    // configuration.ADDL = 0x01;
    // configuration.ADDH = 1;
    // configuration.CHAN = 2;
    // configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;
    // e32ttl.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
    // printParameters(configuration);
    // ---------------------------
}
 
// The loop function is called in an endless loop
void loop()
{
  configuration.ADDL = 0x10;
  String myString;
  myString += String(configuration.ADDL, HEX);

// Serial.print(myString);
  
  // configuration.ADDL = 0x01;
  // String g = "";
    delay(2000);
    // g = configuration.ADDL;
    // Receiving Code Part
    // if (e32ttl.available()  > 1){
    //     ResponseContainer rs = e32ttl.receiveMessage();
    //     // First of all get the data
    //     String message = rs.data;
 
    //     Serial.println(rs.status.getResponseDescription());
    //     Serial.println(message);
    // }
    // else{
    Serial.println("Send message to Transeiver");
    ResponseStatus rs = e32ttl.sendFixedMessage(0x00, 0x00, 0x05, myString);
    Serial.println(rs.getResponseDescription());
    // rs = e32ttl.sendFixedMessage(0x01, 0x00, 0x02, "Kindly");
    // Serial.println(rs.getResponseDescription());
    // }
}

void printParameters(struct Configuration configuration) {
    Serial.println("----------------------------------------");
 
    Serial.print(F("HEAD : "));  Serial.print(configuration.HEAD, BIN);Serial.print(" ");Serial.print(configuration.HEAD, DEC);Serial.print(" ");Serial.println(configuration.HEAD, HEX);
    Serial.println(F(" "));
    Serial.print(F("AddH : "));  Serial.println(configuration.ADDH, BIN);
    Serial.print(F("AddL : "));  Serial.println(configuration.ADDL, BIN);
    Serial.print(F("Chan : "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
    Serial.println(F(" "));
    Serial.print(F("SpeedParityBit     : "));  Serial.print(configuration.SPED.uartParity, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
    Serial.print(F("SpeedUARTDatte  : "));  Serial.print(configuration.SPED.uartBaudRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRate());
    Serial.print(F("SpeedAirDataRate   : "));  Serial.print(configuration.SPED.airDataRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRate());
 
    Serial.print(F("OptionTrans        : "));  Serial.print(configuration.OPTION.fixedTransmission, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFixedTransmissionDescription());
    Serial.print(F("OptionPullup       : "));  Serial.print(configuration.OPTION.ioDriveMode, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getIODroveModeDescription());
    Serial.print(F("OptionWakeup       : "));  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
    Serial.print(F("OptionFEC          : "));  Serial.print(configuration.OPTION.fec, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFECDescription());
    Serial.print(F("OptionPower        : "));  Serial.print(configuration.OPTION.transmissionPower, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());
 
    Serial.println("----------------------------------------");
 
}
void printModuleInformation(struct ModuleInformation moduleInformation) {
    Serial.println("----------------------------------------");
    Serial.print(F("HEAD BIN: "));  Serial.print(moduleInformation.HEAD, BIN);Serial.print(" ");Serial.print(moduleInformation.HEAD, DEC);Serial.print(" ");Serial.println(moduleInformation.HEAD, HEX);
 
    Serial.print(F("Freq.: "));  Serial.println(moduleInformation.frequency, HEX);
    Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
    Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
    Serial.println("----------------------------------------");
 
}