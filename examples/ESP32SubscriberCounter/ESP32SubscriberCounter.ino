//YouTubeCounter 1.0, Markus Wörthmann www.turtleinho.at 2021 mit WifiManager (192.168.4.1)

//This example shows how you can create a subscriber counter with ESP32, WiFi Manager and ArduinoOTA updating

#include <YouTubeSight.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <LiquidCrystal_I2C.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//------- Access data ------
const char* ssid = ""; //post it here or in the Manager
const char* password = ""; //post it her or in the Manager
char channelGUID[40] = ""; //GUID here!
//-----------------------------------

WiFiClient http;
YouTubeSight sight(channelGUID, http);

LiquidCrystal_I2C lcd(0x27,16,2);

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
bool first_run = true;
const long interval = 60000;

void setup() {

  Serial.begin(115200);
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("YouTubeCounter");
  lcd.setCursor(0, 1);
  lcd.print("    vers 3.0  ");
  delay(2500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("by Turtleinho");
  delay(2000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Accesspoint");
  delay(2000);
  Serial.println();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFiManager wifiManager;

  wifiManager.resetSettings();  

  // If the connection fails then an access point is created
  wifiManager.autoConnect("YouTube-Counter", "12345678");

  Serial.print("Connect...");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connect...");
  delay(2000);
  // Waiting for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected ;)");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connected ;)");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP()); //IP Address of the ESP32
  Serial.println();
  delay(2000);

ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  ArduinoOTA.handle();
  currentMillis = millis();
  //Uncomment the following line to debug the output from the library
  //sight._debug = true;
  if (currentMillis - previousMillis >= interval || first_run) {
    first_run = false;
    // save the last time you checked
    previousMillis = currentMillis;
    if (sight.getData()) {
      Serial.println("Subscribers: " + sight.channelStats.subscribers_count);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("YouTube:");
      lcd.setCursor(0,1);   
      lcd.print(sight.channelStats.subscribers_count);
    } else {
      Serial.println("No data at the moment...");
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Receive data");
	}
  }
}
