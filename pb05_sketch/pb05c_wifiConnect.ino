void wifiErrorDiag() {
  if (WiFi.status() == WL_CONNECT_FAILED) {
    Serial.println("");
    Serial.println("Connection Failed.  Possibly a wrong WIFI Password mate?  Sort it out will ya.");
    Serial.println("");
    alertSlowSilent();
    // Two Red Beeps
    alertFast();
    alertFast();

  }
  else if (WiFi.status() == WL_NO_SSID_AVAIL) {
    Serial.println("");
    Serial.print("I can't see \"");
    Serial.print(ssid);
    Serial.println("\".  Have you spelt the WIFI SSID properly, or is the WIFI station switched off?  Check to see if you can see it on your phone or laptop (other WIFI enabled devices available)?");
    Serial.println("");
    alertSlowSilent();
    // Three Red Beeps
    alertFast();
    alertFast();
    alertFast();
  }
  else {
    Serial.println("");
    Serial.println("Not Connected To WiFi.  Will try again shortly.");
    Serial.println("");
    alertSlowSilent();
    // Four Red Beeps
    alertFast();
    alertFast();
    alertFast();
    alertFast();
  }
}


int wifiRetry = 1;

void connectToWifiSilent() {
  Serial.print("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Disconnects from previous WiFi session
  WiFi.disconnect();
  // Disable AP_SSID publication in Client mode
  WiFi.mode(WIFI_STA);
  // Starts WiFi Connection
  WiFi.begin(ssid, password);
  connectionCount = 30;
  Serial.println("");
  Serial.println("Connection timeout in: ");

  while (WiFi.status() != WL_CONNECTED && connectionCount > 0) {

    workingFastSilent();
    delay(400);
    connectionCount--;
    Serial.print(connectionCount);
    Serial.print(" Current WiFi Status = ");
    Serial.print(WiFi.status());
    Serial.println(", ");
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Setup Complete");
    successSlow();
    successSlow();
    //Now to push a REST API Post to the server
    httpsPost();
  }

  else {

    wifiErrorDiag();

  };

  if (wifiRetry < 2) {

    //Now try to connect to WIFI again (silently)
    wifiRetry ++;

    timeoutAlertCount = 1;
    
    while (timeoutAlertCount <= 3) {
      timeoutAlertCount++;
    }

    // Add a 15 second delay in between connections

    delay(15000);

    connectToWifiSilent();

  }

  if (wifiRetry == 2) {
    delay(2000);
    Serial.println("Sorry, I just can't connect.  I give up.  I'm going back to sleep.  Check my settings & your wifi setup please.");
    digitalWrite(alertLED, HIGH);
    digitalWrite(alertLED, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(4000);
    digitalWrite(buzzer, LOW);
    delay(16000);
    digitalWrite(alertLED, LOW);
    digitalWrite(alertLED, LOW);

    //Return to deep sleep
    workingSlowSilent();
    ESP.deepSleep(0);
  }

}


// use the ssid and password to connect to the your WiFi
void connectToWifi() {

  Serial.print("");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Disable AP_SSID publication in Client mode
  WiFi.mode(WIFI_STA);

  // Starts WiFi Connection
  WiFi.begin(ssid, password);

  connectionCount = 30;
  Serial.println("");

  Serial.println("Connection timeout in: ");

  // loop to check if connected to the wi fi network
  while (WiFi.status() != WL_CONNECTED && connectionCount > 0) {
    workingFast();
    delay(400);
    connectionCount--;
    Serial.print(connectionCount);
    Serial.print(" Current WiFi Status = ");
    Serial.print(WiFi.status());
    Serial.println(", ");
  }

  // we're connected to the wi fi network
  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Setup Complete");

    successSlow();

    //Now to push a REST API Post to the server
    httpsPost();
  }
  else { // else we never connected to the network, inform the user of the error using the buzzer and LED

    wifiErrorDiag();
    delay(1000);
    connectToWifiSilent();
  }
}
