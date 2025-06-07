const int potPin = A0;     // Analog input pin connected to potentiometer
const int ledPin = 9;      // PWM output pin connected to LED

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);               // Read analog value (0–1023)
  int brightness = map(potValue, 0, 1023, 0, 255); // Convert to PWM range (0–255)
  analogWrite(ledPin, brightness);                 // Set LED brightness
}