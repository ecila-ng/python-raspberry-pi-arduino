#include <ESP8266WiFi.h>

const char* ssid = "LU-IoT2";
const char* password = "CSC49008";

void setup () {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to: ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nIP Address is:");
  Serial.print(WiFi.localIP());
}

void loop () {
  
}
