#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "LU-IoT2";
const char* password = "CSC49008";

WiFiClient nextClient;
WiFiClient client;
WiFiServer myServer(80);
String clientData;

//void processData();
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
  Serial.println(WiFi.localIP());

  WiFiClient client;


  myServer.begin();

}

void loop() {
  nextClient = myServer.available();
  //Serial.println("Next Client: " + nextClient);

  if (nextClient != NULL) {
    //Serial.println("Found client!");
    String clientData = "";
    while (nextClient.connected()) {

      //Serial.println("Client connected!");
      if (nextClient.available()) //Has client sent data?
      {
        //Serial.println("Client Available!");
        //Serial.println("Client data: " + clientData);
        processData();
      }

    }
  }
}

void processData () {
  char ch = nextClient.read(); //read next char from client
  //Serial.print(ch);
  if (ch == '\n') { //if this is end of line means client is done sending
    if (clientData.length() == 0) { //tell http client we are done
      nextClient.println("HTTP/1.1 200 OK");
      nextClient.println("Content-type:text/html");
      nextClient.println("Connection:close");
      nextClient.println();
      nextClient.stop(); //disconnect from client
    }

    else {
      Serial.println("Client Data: "+ clientData);
    }

    clientData = ""; //clear out current command
  }
  else if (ch != '\r') {
    clientData += ch;
  }
}
