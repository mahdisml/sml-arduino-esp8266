
void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // for detect its working
 Serial.begin(9600);
  initEdits ();
  pinEdits ();
  ESP.deepSleep(5e6);
}

void loop() {

  
}
void initEdits (){
  digitalWrite(D1,0);
  digitalWrite(D2,0);
  digitalWrite(D3,0);
  digitalWrite(D4,0);
  digitalWrite(D5,0);
  digitalWrite(D6,0);
  digitalWrite(D7,0);
  digitalWrite(D8,0);
}
void pinEdits (){
  int j = 1;
  for (int i = 1;i <= 15;i++){
    if (j == 9){
      j = 1;
    }
    if (digitalRead(numberToPin(j)) == 1){
      digitalWrite(numberToPin(j),0);
    }else {
      digitalWrite(numberToPin(j),1);
    }
    delay(296);
    j++;
  }
}
uint8_t numberToPin(int num){
  switch(num) {
  case 1:
    return D1;
    break;
  case 2:
    return D2;
    break;
  case 3:
    return D3;
    break;
  case 4:
    return D4;
    break;
  case 5:
    return D5;
    break;
  case 6:
    return D6;
    break;
  case 7:
    return D7;
    break;
  default:
    return D8;
  }
}
