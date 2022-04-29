#include "relay.h"
#include "card_reader.h"
#include "ota.h"

void setup() {
  Serial.begin(9600);

  setupOta();
  // setupRelay();
  setupRfidReceiver();
}

void loop() {
  loopOta();
  // loopRelay();
  loopRfidReceiver();
}
