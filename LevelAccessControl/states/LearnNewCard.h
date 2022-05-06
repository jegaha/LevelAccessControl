#pragma once

#include "StateInterface.h"

#ifndef APP_LEARN_CARD_DURATION_MS
#define APP_LEARN_CARD_DURATION_MS 10000
#endif

class LearnNewCard : public StateInterface
{
  private:
    CardReader &cardReader;
    CardRepository &cardRepository;

    unsigned long LearnNewCardUntil = 0;

  public:
    LearnNewCard(CardReader &cardReader, CardRepository &cardRepository)
    : cardReader(cardReader)
    , cardRepository(cardRepository)
    {
    }

    virtual void onEnter()
    {
      unsigned long now = millis();
      LearnNewCardUntil = now + APP_LEARN_CARD_DURATION_MS;
      if (LearnNewCardUntil < now) {
        LearnNewCardUntil = 0;
        LearnNewCardUntil--;
      }
    }

    virtual StateIdentifier run()
    {
      if (millis() > LearnNewCardUntil) {
        return StateIdentifier::normalOperation;
      }

      long cardUid = cardReader.getCardUid();
      if (learnNewCardUid(cardUid)) {
        return StateIdentifier::normalOperation;
      }

      return StateIdentifier::learnNewCard;
    }

  private:
    bool learnNewCardUid(long cardUid)
    {
      if (!cardUid
        || cardRepository.isLearnNewCardTrigger(cardUid)
        || cardRepository.hasCard(cardUid)
      ) {
        return false;
      }

      cardRepository.addCard(cardUid);
      return true;
    }
};
