/*
 * CASA0019 Group Project - ISS Tracker
 * Using:
 * HTTPS Secured Client GET Request
 * Copyright (c) 2019, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

/* Set these to your desired credentials. */
const char *ssid = "VM1227143";  //ENTER YOUR WIFI SETTINGS
const char *password = "fsk2htkpBbWp";

//Web/Server address to read/write from 
const char *host = "api.wheretheiss.at";
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80

//SHA1 finger print of certificate use web browser to view and copy
const char fingerprint[] PROGMEM = "D5 28 75 E9 DB C8 8C 13 7A 9E 2B 04 B0 09 C3 D8 DE 7B 6E FB";

//API variables
int latitude;
int longitude;
String visibility;

//JSON document
DynamicJsonDocument doc(2048);

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //Only Station No AP, This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  WiFiClientSecure httpsClient;    //Declare object of class WiFiClient

  Serial.println(host);

  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000); // 15 Seconds
  delay(1000);
  
  Serial.print("HTTPS Connecting");
  int r=0; //retry counter
  while((!httpsClient.connect(host, httpsPort)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }
  if(r==30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to web");
  }
  
  //Declare holding variables
  String getData, Link;

  //GET Data
  Link = "/v1/satellites/25544";

  Serial.print("requesting URL: ");
  Serial.println(host+Link);

  httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
                  
  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  Serial.println("reply was:");
  Serial.println("==========");
  String response;
  while(httpsClient.available()){        
    response = httpsClient.readStringUntil('\n');  //Read response
    Serial.println(response); //Print response
  }
  Serial.println("==========");
  Serial.println("closing connection");

  //Parse JSON, read error if any
  DeserializationError error = deserializeJson(doc, response);
  if(error) {
     Serial.print(F("deserializeJson() failed: "));
     Serial.println(error.f_str());
     delay(5000);
     return;
  }

  latitude = doc["latitude"].as<int>();
  Serial.print("Latitude: ");
  Serial.println(latitude);

  longitude = doc["longitude"].as<int>();
  Serial.print("Longitude: ");
  Serial.println(longitude);

  visibility = doc["visibility"].as<String>();
  Serial.print("Visibility: ");
  Serial.println(visibility);
    
  delay(2000);  //GET Data at every 2 seconds
}
