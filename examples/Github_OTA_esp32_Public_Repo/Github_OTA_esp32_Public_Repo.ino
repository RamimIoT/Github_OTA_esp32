#include <WiFi.h>
#include "GithubOTA.h"
const char* ssid = "SoftKey_TechSpace_IoT";
const char* password = "TechSpace";
unsigned long currentMillis = 0;
unsigned long previousMillis_2 = 0;
const long mini_interval = 1000;

void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  connectWiFi();
  delay(1000);
}


void loop() {

  static int num = 0;
  currentMillis = millis();
  if ((currentMillis - previousOTAMillis) >= OTAinterval) {    
    if (checkForUpdates()) {
      Serial.println("Starting firmware update...");
      performFirmwareUpdate();
    }
    previousOTAMillis = currentMillis;
  }
  if ((currentMillis - previousMillis_2) >= mini_interval) {  
    Serial.print("idle loop...");
    Serial.print(num++);
    Serial.print(" Working : ");
    Serial.println(FirmwareVer);
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("wifi connected");
    } else {
      connectWiFi();
    }
    previousMillis_2 = currentMillis;
  }
}
