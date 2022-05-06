#ifndef APPLICATION_H
#define APPLICATION_H

#include "Relay.h"
#include "CardReader.h"
#include "CardRepository.h"

#include "states/StateInterface.h"
#include "states/NormalOperation.h"
#include "states/RelayActive.h"
#include "states/LearnNewCard.h"

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
      states[StateIdentifier::normalOperation] = new NormalOperation(cardReader, cardRepository);
      states[StateIdentifier::relayActive] = new RelayActive(relay);
      states[StateIdentifier::learnNewCard] = new LearnNewCard(cardReader, cardRepository);
      currentState = states[StateIdentifier::normalOperation];
    }

    void run() {
      int nextStateIdentifier = currentState->run();
      StateInterface* nextState = states[nextStateIdentifier];

      if (currentState != nextState) {
        currentState->onExit();
        nextState->onEnter();
        currentState = nextState;
      }

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
