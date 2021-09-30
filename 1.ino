#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const int led = LED_BUILTIN;
const char* ssid = "2SDSL";
const char* password = "SaeidoMahdi";
String address = "http://mysterious-everglades-08626.herokuapp.com/esp/";
int done = 0;

void blink (){
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
}

int sum (String input){
  int result = 0;
  String one = "";
  String op = "";
  String two = "";
  int situ = 1;
  for (int i = 0; i < input.length();i++){

    if (String(input[i]) == "+" ||String(input[i]) == "-" ){

      if (situ == 1){
        situ = 2;
        op = String(input[i]);
      }else {
        situ = 1;

        if (op == "+"){
          result = result + one.toInt() + two.toInt();
        } else if (op == "-"){
          result = result + one.toInt() - two.toInt();
        } else {

        }
        op = String(input[i]);
        one = String(input[i]);
        two = "";
      }
    } else {

      if (situ == 1){
        one = one + String(input[i]);
      }else {
        two = two + String(input[i]);
      }

      if (i == input.length()-1){
        if (situ == 1){
        situ = 2;
        if (op == "+"){
            result = result + one.toInt();
          } else if (op == "-"){
            result = result + one.toInt();//manfish jaye dige handle shode
          } else {

          }
        }else {
          situ = 1;

          if (op == "+"){
            result = result + one.toInt() + two.toInt();
          } else if (op == "-"){
            result = result + one.toInt() - two.toInt();
          } else {

          }
          
        }
      }
    }
  }
  return result;
}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  blink();
}
void loop() {
  
    if ((WiFi.status() == WL_CONNECTED)) {
      if (done == 0){
      WiFiClient client;
      HTTPClient http;

      Serial.print("[HTTP] begin...\n");
      http.begin(client,address + "register");
      http.addHeader("Content-Type", "application/json");
      Serial.print("[HTTP] POST...\n");

      DynamicJsonDocument doc1(1024);
      doc1["first_name"] = "Mahdi";
      doc1["last_name"]   = "Safarmohammadloo";
      doc1["studentID"] = "95440296";
      doc1["chipID"] = String(ESP.getChipId());

      String output="";
      serializeJson(doc1, output);
      Serial.println(output);
      int httpCode = http.POST(output);
      
      if (httpCode > 0) {

        Serial.printf("[HTTP] POST... code: %d\n", httpCode);

        if (httpCode == HTTP_CODE_OK) {
          const String& payload = http.getString();
          Serial.println("received payload:\n<<");
          Serial.println(payload);
          Serial.println(">>");


          DynamicJsonDocument doc2(1024);
          deserializeJson(doc2, payload);

          const char* token = doc2["token"]; 



          http.end();

          


          //////////////////////////////////////////////////////

          Serial.print("[HTTP] begin...\n");
          http.begin(client,address + "get_expression");
          http.addHeader("Authorization","Token " + String(token));

          Serial.print("[HTTP] GET...\n");

          int httpCode2 = http.GET();
          if (httpCode2 > 0) {
            if (httpCode2 == HTTP_CODE_OK) {
              const String& payload2 = http.getString();
              Serial.println("received payload2:\n<<");
              Serial.println(payload2);
              Serial.println(">>");


              DynamicJsonDocument doc3(1024);
              deserializeJson(doc3, payload2);

              const char* expression = doc3["expression"]; 


              http.end();

            


              //////////////////////////////////////////////////////


              Serial.print("[HTTP] begin...\n");
              http.begin(client,address + "submit_solution");
              http.addHeader("Content-Type", "application/json");
              http.addHeader("Authorization","Token " + String(token));
              Serial.print("[HTTP] POST...\n");

              DynamicJsonDocument doc4(1024);
              doc4["solution"] = sum(expression);

              String output2="";
              serializeJson(doc4, output2);
              Serial.println(output2);
              int httpCode3 = http.POST(output2);

              if (httpCode3 > 0) {

                Serial.printf("[HTTP] POST... code: %d\n", httpCode3);

                if (httpCode3 == HTTP_CODE_OK) {
                  const String& payload3 = http.getString();
                  Serial.println("received payload3:\n<<");
                  Serial.println(payload3);
                  Serial.println(">>");


                  DynamicJsonDocument doc5(1024);
                  deserializeJson(doc5, payload3);
                  const char* result = doc5["result"]; 


                  http.end();

                

                  if (result == "correct"){
                    done = 1;
                  }
                  
                }else {
                  Serial.println(httpCode3);
                }
              }else {
                Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode3).c_str());
              } 
            }else {
              Serial.println(httpCode2);
            }
          }else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode2).c_str());
          }
        }else {
              Serial.println(httpCode);
            }
      } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    }
  }
  Serial.println("DONE !!!");
  delay(2000);
}