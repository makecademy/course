/*************************************************** 
  This is the sketch to test the wireless motion detector 
  using the Parallax PIR sensor with the CC3000 WiFi chip
  
  Written by Marco Schwartz for Open Home System.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <ohs.h>

// Sensor pin
const int sensor_pin = 7; 

// Sensor readout
int old_sensor_value;
int sensor_value;

// Registration
boolean detected = false;
boolean registered = false;
String sensor_id = "motion1";

// Create CC3000 object
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIV2);
                                         
uint32_t ip = cc3000.IP2U32(IP1,IP2,IP3,IP4);

void setup(void)
{
  Serial.begin(115200);
  
  // Initialise the module
  cc3000Init(cc3000);
  
  // Check registration status
  Serial.println("Already registered ?");
  String request = "GET " + String(OHS_FOLDER) + "server.php?device="+ sensor_id +"&phase=registration HTTP/1.0";
  Serial.println(request);
  String result = sendRequestTCP(request, cc3000, ip);
  
  if(result.endsWith("Device registered"))
    {
      Serial.println("Device already registered");
      registered = true;
      detected = true;
    }
    
  // Check detection status
  if (detected == false) {
    
    Serial.println("Already detected ?");
    String request = "GET " + String(OHS_FOLDER) +"server.php?device="+ sensor_id +"&phase=detection HTTP/1.0";
    String result = sendRequestTCP(request, cc3000, ip);
    
    if(result.endsWith("Device already detected"))
    {
      Serial.println("Device already detected");
      detected = true;
    }
  }
  
  // First readout
  int sensor_value = digitalRead(sensor_pin);
  old_sensor_value = sensor_value;
  
  // End of setup
  Serial.println("Detected:");
  Serial.println(detected);
  Serial.println("Registered:");
  Serial.println(registered);
}

void loop(void)
{
  // Detection phase 
  if (registered == false && detected == false)
  {
    Serial.println("Waiting for detection");
    String request = "GET " + String(OHS_FOLDER) + "server.php?device="+ sensor_id +"&phase=detection HTTP/1.0";
    String result = sendRequestTCP(request, cc3000, ip);
  
    // Sensor detected ?
    if(result.endsWith("Device detected"))
    {
      Serial.println("Device detected");
      detected = true;
    }
  
  // Retry every second
  delay(1000);

  }
  
  // Registration phase 
  if (registered == false && detected == true)
  {
    Serial.println("Waiting for registration");
    String request = "GET " + String(OHS_FOLDER) + "server.php?device="+sensor_id+"&phase=registration HTTP/1.0";
    String result = sendRequestTCP(request, cc3000, ip);
  
  // Request received ?  
  if(result.endsWith("Device registered"))
    {
      Serial.println("Sensor Registered");
      registered = true;
    }
  
  // Retry every second
  delay(1000);

  }
  
  // Normal operation
  if (registered == true) {
 
    // Read sensor
    int sensor_value = digitalRead(sensor_pin);
    
    // If the value didn't change, transmit nothing
    if (sensor_value == old_sensor_value) {
      delay(1000);
    }
    
    // Otherwise, connect to server to transmit data
    else {
       if (sensor_value == 1) {
          String request = "GET " + String(OHS_FOLDER) + "server.php?device="+sensor_id+"&phase=receive" + "&data=On HTTP/1.0";
          String result = sendRequestTCP(request, cc3000, ip);
       }
       else {
          String request = "GET " + String(OHS_FOLDER) + "server.php?device="+sensor_id+"&phase=receive" + "&data=Off HTTP/1.0";
          String result = sendRequestTCP(request, cc3000, ip);
       }
    
      old_sensor_value = sensor_value;
    
    }
  }
}
