# YouTube Sight - Arduino Library 
Arduino library for connecting with YouTube Sight to extract channel statistics. The library is build and tested to work with ESP8266 boards but can also work with any other board through a suitable [Client implementation](https://www.arduino.cc/en/Reference/ClientConstructor)

# How to use YouTube Sight
- Sign up at [http://tools.tastethecode.com/youtube-sight](http://tools.tastethecode.com/youtube-sight)
- Get your GUID from the end of the generated API URL
- Replace the WIFI settings and the GUID in the provided example sketch

# Using the example sketch

The downloaded code can be included as a new library into the IDE selecting the menu:

     Sketch / include Library / Add .Zip library

or it can be installed throu the library manager from the Arduino IDE.

Include YoutubeApi in your project:

    #include <YouTubeSight.h>

and pass it a GUID and HTTP client implementation

    #define CHANNEL_GUID "867fb57a-73e4-4020-b455-4fd4959b1cc0" //Taste The Code channel
    WiFiClient http;
    YouTubeSight sight(CHANNEL_GUID, http);


