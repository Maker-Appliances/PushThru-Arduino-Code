// Do not alter anything within this TAB (unless you want to)!


/***************************************************

  // Definitions

***************************************************/

int buttonStatus = 0;
int oldButtonStatus = 0;
int blevel;
float bvolt;
float xbvolt;
int level;
int xlevel;
int levelUnMod;
int var;
int connectionCount;
int timeoutAlertCount;
int errorCount;
int errorButtonCount;

/***************************************************

  // Global Functions

***************************************************/
/*
void validateDeviceParameters(ssid, password, objectID) {
  if (ssid == "") {
        alertSlow();
        Serial.println("No Data In SSID field.  Please Gimme some!"); 
  }
}
*/
void workingFast() {
digitalWrite(LED, HIGH);
digitalWrite(buzzer, HIGH);
delay (50);
digitalWrite(buzzer, LOW);
digitalWrite(LED, LOW);
delay (50);
}

void successFast() {
digitalWrite(successLED, HIGH);
digitalWrite(buzzer, HIGH);
delay (50);
digitalWrite(buzzer, LOW);
digitalWrite(successLED, LOW);
delay (50);
}

void alertFast() {
digitalWrite(alertLED, HIGH);
digitalWrite(buzzer, HIGH);
delay (50);
digitalWrite(buzzer, LOW);
digitalWrite(alertLED, LOW);
delay (50);
}

void workingSlow() {
digitalWrite(LED, HIGH);
digitalWrite(buzzer, HIGH);
delay (250);
digitalWrite(buzzer, LOW);
digitalWrite(LED, LOW);
delay (250);
}

void successSlow() {
digitalWrite(successLED, HIGH);
digitalWrite(buzzer, HIGH);
delay (250);
digitalWrite(buzzer, LOW);
digitalWrite(successLED, LOW);
delay (250);
}

void alertSlow() {
digitalWrite(alertLED, HIGH);
digitalWrite(buzzer, HIGH);
delay (250);
digitalWrite(buzzer, LOW);
digitalWrite(alertLED, LOW);
delay (250);

}

void workingFastSilent() {
digitalWrite(LED, HIGH);
delay (75);
digitalWrite(LED, LOW);
delay (25);
}

void successFastSilent() {
digitalWrite(successLED, HIGH);
delay (75);
digitalWrite(successLED, LOW);
delay (25);
}

void alertFastSilent() {
digitalWrite(alertLED, HIGH);
delay (75);
digitalWrite(alertLED, LOW);
delay (25);
}

void workingSlowSilent() {
digitalWrite(LED, HIGH);
delay (400);
digitalWrite(LED, LOW);
delay (100);
}

void successSlowSilent() {
digitalWrite(successLED, HIGH);
digitalWrite(buzzer, HIGH);
delay (400);
digitalWrite(successLED, LOW);
delay (100);
}

void alertSlowSilent() {
digitalWrite(alertLED, HIGH);
digitalWrite(buzzer, HIGH);
delay (400);
digitalWrite(alertLED, LOW);
delay (100);
}
