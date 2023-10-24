#include <HTTPClient.h>
#include <GithubOTAUpdate.h>
#include <WiFiClientSecure.h>
#include "cert.h"
// binVersionURL = "https://github.com/RamimIoT/Github_OTA_esp32/blob/main/bin_version.h";
// firmwareURL = "https://github.com/RamimIoT/Github_OTA_esp32/blob/main/build/esp32.esp32.esp32/Github_OTA_esp32.ino.bin";
// Create a URL to fetch the asset from your release
const String githubUser = "RamimIoT";
const String githubRepo = "Github_OTA_esp32";
const String githubBranches = "main";
const String githubBin_version = "examples/Github_OTA_esp32_Public_Repo/bin_version.h";
const String githubBin_file = "examples/Github_OTA_esp32_Public_Repo/build/esp32.esp32.esp32/Github_OTA_esp32_Public_Repo.ino.bin";
// We don't need 'githubToken' for Public Repo.
// const char* githubToken = " ";
const String binVersionURL = "https://raw.githubusercontent.com/" + githubUser + "/" + githubRepo + "/" + githubBranches + "/" + githubBin_version;
const String firmwareURL = "https://raw.githubusercontent.com/" + githubUser + "/" + githubRepo + "/" + githubBranches + "/" + githubBin_file;

String FirmwareVer = "1.1";
#define LED_BUILTIN 2

unsigned long previousOTAMillis = 30000 + 1000;
unsigned long OTAinterval = 30 * 1000;  //30s


bool checkForUpdates() {
  HTTPClient http;
  http.begin(binVersionURL);
  // We don't need 'githubToken' for Public Repo.
  // http.addHeader("Authorization", "token " + String(githubToken));
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String latestVersion = http.getString();
    Serial.println("Latest version from GitHub: " + latestVersion);

    if (latestVersion > FirmwareVer) {
      Serial.println("A new firmware version is available.");
      return true;
    } else {
      Serial.println("You are already using the latest firmware version.");
      return false;
    }
  } else {
    Serial.print("Failed to check for updates. HTTP code: ");
    Serial.println(httpCode);
    return false;
  }
  http.end();
}

void performFirmwareUpdate() {
  WiFiClientSecure client;
  client.setCACert(rootCACertificate);
  // We don't need 'githubToken' for Public Repo.
  // githubOTAUpdate.addGitToken(String(githubToken));
  githubOTAUpdate.setLedPin(LED_BUILTIN, LOW);
  t_githubOTAUpdate_return ret = githubOTAUpdate.update(client, firmwareURL);

  switch (ret) {
    case GithubOTA_UPDATE_FAILED:
      Serial.printf("Firmware update failed. Error (%d): %s\n", githubOTAUpdate.getLastError(), githubOTAUpdate.getLastErrorString().c_str());
      break;
    case GithubOTA_UPDATE_NO_UPDATES:
      Serial.println("No updates available.");
      break;
    case GithubOTA_UPDATE_OK:
      Serial.println("Firmware update successful.");
      break;
  }
}
