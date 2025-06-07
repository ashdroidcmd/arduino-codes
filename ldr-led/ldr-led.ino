const int ldrPin = A0;      // Analog pin connected to LDR voltage divider
const int ledPin = 9;       // Digital pin connected to LED
int lightLevel;             // Variable to store LDR value
const int threshold = 500;  // Light threshold (adjust based on ambient conditions)

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // Optional: Monitor light levels in Serial Monitor
}

void loop() {
  lightLevel = analogRead(ldrPin); // Read LDR value (0–1023)

  Serial.println(lightLevel); // Debug: Show value in Serial Monitor

  if (lightLevel < threshold) {
    digitalWrite(ledPin, HIGH); // It's dark → turn on LED
  } else {
    digitalWrite(ledPin, LOW);  // It's bright → turn off LED
  }

  delay(200); // Small delay for stability
}