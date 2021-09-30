int on = 0;
int pin8 = 8;
int pin6 = 6;
unsigned long duration8;
unsigned long duration6;

void setup() {
  Serial.begin(115200);//debug
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pin8, INPUT);
  pinMode(pin6, INPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  start();
}
void start(){
  
}
void loop() {
  duration8 = pulseIn(pin8, HIGH);
  duration6 = pulseIn(pin6, HIGH);
  if (duration8 > 5000){
    on = 1;
  }
  if (duration6 > 3000){
    on = 0;
    ESP.restart();
  }
  if (on == 1){
    digitalWrite(LED_BUILTIN, LOW);
    delay(duration8/2);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(duration8/2);
  }else{
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

