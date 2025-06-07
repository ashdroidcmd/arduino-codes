const int redPin = 8;
const int yellowPin = 9;
const int greenPin = 10;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // Green light
  digitalWrite(greenPin, HIGH);
  delay(5000); // Green for 5 seconds
  digitalWrite(greenPin, LOW);

  // Yellow light
  digitalWrite(yellowPin, HIGH);
  delay(2000); // Yellow for 2 seconds
  digitalWrite(yellowPin, LOW);

  // Red light
  digitalWrite(redPin, HIGH);
  delay(5000); // Red for 5 seconds
  digitalWrite(redPin, LOW);
}