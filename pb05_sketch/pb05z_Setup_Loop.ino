#include "fetch.h"
#include "timeSync.h"

void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(successLED, OUTPUT);
  pinMode(alertLED, OUTPUT);

  Serial.begin(115200);
  Serial.println(" ");

  if (batteryCheck == true)
  {
    Serial.println("Checking my battery...");
    battery_level();
  }

  connectToWifi();
  workingSlowSilent();

  timeSync.begin();
}

void loop() {
  const char* host = "https://httpbin.org/get";
  String payload;

  fetch.begin(host);
  fetch.addHeader("Host", "httpbin.org");
  int result = fetch.GET();
  if (result == HTTP_CODE_OK)
  {
    payload = fetch.readString();
    Serial.println(payload);
  }
  else
  {
    Serial.printf("Request failed: %d\n", result);
  }
  fetch.clean();

  Serial.println("Night!");
  ESP.deepSleep(0);
};
