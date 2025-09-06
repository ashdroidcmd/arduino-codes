#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "DOCTORSWIFI";
const char* password = "acemc@@c3mc";

// 🔗 Replace with your actual n8n webhook URL
const char* webhookUrl = "https://n8n.acemcbohol.ph/webhook/esp-32";

// Send interval (5 minutes in milliseconds)
const unsigned long interval = 5 * 60 * 1000;
unsigned long lastSentTime = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.println("📶 Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to Wi-Fi!");
}

void loop() {
  unsigned long now = millis();

  // Send every 15 minutes
  if (now - lastSentTime >= interval || lastSentTime == 0) {
    lastSentTime = now;

    float dummyTemp = 99.9; // simulate broken sensor

    // Create full URL
    String url = String(webhookUrl) + "?temp=" + String(dummyTemp, 1);
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

  delay(1000); // Poll loop every second
}
