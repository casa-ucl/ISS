#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//Provide WiFi credentials
const char* ssid = "WiFi_Name";
const char* password = "WiFi_Password";
//String for storing server response
String response = "";
//JSON document
DynamicJsonDocument doc(2048);

//Our api variables
int latitude;
int longitude;
String visibility;

void setup() {
  Serial.begin(115200);
  //Initiate WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Initiate HTTP client
  HTTPClient http;
  //Initiate WiFi client
  WiFiClient client;
  //The API URL
  String request = "api.wheretheiss.at/v1/satellites/25544";
  //Start the request
  http.begin(client, request);
  //Use HTTP GET request
  http.GET();
  //Response from server
  response = http.getString();
  //Serial.print(response); //use for debugging

  //Parse JSON, read error if any
  DeserializationError error = deserializeJson(doc, response);
  if(error) {
     Serial.print(F("deserializeJson() failed: "));
     Serial.println(error.f_str());
     delay(5000);
     return;
  }

  Serial.print("Full response: ");
  Serial.println(response);
 
  latitude = doc["latitude"].as<int>();
  Serial.print("Latitude: ");
  Serial.println(latitude);

  longitude = doc["longitude"].as<int>();
  Serial.print("Longitude: ");
  Serial.println(longitude);

  visibility = doc["visibility"].as<String>();
  Serial.print("Visibility: ");
  Serial.println(visibility);

  //Close connection  
  http.end();
  //Wait five seconds
  delay(5000);
}
