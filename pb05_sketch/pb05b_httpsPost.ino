template <class T> void sendWithDebug(T dataToSend, WiFiClientSecure& client); // function prototype
bool checkHTTPstatusOK(WiFiClientSecure& client);

#define HOST "api.pantri.net"  // The host name of the server (without "http://" and without any slashes)
#define URI "/classes/DeviceActivity/"  // The URI of the resource you wish to send the request to
#define PORT 443  // port 443 for HTTPS

#define FINGERPRINT "78 68 E5 9E 5D 47 18 03 7D 50 08 0F D9 A2 F2 DF BF CE 1F B6"   //  This is the latest server certificate fingerprint

const char* httpHeaders =    "POST " URI " HTTP/1.1\r\n"
                             "Host: " HOST "\r\n"
                             "Content-Type: application/json\r\n"
                             "X-Parse-Application-Id: pantri_api\r\n"
                             "Connection: close\r\n"
                             "Content-Length: "; // + bodyLength + "\r\n"
// "\r\n"
const char* body_1 =         "{\"ReceiptBoolean\":true,\"Device\":{\"__type\":\"Pointer\",\"className\":\"Device\",\"objectId\":\"";
char objectIDstr[11];     // + objectID        (4 294 967 295 + null)
const char* body_2 =         "\"},\"macAddress\":\"";
char MACstr[17 + 1];      // + MACstr          (6 hexadecimal bytes + 5 colons + null)
const char* body_3 =         "\"}";

size_t fixedBodyLength;

bool httpsPost() {
  uint8_t MAC[6];
  WiFi.macAddress(MAC);
  sprintf(MACstr, "%02X:%02X:%02X:%02X:%02X:%02X", MAC[5], MAC[4], MAC[3], MAC[2], MAC[1], MAC[0]);

  fixedBodyLength = strlen(body_1) + strlen(body_2) + strlen(body_3) + strlen(MACstr);

  /* Convert the objectID to a string */
  size_t bodyLength = fixedBodyLength;
  bodyLength += sprintf(objectIDstr, "%u", objectID);

  /* Connect to the server */

  WiFiClientSecure client; // Use WiFiClientSecure class to create TLS (HTTPS) connection
  if (!client.connect(HOST, PORT)) {   // Connect to the server on port 443
    Serial.println("Connection failed");    // If the connection fails, stop and return
    alertSlow();
    alertFast();
    alertSlow();
    alertFast();
    alertSlow();
    return false;
  }

  if (!client.verify(FINGERPRINT, HOST)) {   // Check the SHA-1 fingerprint of the SSL (TLS) certificate
    Serial.println("SSL Certificate doesn't match");
    alertSlow();
    alertSlow();
    alertSlow();
    alertSlow();
    alertSlow();
    client.stop();
    return false; // if it doesn't match, it's not safe to continue
  }

  /* Send the request to the server,
     write headers, lenght of the body and body over the TCP connection
     and print them to the Serial Monitor as well */

  sendWithDebug(httpHeaders, client);
  sendWithDebug(bodyLength, client);
  sendWithDebug("\r\n\r\n", client);
  sendWithDebug(body_1, client);
  sendWithDebug(objectID, client);
  sendWithDebug(body_2, client);
  sendWithDebug(MACstr, client);
  sendWithDebug(body_3, client);

  client.flush(); // wait for the transmission to finish

  // Check the server's response to see if the request was successful
  bool HTTPstatusOK = checkHTTPstatusOK(client);

  client.stop(); // Close the connection

  return HTTPstatusOK;
}

template <class T> void sendWithDebug(T dataToSend, WiFiClientSecure& client) {
  client.print(dataToSend);
  Serial.print(dataToSend);
}

/*
   Check the server's response and check the HTTP status code to see if the request was successful.
   Returns true on success.
*/

bool checkHTTPstatusOK(WiFiClientSecure& client) {
  unsigned long timeout = millis();

  /* Read until the first space (SP) of the response. */
  char data = 0;
  while (data != ' ') {  // wait for a space character
    if (client.available() > 0) {  // if theres a character to read from the response
      data = client.read();  // read it
    }
    // if the space doesn't arrive within 5 seconds, timeout and return
    if (millis() - timeout > 5000) {
      Serial.println("");
      Serial.println("Error: Client Timeout!  There might be an issue with the Pantri Server...");

      alertSlow();
      alertSlow();
      alertFast();
      alertFast();

      return false;
    }
    yield();
  }

  /* The three next characters are the HTTP status code.
      Wait for 3 characters to be received, and read them into a buffer. */
  while (client.available() < 3) {
    if (millis() - timeout > 5000) {
      Serial.println("\r\nError:\tClient Timeout !");
      return false;
    }
    yield();
  }
  char statusCodeStr[4];  // three digits + null
  client.read((uint8_t*) statusCodeStr, 3);  // read the status code into the buffer
  statusCodeStr[3] = '\0';  // add terminating null character, needed for strcmp()

  String payload = client.readStringUntil('\n');  // Get the response
  Serial.println("");
  Serial.println("***RETURN PAYLOAD***");
  Serial.println(payload);
  Serial.println("********************");
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(payload);
  const int connectionCodes = root["code"];

  /* Check if the status code was "201". If so, the request was successful. */
  if (strcmp(statusCodeStr, "201") == 0) {
    Serial.println("");
    Serial.println("Button Press Sent To Pantri API");
    successSlow();
    successFast();
    successSlow();
    digitalWrite(successLED, HIGH);
    delay(3000);
    digitalWrite(successLED, LOW);
  }

  if (strcmp(statusCodeStr, "201") != 0) {
    Serial.print("\r\nError:\tHTTP status ");
    Serial.println(statusCodeStr);

    // The bit below extracts the server code returned in the JSON object.
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }

    // Display Errors Via LEDs
    if (connectionCodes == 10) {
      Serial.println("Wrong MAC Address for the device ID specified.  Have you loaded the deviceID onto the wrong piece of hardware?");
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
    }
    else if (connectionCodes == 20) {
      Serial.println("Device ID is not registered on the system.");
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
      alertSlow();
    } else {
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

/*

   A Huge thankyou to PieterP on http://forum.arduino.cc for assisting in getting this working - http://forum.arduino.cc/index.php?topic=497048.msg3393151#msg3393151

*/
