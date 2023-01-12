

![FINAL PRODUCT]("physical device photos/FINAL RESULT GAUGE.jpeg")
# ISS Tracker Overview
Welcome to our International Space Station (ISS) Tracking Device project! This project is a physical gauge that displays the position and visibility of the ISS in real-time using a combination of a rotating map, LED lights, and a servo motor. The device was developed by a team of students and is powered by an Arduino NodeMCU board.

This GitHub repository contains all the files and information related to the project, including:

The code for the NodeMCU and the augmented reality app
3D model files for the physical device and the animation created in Blender
Photos and instructions for 3D printing the device
The project report and bibliography
Collaboration folder that contains information on the team members' individual contributions and their roles on the project
To access and use the files, please navigate through the different folders and open the files in the appropriate software.
If you have any questions or feedback, please do not hesitate to contact us. Thank you for visiting our repository and we hope you enjoy our project.


#Introduction

First launched in 1998, The International Space Station (ISS) is the Earth’s biggest artificial satellite and the largest spacecraft ever constructed. It is the world’s only microgravity science lab where researchers conduct experiments across a wide variety of disciplines, often with groundbreaking results (NASA, 2020).  Its unique research environment and level of international cooperation required for its running make the ISS  “the most complex engineering, scientific, collaborative human feat ever managed” (NASA, 2020). Orbiting about 400 kilometers above Earth, it travels 28,000km/h and makes a complete orbits every 90 minutes, or 16 times per day. The ISS reflects sunlight and can be seen with the naked eye as a bright white pinpoint of light in the sky moving at a constant speed (NASA, 2013). Spotting the ISS is a popular hobby, and is regarded as one of the most intriguing and rewarding stargazing activities (Beall, 2023). For that reason, there are many apps and websites dedicated to mapping the live location of the ISS, such as AstroViewer (AstroViewer, 2022), NASA’s Spot the Station (Spot The Station, 2020), and mobile applications GoISSWatch ISS Tracking (GoSoftWorks, 2021), and ISS Finder (Harry Slotwiner, 2022). Following this trend, our team thought it would be fulfilling to create a physical device that tracked the location of this iconic spacecraft.
 



# Workspace
* 3D printer (Original Prusa i3 MK3S or MK3S+)
* Fusion 360 for 3D modeling
* [Blender for animation](https://www.youtube.com/watch?v=Yl_qDDRlXHo)
* Unity for AR development and Google Pixel 4a as the target platform
* Servo motors, LEDs, and acrylic sheets to construct the physical device
* Arduino IDE and C# for programming


# component of the physical divice
- Servo motors
- LEDs
- Acrylic sheets
- Arduino NodeMCU
- 360 Lego Geekservo
- Adafruit Neopixel Stick
- WS2812B LED Strip
- Globe map

# For the Arduino code:
- Remeber to change the WiFi credentials to the WiFi you want to connect to.
- When it starts, expect the LED strip (visibility) to turn on white.
- Expect all the LEDs on the NeoPixel board (latitude) to turn on red.
- Expect the servo (longitude) to turn to the 0 degrees location.
- Move the map so that the 0 degrees latitude line is aligned to the led line formed by the latitude LEDs.
- The device will automatically make a request to the API and once it recives a response the lights and servo will then update automatically every 5 seconds to the correct positions.
