#pragma once

#include "StateInterface.h"

class RelayActive : public StateInterface
{
  private:
    Relay &relay;
    CardReader &cardReader;
    CardRepository &cardRepository;

    unsigned long relayOnUntil = 0;
    bool relayTriggered = false;

  public:
    RelayActive(Relay &relay, CardReader &cardReader, CardRepository &cardRepository)
    : relay(relay)
    , cardReader(cardReader)
    , cardRepository(cardRepository)
    {
    }

    virtual int run()
    {
      return StateIdentifier::relayActive;
    }

};
