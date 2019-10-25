#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

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
  WiFiClient client;
  String host = "dweet.io";
  if (client.connect(host, 80)) {
    String url = "/get/latest/dweet/for/trannnnn";
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    while (client.connected()) {
      Serial.print(client.readStringUntil('\r'));
    }
    client.stop();

  }
}
