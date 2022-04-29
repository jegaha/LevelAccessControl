#include "settings.h"

#include "ota.h"
#include "Relay.h"
#include "CardReader.h"
#include "CardRepository.h"
#include "Application.h"

Relay relay = Relay(RELAY_TOGGLE_PIN);
CardReader cardReader = CardReader(SS_PIN, RST_PIN);
CardRepository cardRepository = CardRepository();
Application application = Application(relay, cardReader, cardRepository);

void setup() {
  Serial.begin(9600);

  setupOta();
  cardReader.begin();
}

void loop() {
  loopOta();
  application.run();
}
