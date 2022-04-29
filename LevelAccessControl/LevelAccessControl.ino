#include "settings.h"

#include "Relay.h"
#include "card_reader.h"
#include "ota.h"

Relay relay = Relay(RELAY_TOGGLE_PIN);

void setup() {
  Serial.begin(9600);

  setupOta();
  setupRfidReceiver();
}

void loop() {
  loopOta();
  loopRfidReceiver();
}
