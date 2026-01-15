#define BLYNK_TEMPLATE_ID "************"
#define BLYNK_TEMPLATE_NAME "GAS Monitoring System"
#define BLYNK_AUTH_TOKEN "*******************"
#define BOT_TOKEN "********************"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define SDA_PIN D2   
#define SCL_PIN D6
#define BLYNK_PRINT Serial
#define DHTPIN D5
#define DHTTYPE DHT11
#define FSR_PIN A0

const char* ssid = "**********";
const char* password = "***************";

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
String chat_id = "6143566022";

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(FSR_PIN, INPUT);
  pinMode(D7, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(D1, OUTPUT);

  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.begin(115200);
  dht.begin();
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setBacklight(HIGH);


  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  secured_client.setInsecure();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  delay(1000);
}

void loop() {
  int sensor = digitalRead(D7);
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  int fsrReading = analogRead(FSR_PIN);
  int force = map(fsrReading, 0, 1023, 0, 1000);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight: ");
  lcd.print(force,1); 
  lcd.print(" F");
  Serial.println("LCD Working...");
  lcd.setCursor(0, 1);
  lcd.print("Temperature ");
  lcd.print(temp,1); 
  lcd.print(" %C");
  Serial.println("LCD Working...");


  if (temp > 33) {
    Blynk.virtualWrite(V0, "There is a Fire!!");
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

  Serial.println("Weight:");
  Serial.println(force);
  Blynk.virtualWrite(V4, force);

  if (force < 900) {
    Serial.println("Gas has been booked");
    Blynk.virtualWrite(V5, "Gas has been booked");
    digitalWrite(D1, HIGH); delay(200);
    digitalWrite(D1, LOW); delay(200);
    digitalWrite(D1, HIGH); delay(200);
    digitalWrite(D1, LOW);
    bot.sendMessage(chat_id, "📦 Gas has been booked successfully!", "");
  } else {
    Serial.println("Gas is Full");
    Blynk.virtualWrite(V5, "Gas is Full");
    digitalWrite(D1, LOW);
  }

  Blynk.run();
  lcd.clear();
  delay(100); // Stabilize Blynk
}
