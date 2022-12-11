# ISS Tracker


#Introduction
ISS Tracker as a physical data device and Augmented Twin
# Overview



# Workspace

# Format of files 

# component of the physical divice 

Gauge Dial

For the Arduino code:
- Remeber to change the WiFi credentials to the WiFi you want to connect to.
- When it starts, expect the LED strip (visibility) to turn on white.
- Expect all the LEDs on the NeoPixel board (latitude) to turn on red.
- Expect the servo (longitude) to turn to the 0 degrees location.
- Move the map so that the 0 degrees latitude line is aligned to the led line formed by the latitude LEDs.
- The device will automatically make a request to the API and once it recives a response the lights and servo will then update automatically every 5 seconds to the correct positions.
