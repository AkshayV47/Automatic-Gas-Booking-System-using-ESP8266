#define BLYNK_TEMPLATE_ID "************"
#define BLYNK_TEMPLATE_NAME "GAS Monitoring System"
#define BLYNK_AUTH_TOKEN "*********************"
#define BOT_TOKEN "*******************"

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <DHT.h>

#define BLYNK_PRINT Serial
#define DHTPIN D5
#define DHTTYPE DHT11
#define FSR_PIN A0

// WiFi credentials
const char* ssid = "***********";
const char* password ="**************";

// Telegram bot setup
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
String chat_id = "6240494160";   // <-- Replace with your Telegram Chat ID

// Sensors
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(FSR_PIN, INPUT);
  pinMode(D7, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(D1, OUTPUT);

  Serial.begin(115200);
  dht.begin();

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  secured_client.setInsecure();  

  // Connect Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  delay(1000);
}

void loop() {
  int sensor = digitalRead(D7);
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  if (temp > 31) {
    Blynk.virtualWrite(V0, "There is a Fire!!"); // Fire status
    Serial.println("There is a Fire!!");
    bot.sendMessage(chat_id, "🔥 Fire has been detected!", "");
    Blynk.virtualWrite(V1, temp);
    delay(1000);
  } else {
    Blynk.virtualWrite(V0, "It's Normal");
    Serial.println("It's Normal");
  }
  Serial.print("Temperature : ");
  Serial.println(temp);
  Serial.print("Humidity : ");
  Serial.println(hum);

  Serial.print("Gas : ");
  Serial.println(sensor);
  Blynk.virtualWrite(V2, sensor);

  if (sensor == HIGH) {
    Serial.println("There is no Gas leakage");
    Blynk.virtualWrite(V3, "There is no Gas leakage");
    digitalWrite(D1, LOW);
  } else {
    Serial.println("There is a Gas leakage");
    Blynk.virtualWrite(V3, "There is a Gas leakage");
    bot.sendMessage(chat_id, "💨 Gas leakage is detected!", "");
    digitalWrite(D1, HIGH);
    delay(2000);
  }

  // Weight (FSR) - Gas Booking System
  int fsrReading = analogRead(FSR_PIN);
  float force = map(fsrReading, 0, 1023, 0, 1000);
  Serial.println("Weight:");
  Serial.println(force);
  Blynk.virtualWrite(V4, force);

  if (force < 900) {
    Serial.println("Gas has been booked");
    Blynk.virtualWrite(V5, "Gas has been booked");

    // Buzzer alert
    digitalWrite(D1, HIGH); delay(200);
    digitalWrite(D1, LOW); delay(200);
    digitalWrite(D1, HIGH); delay(200);
    digitalWrite(D1, LOW);

    // Telegram Notification
    bot.sendMessage(chat_id, "📦 Gas has been booked successfully!", "");
    delay(1000);
  } else {
    Serial.println("Gas is Full");
    Blynk.virtualWrite(V5, "Gas is Full");
    digitalWrite(D1, LOW);
  }

  Blynk.run();
  delay(1000);
}
