#include "pb05e_fetch.h"
#include "pb05h_timeSync.h"

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

  if (connectToWifi() == false)
  {
    Serial.println("Can't connect WiFi!\nNigth!");
    ESP.deepSleep(0);
  }
  workingSlowSilent();

  timeSync.begin();
}

void loop()
{
  Serial.println("Try to make Pantri post request ...");
  uint8_t macAddress[WL_MAC_ADDR_LENGTH];
  WiFi.macAddress(macAddress);
  if (MakePantriPostRequest(macAddress))
  {
    Serial.println("Pantri post request succeeded!");
  }
  else
  {
    Serial.println("Pantri post request failed!");
  }

  Serial.println("Night!");
  ESP.deepSleep(0);
};
