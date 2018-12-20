void setup() {

  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(successLED, OUTPUT);
  pinMode(alertLED, OUTPUT);
  Serial.begin(115200);
  Serial.println(" ");
  if (batteryCheck == true) {
    Serial.println("Checking my battery...");
    battery_level();
  }
  connectToWifi();
  workingSlowSilent();
  Serial.println("Night!");
  ESP.deepSleep(0);
  
}

void loop() {

};
