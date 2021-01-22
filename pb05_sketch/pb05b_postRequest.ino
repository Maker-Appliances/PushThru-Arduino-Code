#include "pb05e_fetch.h"

#define HOST "platform.pantri.net"         // host name
#define URI "/v3/device-input/single-post" // uri

#define SCHEME "https" // http or https

#define POST_REQUEST_BODY_MAX_LENGTH (1023)

#define JSON_BUFFER_LEGTH (255)
#define JSON_PARAMETER_NAME_MAC "mac_address"
#define JSON_PARAMETER_NAME_DEVID "device_id"
#define JSON_PARAMETER_NAME_SECRET "secret"

bool MakePantriPostRequest(uint8_t *macAddress)
{
  char macAddressString[17 + 1]; //(6 hexadecimal bytes + 5 colons + null)
  sprintf(macAddressString, "%02X:%02X:%02X:%02X:%02X:%02X", macAddress[5], macAddress[4], macAddress[3], macAddress[2], macAddress[1], macAddress[0]);

  char body[POST_REQUEST_BODY_MAX_LENGTH] = {0};

#if ARDUINOJSON_VERSION_MAJOR != 6 || ARDUINOJSON_VERSION_MINOR < 1
  {
    StaticJsonBuffer<JSON_BUFFER_LEGTH> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root[JSON_PARAMETER_NAME_MAC] = macAddressString;
    root[JSON_PARAMETER_NAME_DEVID] = device_id;
    root[JSON_PARAMETER_NAME_SECRET] = secret;

    root.printTo(body, POST_REQUEST_BODY_MAX_LENGTH);

    Serial.print("Body of request:");
    root.printTo(Serial);
    Serial.println();
  }
#else
  {
    StaticJsonDocument<JSON_BUFFER_LEGTH> bodyJson;

    bodyJson[JSON_PARAMETER_NAME_MAC] = macAddressString;
    bodyJson[JSON_PARAMETER_NAME_DEVID] = device_id;
    bodyJson[JSON_PARAMETER_NAME_SECRET] = secret;

    serializeJson(bodyJson, body, POST_REQUEST_BODY_MAX_LENGTH);

    Serial.print("Body of request:");
    serializeJson(bodyJson, Serial);
    Serial.println();
  }
#endif

  String fullUrl = String(SCHEME) + "://" + HOST + URI;
//  Serial.println(fullUrl);

  fetch.begin(fullUrl);

  fetch.addHeader("Host", HOST);
  fetch.addHeader("Content-Type", "application/json");
  fetch.addHeader("Content-Length", String(strnlen(body, POST_REQUEST_BODY_MAX_LENGTH)));

  int code = fetch.POST(body);
  bool result = CheckPostRequestStatus(code, fetch.readString());
  fetch.clean();

  return result;
}

/*
   Check the server's response and check the HTTP status code to see if the request was successful.
   Returns true on success.
*/
bool CheckPostRequestStatus(int code, String payload)
{
  Serial.println("\n***RETURN PAYLOAD***");
  Serial.println(payload);
  Serial.println("********************\n");

  /* Check if the status code was "201". If so, the request was successful. */
  if (code == HTTP_CODE_CREATED)
  {
    Serial.println("Button Press Sent To Pantri API");

    successSlow();
    successFast();
    successSlow();
    digitalWrite(successLED, HIGH);
    delay(3000);
    digitalWrite(successLED, LOW);
  }
  else
  {
    int extendedErrorCode = 0;
#if ARDUINOJSON_VERSION_MAJOR != 6 || ARDUINOJSON_VERSION_MINOR < 1
    { // ArduinoJson 5
      StaticJsonBuffer<JSON_BUFFER_LEGTH> jsonBuffer;
      JsonObject &root = jsonBuffer.parseObject(payload);
      extendedErrorCode = root["code"];
    }
#else
    { // ArduinoJson 6
      StaticJsonDocument<JSON_BUFFER_LEGTH> doc;
      DeserializationError error = deserializeJson(doc, payload);
      if (error)
      {
        Serial.println("Failed to deserialize response.");
      }
      extendedErrorCode = doc["code"];
    }
#endif
    Serial.printf("Error:\tHTTP status %d", code);
    // The bit below extracts the server code returned in the JSON object.

    // Display Errors Via LEDs
    if (extendedErrorCode == 10)
    {
      Serial.println("Wrong MAC Address for the device ID specified.  Have you loaded the deviceID onto the wrong piece of hardware?");
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
    }
    else if (extendedErrorCode == 20)
    {
      Serial.println("Device ID is not registered on the system.");
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
    }
    else
    {
      Serial.println("Unspecified error chatting to the Pantri API");
      alertSlow();
      workingFast();
      alertSlow();
      workingFast();
      alertSlow();
      workingFast();
      alertSlow();
      workingFast();
      alertSlow();
      workingFast();
      alertSlow();
    };

    return false;
  }

  return true;
};
