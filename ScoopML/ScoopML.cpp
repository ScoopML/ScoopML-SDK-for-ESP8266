#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
const char *server = "https://api.climacell.co/v3/weather/realtime";
string text;
HTTPClient http;
void loop() {
  Serial.println("Connecting to the HTTP server....");
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  char apiURL[1024];
  Serial.println("Building URL...");
  sprintf(apiURL,server);
  
  Serial.printf("API URL=%s\r\n",apiURL);
  if (http.begin(*client, apiURL)) {
    Serial.println("Connected");
    http.addHeader("Accept", "application/json");
    int code = http.POST("payload",text);
    Serial.printf("HTTP Code [%d]", code);
    if (code > 0) {
      if (code == HTTP_CODE_OK || code == HTTP_CODE_MOVED_PERMANENTLY) {
        Serial.println("GET OK");
        String payload = http.getString();
        Serial.println(payload);
        Serial.println("...JSON..");
      }
    }
    else {
      Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(code).c_str());
    }
  }
