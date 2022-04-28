#include "relay.h"
#include "card_reader.h"

void setup() {
  Serial.begin(9600);

  // setupRelay();
  setupRfidReceiver();
}

void loop() {
  // loopRelay();
  loopRfidReceiver();
}
