#include "settings.h"

#include "Ota.h"
#include "Relay.h"
#include "CardReader.h"
#include "CardRepository.h"
#include "Application.h"

Ota ota = Ota();
Relay relay = Relay(RELAY_TOGGLE_PIN);
CardReader cardReader = CardReader(SS_PIN, RST_PIN);
CardRepository cardRepository = CardRepository();
Application application = Application(relay, cardReader, cardRepository);

void setup() {
  Serial.begin(9600);

  ota.begin();
  cardReader.begin();
  cardRepository.begin();
}

void loop() {
  ota.loop();
  application.run();
}
