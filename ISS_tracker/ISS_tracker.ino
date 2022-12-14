/*
 * CASA0019 Group Project - ISS Tracker
 * Group 1 Astronaut - Gil Adda, Patrick Whyte, Sophia Chong, Hanpu Liu
 *
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

#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define LAT_LED_PIN 12 // PIN D6 on NodeMCU
#define LAT_NUM_PIXELS 8

#define VIS_LED_PIN 14 // PIN D5 on NodeMCU
#define VIS_NUM_PIXELS 100

#define LON_SER_PIN 13 // PIN D7 on NodeMCU

/* Set these to your desired credentials. */
const char *ssid = "CE-Hub-Student";  //ENTER YOUR WIFI SETTINGS
const char *password = "casa-ce-gagarin-public-service";

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

// Geekservo (longitude)
Servo servo;

// Initialize NeoPixel 8 Board (latitude)
Adafruit_NeoPixel pixels(LAT_NUM_PIXELS, LAT_LED_PIN);
// Initialize NeoPixel Strip (visibility)
Adafruit_NeoPixel strip(VIS_NUM_PIXELS, VIS_LED_PIN,  NEO_RGB + NEO_KHZ800);

void setup() {
  delay(1000);
  Serial.begin(115200);

  // Servo Code
  servo.attach(LON_SER_PIN);
  servo.write(0);

  // start NeoPixel board LEDs and set them all to be red to initalize
  pixels.begin();
  for (int i = 0; i < LAT_NUM_PIXELS; i++){
    pixels.setPixelColor(i, 200, 0, 0);
    pixels.show();
  }

  // Start Strip LEDs and set them to be white to initalize
  strip.begin();
  for (int i = 0; i < VIS_NUM_PIXELS; i++){
      strip.setPixelColor(i, 200, 200, 200);
      strip.show();
    }

  //start of wifi code TODO: move bloc to own function
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
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClientSecure httpsClient;

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

  // Update values from the response from the API
  latitude = doc["latitude"].as<int>();
  Serial.print("Latitude: ");
  Serial.println(latitude);

  longitude = doc["longitude"].as<int>();
  Serial.print("Longitude: ");
  Serial.println(longitude);

  visibility = doc["visibility"].as<String>();
  Serial.print("Visibility: ");
  Serial.println(visibility);

  // Update the hardware to show changes from the API  
  updateLongitude();
  updateLatitude();
  updateVisibility();  
    
  delay(5000);  //GET Data at every 2 seconds
}

// Helper Methods
void updateLongitude() {
  if (longitude < 0) {
    int mappedLongitude = map(longitude, -180, 0, 180, 360);
    servo.write(mappedLongitude);
  } else {
    servo.write(longitude);
  }
}

void updateVisibility() {
  if (visibility == "daylight") {
    for (int i = 0; i < VIS_NUM_PIXELS; i++){
      strip.setPixelColor(i, 252, 223, 3); // orange
      strip.show();
    }
  } else {  // "eclipsed" the ISS is in shadow
    for (int i = 0; i < VIS_NUM_PIXELS; i++){
      strip.setPixelColor(i, 107, 3, 252); // purple
      strip.show();
    }
  }
}

void updateLatitude() {
  //reset all the LEDs so only one is showing at a time
  for (int i = 0; i < LAT_NUM_PIXELS; i++){
    pixels.setPixelColor(i, 0, 0, 0);
    pixels.show();
  }
  //use the map function to remap the latitude to a number between 0-7 
  //then light up that LED
  //update: since I resoldered the Neopixel LED the opposite way, remap to 7-0 instead
  //int ledToLight = map(latitude, -90, 90, 0, 7);
  int ledToLight = map(latitude, -90, 90, 7, 0);
  pixels.setPixelColor(ledToLight, 100, 0, 0);
  pixels.show();
}



