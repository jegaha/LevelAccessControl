#include "settings.h"

#include "StaServer.h"
#include "Ota.h"
#include "Relay.h"
#include "CardReader.h"
#include "CardRepository.h"
#include "Application.h"

StaServer staServer = StaServer();
Ota ota = Ota();
Relay relay = Relay(RELAY_TOGGLE_PIN);
CardReader cardReader = CardReader(SS_PIN, RST_PIN);
CardRepository cardRepository = CardRepository();

Application application = Application(relay, cardReader, cardRepository, ota, staServer);

void setup() {
  Serial.begin(9600);

  staServer.enable();

  ota.begin();
  ota.enable();

  cardReader.begin();
  cardRepository.begin();
}

void loop() {
  staServer.loop();
  ota.loop();

  application.run();
}
