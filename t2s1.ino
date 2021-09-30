#include <EEPROM.h>

int address = 0;
int maxEeprom = 40;

void setup() {
  Serial.begin(115200);//debug
  EEPROM.begin(512);
  start();
}

void start(){
  attachInterrupt(digitalPinToInterrupt(D0), run, RISING);
  attachInterrupt(digitalPinToInterrupt(D1), run, RISING);
  attachInterrupt(digitalPinToInterrupt(D2), run, RISING);
  attachInterrupt(digitalPinToInterrupt(D3), run, RISING);
  attachInterrupt(digitalPinToInterrupt(D4), run, RISING);
  attachInterrupt(digitalPinToInterrupt(D5), run, RISING);
  attachInterrupt(digitalPinToInterrupt(D6), run, RISING);
  attachInterrupt(digitalPinToInterrupt(D7), run, RISING);
  attachInterrupt(digitalPinToInterrupt(D8), run, RISING);
}

void loop() {
 
}

void run (){
  int sensorValue = analogRead(D1);
  Serial.println(sensorValue);
  add(sensorValue);
}



void add(int num){
  
  if (address + 4 > maxEeprom){
    address = 0;
  }
  eeWriteInt(address,num);
  address = address + 4;
}

int get (int place){ // az 0 ta 9 (akhar be avval hastesh)
  int realPlace = (9-place)*4;
  return eeGetInt(realPlace);
}


///////////////
// int to bytes and save to EEPROM


void eeWriteInt(int pos, int val) {
    byte* p = (byte*) &val;
    EEPROM.write(pos, *p);
    EEPROM.write(pos + 1, *(p + 1));
    EEPROM.write(pos + 2, *(p + 2));
    EEPROM.write(pos + 3, *(p + 3));
    EEPROM.commit();
}
int eeGetInt(int pos) {
  int val;
  byte* p = (byte*) &val;
  *p        = EEPROM.read(pos);
  *(p + 1)  = EEPROM.read(pos + 1);
  *(p + 2)  = EEPROM.read(pos + 2);
  *(p + 3)  = EEPROM.read(pos + 3);
  return val;
}
