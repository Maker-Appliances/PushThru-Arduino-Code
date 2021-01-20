// Do not alter anything within this TAB (unless you want to)!

/***************************************************

  // Definitions

***************************************************/

#define DELAY_FAST_ms (50)
#define DELAY_SLOW_ms (250)

int buttonStatus = 0;
int oldButtonStatus = 0;
int blevel;
float bvolt;
float xbvolt;
int level;
int xlevel;
int levelUnMod;
int connectionCount;
int timeoutAlertCount;
int errorCount;
int errorButtonCount;

enum IndicationType
{
  Work = 0,
  Success,
  Alert
};

/***************************************************

  // Global Functions

***************************************************/
/*
  void validateDeviceParameters(ssid, password, device_id) {
  if (ssid == "") {
        alertSlow();
        Serial.println("No Data In SSID field.  Please Gimme some!");
  }
  }
*/


void Indicate(IndicationType type, int pauseLenght = 50, bool silent = false)
{
  int led = 0;

  switch (type)
  {
    case Work:
      led = LED;
      break;
    case Success:
      led = successLED;
      break;
    case Alert:
      led = alertLED;
      break;
    default:
      return;
  }

  digitalWrite(led, HIGH);
  if (!silent) digitalWrite(buzzer, HIGH);
  delay(pauseLenght);
  if (!silent) digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);
  delay(pauseLenght);
}

void Working(bool slow = false, bool silent = false)
{
  Indicate(Work, slow ? DELAY_SLOW_ms : DELAY_FAST_ms, silent);
}

void Successing(bool slow = false, bool silent = false)
{
  Indicate(Success, slow ? DELAY_SLOW_ms : DELAY_FAST_ms, silent);
}

void Alerting(bool slow = false, bool silent = false)
{
  Indicate(Alert, slow ? DELAY_SLOW_ms : DELAY_FAST_ms, silent);
}

void workingFast()
{
  Working();
}

void successFast()
{
  Successing();
}

void alertFast()
{
  Alerting();
}

void workingSlow()
{
  Working(true);
}

void successSlow()
{
  Successing(true);
}

void alertSlow()
{
  Alerting(true);
}

void workingFastSilent()
{
  Working(false, true);
}

void successFastSilent()
{
  Successing(false, true);
}

void alertFastSilent()
{
  Alerting(false, true);
}

void workingSlowSilent()
{
  Working(true, true);
}

void successSlowSilent()
{
  Successing(true, true);
}

void alertSlowSilent()
{
  Alerting(true, true);
}
