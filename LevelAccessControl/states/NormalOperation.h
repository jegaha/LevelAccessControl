#pragma once

#include "StateInterface.h"

class NormalOperation : public StateInterface
{
  private:
    Relay &relay;
    CardReader &cardReader;
    CardRepository &cardRepository;

    unsigned long relayOnUntil = 0;
    bool relayTriggered = false;

  public:
    NormalOperation(Relay &relay, CardReader &cardReader, CardRepository &cardRepository)
    : relay(relay)
    , cardReader(cardReader)
    , cardRepository(cardRepository)
    {
    }

    virtual int run()
    {
      long cardId = cardReader.getCardId();
      handleCardId(cardId);
      handleRelais();
    }

  private:
    void handleCardId(long cardId) {
      if (!relayTriggered && cardId) {
        Serial.print("card ID: ");
        Serial.print(cardId);
        Serial.print(" ");

        if(cardRepository.hasCard(cardId)) {
          Serial.println("access granted.");
          triggerRelay();
        } else {
          Serial.println("access denied.");
          delay(10);
        }
      }
    }

    void handleRelais() {
      if (relayTriggered) {
        if (relayOnUntil && (millis() > relayOnUntil)) {
          relay.off();
          relayTriggered = false;
        }
      }
    }

    void triggerRelay() {
      relayOnUntil = millis() + APP_RELAY_DURATION_MS;
      if (relayOnUntil == 0) {
        relayOnUntil = 1;
      }
      relayTriggered = true;
      relay.on();
    }
};