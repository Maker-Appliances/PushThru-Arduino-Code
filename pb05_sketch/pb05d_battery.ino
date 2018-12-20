void battery_alert() {
  // Low Battery
  Serial.println("");
  Serial.print("Battery level: "); Serial.print(blevel); Serial.print("%"); Serial.print(" / "); Serial.print(bvolt); Serial.println(" v");
  Serial.println("");

  var = 0;

  if (blevel < 10) {

    Serial.println("Low Battery");

    int battLowCount = 0;

    while (battLowCount < 3) {

      workingFast();
      successFast();
      alertFast();

      battLowCount ++;

    }

    alertSlow();

    /* Send the device back to sleep without doing an API call.
      The theory being that powering up from a flat battery wil be
      when the unit is flat & so we won't want to make an API call */
    workingSlowSilent();
    Serial.println("I'm out of energy. Going to sleep. Let me recharge my battery...PLEASE!");
    ESP.deepSleep(0);

  }
  // Fully Charged Battery
  else if (blevel > 98) {
    Serial.println("Battery Is Charged");
    successSlow();
  }
  else {
    // Do nothing if battery is neither fully charged or low!
  }

}

void battery_level() {

  // read the battery level from the ESP8266 analog in pin.
  // analog read level is 10 bit 0-1023 (0V-1V).
  // our 1M & 220K voltage divider takes the max
  // lipo value of 4.2V and drops it to 0.758V max.
  // this means our min analog read value should be 580 (3.14V)
  // and the max analog read value should be 774 (4.2V).

  level = analogRead(A0);
  levelUnMod = analogRead(A0);
  // convert battery level to percent
  blevel = map(level, 580, 774, 0, 100);
  xlevel = level * 100;
  xbvolt = map(xlevel, 58000, 77400, 314, 420);
  bvolt = xbvolt / 100;
  battery_alert();

}
