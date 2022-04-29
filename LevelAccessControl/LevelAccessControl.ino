#include "settings.h"

#include "Relay.h"
#include "CardReader.h"
#include "ota.h"
#include "Application.h"

Relay relay = Relay(RELAY_TOGGLE_PIN);
CardReader cardReader = CardReader(SS_PIN, RST_PIN);
Application application = Application(relay, cardReader);

void setup() {
  Serial.begin(9600);

  setupOta();
  cardReader.begin();
}

void loop() {
  loopOta();
  application.run();
}
