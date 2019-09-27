/*
 * YouTube Sight Library - ESP8266 Example
 * http://tools.tastethecode.com/youtube-sight
 * 
 * The YouTube Sight service and library are written by Blagojce Kolicoski
 * for the Taste The Code YouTube Channel
 * https://www.youtube.com/tastethecode
 */

#include <YouTubeSight.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

/* Set these to your desired credentials. */
const char *ssid = "WIFINAME";  //ENTER YOUR WIFI SETTINGS
const char *password = "wifipassword";

#define CHANNEL_GUID "867fb57a-73e4-4020-b455-4fd4959b1cc0" //ENTER YOUR CHANNEL GUID

//required for non blocking delay implementation
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
bool first_run = true;

//delay interval 60 seconds
const long interval = 60000;

WiFiClient http;
YouTubeSight sight(CHANNEL_GUID, http);

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot

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
  currentMillis = millis();
  //Uncomment the following line to debug the output from the library
  //sight._debug = true;
  if (currentMillis - previousMillis >= interval || first_run) {
    first_run = false;
    // save the last time you checked
    previousMillis = currentMillis;
    if (sight.getData()) {
      Serial.println("views: " + sight.channelStats.views);
      Serial.println("subscribers_gained: " + sight.channelStats.subscribers_gained);
      Serial.println("subscribers_lost: " + sight.channelStats.subscribers_lost);
      Serial.println("subscribers_count: " + sight.channelStats.subscribers_count);
      Serial.println("estimated_minutes_watched: " + sight.channelStats.estimated_minutes_watched);
      Serial.println("average_view_duration: " + sight.channelStats.average_view_duration);
    } else {
      //use sight._debug = true; at the begining to debug the library output
      Serial.println("There was an error getting the data.");
    }
  }

  //rest of your application code
}
