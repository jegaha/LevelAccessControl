#pragma once

#include "StateInterface.h"

class NormalOperation : public StateInterface
{
  private:
    CardReader &cardReader;
    CardRepository &cardRepository;

  public:
    NormalOperation(CardReader &cardReader, CardRepository &cardRepository)
    : cardReader(cardReader)
    , cardRepository(cardRepository)
    {
    }

    virtual StateIdentifier run()
    {
      long cardId = cardReader.getCardId();
      StateIdentifier nextState = nextStateByCardId(cardId);

      return nextState;
    }

  private:
    StateIdentifier nextStateByCardId(long cardId) {
      if (!cardId) {
        return StateIdentifier::normalOperation;
      }

      Serial.print("card ID: ");
      Serial.print(cardId);
      Serial.print(" ");

      if(cardRepository.hasCard(cardId)) {
        Serial.println("access granted.");
        return StateIdentifier::relayActive;

      }

      Serial.println("access denied.");
      delay(10);
      return StateIdentifier::normalOperation;
    }
};
