#ifndef APPLICATION_H
#define APPLICATION_H

#include "Relay.h"
#include "CardReader.h"
#include "CardRepository.h"

#include "states/StateInterface.h"
#include "states/NormalOperation.h"
#include "states/RelayActive.h"

#ifndef APP_RELAY_DURATION_MS
#define APP_RELAY_DURATION_MS 1000
#endif

class Application
{
  private:
    Relay &relay;
    CardReader &cardReader;
    CardRepository &cardRepository;
    Ota &ota;
    StaServer &staServer;
    bool serversShutDown = false;

    StateInterface* currentState;
    StateInterface* states[StateIdentifier::count];


  public:
    Application(Relay &relay, CardReader &cardReader, CardRepository &cardRepository, Ota &ota, StaServer &staServer)
    : relay(relay)
    , cardReader(cardReader)
    , cardRepository(cardRepository)
    , ota(ota)
    , staServer(staServer)
    {
      states[StateIdentifier::normalOperation] = new NormalOperation(relay, cardReader, cardRepository);
      states[StateIdentifier::relayActive] = new RelayActive(relay, cardReader, cardRepository);
      currentState = states[StateIdentifier::normalOperation];
    }

    void run() {
      int nextStateIdentifier = currentState->run();
      currentState = states[nextStateIdentifier];
      handleShutdownOtaAndStaServer();
    }

  private:
    void handleShutdownOtaAndStaServer() {
      if (
        !serversShutDown
         && (millis() > 5 * 60 * 1000)
      ) {
        ota.disable();
        staServer.disable();
        serversShutDown = true;
      }
    }
};

#endif // APPLICATION_H
