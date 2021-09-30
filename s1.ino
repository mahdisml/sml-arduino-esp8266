#include <EEPROM.h>

int currentEeprom = 0;
int currentEepromPlace = 511;
int maxEeprom = 255;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);// for detect its working
  digitalWrite(LED_BUILTIN, LOW); // for detect its working
  pinMode(D8, OUTPUT);
  Serial.begin(9600);
  EEPROM.begin(512);
  attachInterrupt(digitalPinToInterrupt(D5), run, CHANGE);
}

void loop() {
  analogWrite(D8, (eeGetInt(currentEeprom)/255)*100);
  delay(5000);

}

void run (){
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  add(sensorValue);
}

void add(int num){
  
  if (currentEeprom + 4 > maxEeprom){
    currentEeprom = 0;
    EEPROM.write(currentEepromPlace, currentEeprom);
    EEPROM.commit();
  }
  eeWriteInt(currentEeprom,num);
  currentEeprom = currentEeprom + 4;
  EEPROM.write(currentEepromPlace, currentEeprom);
  EEPROM.commit();
}

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