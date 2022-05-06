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
      long cardUid = cardReader.getCardUid();
      StateIdentifier nextState = nextStateByCardUid(cardUid);

      return nextState;
    }

  private:
    StateIdentifier nextStateByCardUid(long cardUid) {
      if (!cardUid) {
        return StateIdentifier::normalOperation;
      }

      Serial.print("card ID: ");
      Serial.print(cardUid);
      Serial.print(" ");

      if (cardRepository.isLearnNewCardTrigger(cardUid)) {
        return StateIdentifier::learnNewCard;
      }

      if(cardRepository.hasCard(cardUid)) {
        Serial.println("access granted.");
        return StateIdentifier::relayActive;

      }

      Serial.println("access denied.");
      delay(10);
      return StateIdentifier::normalOperation;
    }
};
