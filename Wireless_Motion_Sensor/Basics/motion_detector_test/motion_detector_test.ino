/*************************************************** 
  This is a sketch to test the motion detection using the Parallax PIR sensor.
  
  Written by Marco Schwartz for Open Home System.
 ****************************************************/
 
const int sensor_pin = 7; // Sensor pin

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // Get sensor value
  int sensor_value = digitalRead(sensor_pin);
  
  // Print on serial
  Serial.println(sensor_value);
  delay(10);
}
