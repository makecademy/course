#include "DHT.h"
#include<stdlib.h>

#define DHTPIN 7    
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Setup
void setup(void)
{
  
  dht.begin();
  
  Serial.begin(115200);

}

void loop(void)
{
  
    float h = dht.readHumidity();
    float t = dht.readTemperature();
        
    Serial.print("Temperature:");
    Serial.println(t);
    Serial.print("Humidity:");
    Serial.println(h);
    Serial.println();
    
    delay(2000);
  
}
