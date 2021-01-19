/***************************************************

  // Libraries

***************************************************/

#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

/**************************************************
  
  Pantri PB05 a.k.a:

  --- Push Thru ---

  ALPHA RELEASE V 1.0.1
    V 1.0.1 - Updated for 2021 V3 system.
  V 1.0.1 - Updated SSL Fingerprint.
  V 1.0.0 - REST Post description updated to match general API convention, url & certificate altered to official domain.  Numbered V1 - ready for production!
  V 0.3.1 - deepSleep HTTPS release (alpha)
  V 0.2.1 - HTTPS Building pre deepSleep (None working)
  V 0.1.1 - Working HTTP release (alpha)

  Distributed under GNU General Public License V3

  This sketch comprises of the following tabs:
 - pb01sketch
 - pb01a_operables    - Miscellaneous global functions live here.
 - pb01b_httpsPost    - The functions that send a message to the Pantri API once you've connected to the internet.
 - pb01c_wifiConnect  - The functions that connect A Bit Pushy to your WiFi Connection.
 - pb01d_battery      - The functions monitoring the battery voltage are located here.
 - pb01z_Setup_Loop    - The principle setup & loop functions operate here.

*/

// Insert your personal WLAN device (home router, etc) credentials inside the speach marks.

const char *ssid = ""; //  This is the name or your wireless network

const char *password = ""; //  This is your wireless network password

const char *device_id = ""; //  This is the device ID issued to your device (in the Powered by Pantri App device config)

const char *secret = ""; //  This is the secret you gave your device (in the Powered by Pantri App device config)

bool batteryCheck = true; //  Set this to false if you want to disable the battery check loop

//  This section defines pins that link your Adafruit Arduino Huzzah ESP8266 Feather board to your button, buzzer & LED.

int buzzer = 15;     // This is the pin output leading to your Buzzer
int LED = 12;        // This is the pin output leading to your blue status LED
int successLED = 14; // This is the pin output leading to your green success LED
int alertLED = 13;   // This is the pin output leading to the red alert LED

/***************************************************

  LICENSES

  This section declares any legal obligations with relation to elements of code obtained from other repositories:

  BATTERY SCRIPT
  Adafruit IO Trigger Example
  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board:
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/product/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Todd Treece for Adafruit Industries.

  MIT license, all text above must be included in any redistribution
  
****************************************************/
