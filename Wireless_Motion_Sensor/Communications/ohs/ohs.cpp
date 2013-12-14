#include "ohs.h"

void cc3000Init(Adafruit_CC3000 cc3000)
{
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }

  // Connect to  WiFi network
  cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
  Serial.println(F("Connected!"));
    
  // Display connection details
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }
  
}

String sendRequestTCP (String request, Adafruit_CC3000 cc3000, uint32_t ip) {
  
  Adafruit_CC3000_Client client;
  unsigned long startTime;

  String result = "";
    
  Serial.println(F("\r\nAttempting connection..."));
  client = cc3000.connectTCP(ip, SERVER_PORT_TCP);

  Serial.print(F("Connected..."));

    if(client.connected()) {
      Serial.print(F("Issuing request..."));
      startTime = millis();
      
      // Assemble and issue request packet
      client.println(request);
      client.println();

      } 
      
      Serial.print(F("\r\nAwaiting response..."));

      while (client.connected()) {
        while (client.available()) {
          char c = client.read();
          result = result + c;
          Serial.print(c);
        }
      } 

    client.close();

    Serial.println("Time to connect, send & read:");
    Serial.println(millis() - startTime);

    return result;
    
}