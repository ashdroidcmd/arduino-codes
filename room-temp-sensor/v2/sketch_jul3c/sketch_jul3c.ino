#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// Wi-Fi credentials
const char* ssid = "DOCTORSWIFI";
const char* password = "acemc@@c3mc";

// Webhook URL
const char* webhookUrl = "https://n8n.acemcbohol.ph/webhook/esp-32";

// DHT11 setup
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Interval settings
const unsigned long interval = 5 * 60 * 1000;  // 5 minutes in milliseconds
unsigned long lastSentTime = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("📶 Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to Wi-Fi!");
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temp) || isnan(humidity)) {
    Serial.println("❌ Sensor read failed.");
    delay(2000);
    return;
  }

  Serial.print("🌡️ Temp: ");
  Serial.print(temp);
  Serial.print(" °C | 💧 Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  unsigned long now = millis();

  if (temp >= 20.0 && (now - lastSentTime >= interval || lastSentTime == 0)) {
    lastSentTime = now;

    // Create webhook URL with data
    String url = String(webhookUrl) + "?temp=" + String(temp, 1) + "&humidity=" + String(humidity, 1);
    Serial.print("🌐 Sending to: ");
    Serial.println(url);

    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("✅ Sent! HTTP %d\n", httpCode);
    } else {
      Serial.printf("❌ Send failed! Code: %d\n", httpCode);
    }

    http.end();
  }

  delay(10000);  // Allow DHT11 to stabilize
}
