#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// === WiFi Credentials ===
const char* ssid = "DOCTORSWIFI";
const char* password = "acemc@@c3mc";

// === Backend URLs Railway and N8N ===
const char* backendUrl = "https://mis-server-monitor-server-production.up.railway.app/api/sensor-data";
const char* webhookUrl = "https://n8n.acemcbohol.ph/webhook/esp-32";

// === DHT Sensor Setup ===
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// === Time Interval ===
const int intervalMinutes = 5;
const unsigned long interval = intervalMinutes * 60UL * 1000UL;
unsigned long lastSentTime = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("📶 Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to Wi-Fi!");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastSentTime >= interval || lastSentTime == 0) {
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temp) || isnan(humidity)) {
      Serial.println("❌ Failed to read from DHT sensor!");
      return;
    }

    // Create JSON payload
    String payload = "{";
    payload += "\"temp\":" + String(temp, 2) + ",";
    payload += "\"humidity\":" + String(humidity, 2);
    payload += "}";

    Serial.println("📤 Sending to both endpoints: " + payload);

    sendToEndpoint(backendUrl, payload, "Backend");
    sendToEndpoint(webhookUrl, payload, "n8n");

    lastSentTime = currentTime;
  }
}

void sendToEndpoint(const char* url, const String& payload, const char* label) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(payload);
    if (httpCode > 0) {
      Serial.printf("✅ Sent to %s! Response code: %d\n", label, httpCode);
    } else {
      Serial.printf("❌ Failed to send to %s. Error code: %d\n", label, httpCode);
    }

    http.end();
  } else {
    Serial.printf("⚠️ Wi-Fi not connected. Cannot send to %s\n", label);
  }
}
