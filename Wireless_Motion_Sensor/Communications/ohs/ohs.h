#ifndef String_h
#include <String.h>
#endif

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
	#include <pins_arduino.h>
#endif

#include <Adafruit_CC3000.h>

// WiFi network (change with your settings !)
#define WLAN_SSID       "yourNetwork"        // cannot be longer than 32 characters!
#define WLAN_PASS       "yourPass"
#define WLAN_SECURITY   WLAN_SEC_WPA2 // This can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

// Server port & IP
#define SERVER_PORT_TCP 80
#define OHS_FOLDER "/ohs_test/"
#define IP1 192
#define IP2 168
#define IP3 0
#define IP4 1

// Define CC3000 chip pins
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// CC3000 timing settings
const unsigned long
  dhcpTimeout     = 60L * 1000L, // Max time to wait for address from DHCP
  connectTimeout  = 15L * 1000L, // Max time to wait for server connection
  responseTimeout = 15L * 1000L; // Max time to wait for data from server

// Functions
String sendRequestTCP (String request, Adafruit_CC3000 cc3000, uint32_t ip);

void cc3000Init(Adafruit_CC3000 cc3000);
