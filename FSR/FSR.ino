#define FSR_PIN A0

void setup() {
  Serial.begin(115200);  
  Serial.println("FSR Weight Sensor on ESP8266");
  delay(1000);  
}

void loop() {
  int fsrReading = analogRead(FSR_PIN); 
  float voltage = fsrReading * (3.3 / 1023.0);

  float force = map(fsrReading, 0, 1023, 0, 1000); 

  if (force < 10) force = 0;  

  Serial.print("Analog Reading: ");
  Serial.print(fsrReading);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print(" V | Estimated Weight: ");
  Serial.print(force);
  Serial.println(" grams");

  delay(500);  
}