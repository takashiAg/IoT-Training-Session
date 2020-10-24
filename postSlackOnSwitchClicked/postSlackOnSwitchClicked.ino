#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#define SWITCH_PORT 4
#define USE_SERIAL Serial
#define URI_GET "https://hook.integromat.com/8y2i2ajavei5fk2fhjym8u2clv0zrm50?name=Ryosuke&message=Hello&channel=iot-test"
#define SSID "Garedge"
#define PASSWORD "wXKvUA6v"

#define LED_BUILTIN 2

WiFiMulti wifiMulti;
boolean switchValueBefore = false;

void setup() {
  Serial.begin(115200);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }
  pinMode(SWITCH_PORT, INPUT );
  pinMode(LED_BUILTIN, OUTPUT);
  wifiMulti.addAP(SSID, PASSWORD);
}


int access_server(String *response, String *error) {
  int isError = 0;
  if ((wifiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
    http.begin(URI_GET); //HTTP

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        *response = payload;
      }
    } else {
      isError = 1;
      *error = http.errorToString(httpCode).c_str();
    }

    http.end();
  }
  return isError;
}

void loop() {
  delay(10);
  // put your main code here, to run repeatedly:
  boolean switchValue = digitalRead(SWITCH_PORT);
  if (switchValue != switchValueBefore)
  {
    if (switchValue) {
      USE_SERIAL.println("accessing to server");
      String responseString = "";
      String error = "";
      int isError = access_server(&responseString, &error);
    }
    else
      Serial.println("LED turns off");
  }
  switchValueBefore = switchValue;
}
