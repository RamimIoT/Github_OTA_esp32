
# GitHub OTA for ESP32

GitHub OTA for ESP32 is an Arduino library that facilitates Over-The-Air (OTA) updates for ESP32 devices from both Public and Private GitHub repositories. This library leverages the 'httpUpdate' library and supports fine-grained personal access tokens for secure access to private repositories.

## Installation

1. **Library Manager (Recommended)**: Install the library via the Arduino Library Manager. Open the Arduino IDE, go to "Sketch" -> "Include Library" -> "Manage Libraries," and search for "GitHub OTA for ESP32."

2. **Manual Installation**: Alternatively, download the library from the [GitHub repository](https://github.com/RamimIoT/Github_OTA_esp32) and extract the contents into your Arduino libraries directory. Restart the Arduino IDE.

## Getting Started

Before using this library, create a fine-grained personal access token with the necessary permissions to access your private GitHub repositories. Learn how to create personal access tokens [here](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token).

## Usage - Private Repository Example

### Example Code - Github_OTA_esp32_Private_Repo.ino

```cpp
#include <WiFi.h>
#include "GithubOTA.h"

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
unsigned long currentMillis = 0;
unsigned long previousMillis_2 = 0;
const long mini_interval = 1000;

void connectWiFi() {
  WiFi.begin(ssid, password);
  while WiFi.status() != WL_CONNECTED) {
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
  // Check for OTA updates and perform them
  // Code provided in the example.
}
```

### GitHubOTA.h

```cpp
#include <HTTPClient.h>
#include <GithubOTAUpdate.h>
#include <WiFiClientSecure.h>
#include "cert.h"

const String githubUser = "YourGitHubUser";
const String githubRepo = "YourGitHubRepo";
const String githubBranches = "YourGitHubBranch";
const String githubBin_version = "YourGitHubBinVersionPath";
const String githubBin_file = "YourGitHubBinFilePath";
const char* githubToken = "YourGitHubToken"; // Fine-grained personal access token
const String binVersionURL = "https://raw.githubusercontent.com/" + githubUser + "/" + githubRepo + "/" + githubBranches + "/" + githubBin_version;
const String firmwareURL = "https://raw.githubusercontent.com/" + githubUser + "/" + githubRepo + "/" + githubBranches + "/" + githubBin_file";

String FirmwareVer = "1.0";
#define LED_BUILTIN 2

unsigned long previousOTAMillis = 30000 + 1000;
unsigned long OTAinterval = 30 * 1000;

bool checkForUpdates() {
  // Check for firmware updates on GitHub
}

void performFirmwareUpdate() {
  // Perform firmware update
}
```

In this example, we've updated the parameter values in the code snippets to placeholders ("YourGitHubUser," "YourGitHubRepo," "YourGitHubBranch," "YourGitHubBinVersionPath," "YourGitHubBinFilePath," and "YourGitHubToken") to emphasize that you should customize these values according to your specific GitHub repository and access token.

## Usage - Public Repository Example

### Example Code - Github_OTA_esp32_Public_Repo.ino

```cpp
#include <WiFi.h>
#include "GithubOTA.h"

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
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
  // Check for OTA updates and perform them
  // Code provided in the example.
}
```

### GitHubOTA.h

```cpp
#include <HTTPClient.h>
#include <GithubOTAUpdate.h>
#include <WiFiClientSecure.h>
#include "cert.h"

const String githubUser = "YourGitHubUser";
const String githubRepo = "YourGitHubRepo";
const String githubBranches = "YourGitHubBranch";
const String githubBin_version = "YourGitHubBinVersionPath";
const String githubBin_file = "YourGitHubBinFilePath";
const String binVersionURL = "https://raw.githubusercontent.com/" + githubUser + "/" + githubRepo + "/" + githubBranches + "/" + githubBin_version;
const String firmwareURL = "https://raw.githubusercontent.com/" + githubUser + "/" + githubRepo + "/" + githubBranches + "/" + githubBin_file";

String FirmwareVer = "1.0";
#define LED_BUILTIN 2

unsigned long previousOTAMillis = 30000 + 1000;
unsigned long OTAinterval = 30 * 1000;

bool checkForUpdates() {
  // Check for firmware updates on GitHub
}

void performFirmwareUpdate() {
  // Perform firmware update
}
```

In this example, we've updated the parameter values in the code snippets to placeholders ("YourGitHubUser," "YourGitHubRepo," "YourGitHubBranch," "YourGitHubBinVersionPath," and "YourGitHubBinFilePath") to emphasize that you should customize these values according to your specific GitHub repository.

## License

This library is released under the [MIT License](LICENSE).

## Contributing

If you have suggestions, improvements, or bug reports, feel free to open an issue or create a pull request on the [GitHub repository](https://github.com/RamimIoT/Github_OTA_esp32).

## Support

If you encounter any issues or need assistance, please use the [GitHub Issues](https://github.com/RamimIoT/Github_OTA_esp32/issues) page to report problems or ask questions.
```
