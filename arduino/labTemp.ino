#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Endexe"
#define WIFI_PASSWORD "Anderson1105"

// Insert Firebase project API Key
#define API_KEY "AIzaSyClPSByhl-G5yExr49SdFxxcC3LUfYSmGA"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://lab-temp-92a6c-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    if (Firebase.RTDB.getJSON(&fbdo, "experiment/JHYzRqJbr35akhKqbSsU_")) {
      if (fbdo.dataType() == "json") {
        FirebaseJson &jsonObject = fbdo.jsonObject();
        FirebaseJsonData jsonData;
        if (jsonObject.get(jsonData, "Kp")) {
          String Kp = jsonData.stringValue;
          Serial.println(Kp);
        }
      }
    } else {
      Serial.println(fbdo.errorReason());
    }
  }
}
