#include "HLK_LD1125.h"
//#include <SoftwareSerial.h>

#define ld1125_rx 14
#define ld1125_tx 27

HLK_LD1125 ld1125(ld1125_rx, ld1125_tx, &Serial1);
//HLK_LD1125 ld1125(&Serial2);

void setup() {
  Serial.begin(115200);
  ld1125.begin();
  /*ld1125.setRmax(8.00);
  ld1125.setMth1Mov(80);
  ld1125.setMth2Mov(50);
  ld1125.setMth3Mov(20);
  ld1125.setMth1Occ(60);
  ld1125.setMth2Occ(55);
  ld1125.setMth3Occ(20);
  ld1125.setTsOn(60);
  ld1125.setTsOff(15);
  ld1125.setOutputMode(false);
  ld1125.saveAllSettings();*/
  Serial.println(ld1125.setTestMode(true));
  Serial.println(ld1125.setTestMode(true));
}

void loop() {

  /*ld1125.getAllSettings();

  Serial.print("rmax: ");
  Serial.println(ld1125.getRmax());
  Serial.print("mth1_mov: ");
  Serial.println(ld1125.getMth1Mov());
  Serial.print("mth2_mov: ");
  Serial.println(ld1125.getMth2Mov());
  Serial.print("mth3_mov: ");
  Serial.println(ld1125.getMth3Mov());
  Serial.print("mth1_occ: ");
  Serial.println(ld1125.getMth1Occ());
  Serial.print("mth2_occ: ");
  Serial.println(ld1125.getMth2Occ());
  Serial.print("mth3_occ: ");
  Serial.println(ld1125.getMth3Occ());
  Serial.print("ts_on: ");
  Serial.println(ld1125.getTsOn());
  Serial.print("ts_off: ");
  Serial.println(ld1125.getTsOff());
  Serial.print("output_mode: ");
  Serial.println(ld1125.getOutputMode());
  Serial.println("----------------------------------------");*/

  //delay(1000);
  
  ld1125.read();

  Serial.print(ld1125.getDisType());
  Serial.print(" ");
  Serial.print(ld1125.getOccDis());
  Serial.print(" ");
  Serial.print(ld1125.getMovDis());
  Serial.print(" ");
  Serial.print(ld1125.getOccStr());
  Serial.print(" ");
  Serial.println(ld1125.getMovStr());
}
