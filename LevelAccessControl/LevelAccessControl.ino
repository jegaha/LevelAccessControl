#define RELAY_TOGGLE_PIN 'D1' // pin 'D1' or GPIO 5

void setup() {
  pinMode(RELAY_TOGGLE_PIN, OUTPUT); // Set pin as output
}

void loop() {
  digitalWrite(RELAY_TOGGLE_PIN, HIGH); // Turn pin on
  delay(1000);
  digitalWrite(RELAY_TOGGLE_PIN, LOW); // Turn pin off
  delay(1000);
}
