#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

const char* ssid = "SSIDXXXX";
const char* password = "PASSWORDXXXX";
ESP8266WebServer server(80);
SoftwareSerial sim800l(2, 3);

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.begin(ssid, password);
  Serial.println("");
  mySerial.begin(9600);
  start();
  server.begin();
  Serial.println(WiFi.softAPIP()); // address
}


void loop() {
  WiFiClient client = server.available();
  if (client){
    while (client.connected()){
      if (client.available()){
        String line = client.readStringUntil('\r');

        String chipId = String(getChipId());
        String vcc = String(ESP.getVcc());
        
        //send sms chipId and vcc
        mySerial.println("AT");
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+98"\""+line);
        client.println("its done");
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client down");
  }
}

