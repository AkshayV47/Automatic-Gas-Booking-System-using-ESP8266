#define BLYNK_TEMPLATE_ID "************"
#define BLYNK_TEMPLATE_NAME "GAS Monitoring System"
#define BLYNK_AUTH_TOKEN "************************"

#include <BlynkSimpleEsp8266.h>    
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#define BLYNK_PRINT Serial
#define DHTPIN D5
#define DHTTYPE DHT11
#define FSR_PIN A0

const char* ssid ="*********";
const char* password ="**********";

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  pinMode(FSR_PIN, INPUT);
  pinMode(D7, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(D1, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  delay(1000);
  dht.begin();
  Serial.begin(115200);
}

void loop() {
  int sensor = digitalRead(D7);
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  if (temp > 31){
  Blynk.virtualWrite(V0, "There is a Fire!!");       // V0 - for satus of fire
  Serial.println("There is a Fire!!");
  Blynk.virtualWrite(V1, temp);                     // Temp - gauge
  }
  else{
  Blynk.virtualWrite(V0, "It's Normal");       // V0 - for satus of fire
  Serial.println("It's Normal");
  }
  Serial.print("Temperature : ");
  Serial.println(temp);
  Serial.print("Humidity : ");
  Serial.println(hum);

  Serial.print("Gas : ");
  Serial.println(sensor);
  Blynk.virtualWrite(V2, sensor);                // gas - Gauge
  if(sensor == HIGH){
  Serial.println("There is no Gas leakage");
  Blynk.virtualWrite(V3,"There is no Gas leakage" );     // gas status 
  digitalWrite(D1, LOW); 
  }
  else if(sensor == LOW){                    
  Serial.println("There is a Gas leakage");
  Blynk.virtualWrite(V3,"There is a Gas leakage");
  digitalWrite(D1, HIGH);
  delay(2000);
  }

  int fsrReading = analogRead(FSR_PIN);  
  float force = map(fsrReading, 0, 1023, 0, 1000); 
  Serial.println("Weight:");
  Serial.println(force);
  Blynk.virtualWrite(V4,force);           // Weight value
  if(force < 900){
    Serial.println("Gas has been booked");
    Blynk.virtualWrite(V5,"Gas has been booked");   // gas booking status
    digitalWrite(D1, HIGH);                          // buzzer function
    delay(200);
    digitalWrite(D1, LOW);
    delay(200);
    digitalWrite(D1, HIGH);
    delay(200);
    digitalWrite(D1, LOW);
  }
  else{
    Serial.println("Gas is Full");
    Blynk.virtualWrite(V5,"Gas is Full"); 
    digitalWrite(D1, LOW); 
  }
  Blynk.run();
  delay(1000);
}


