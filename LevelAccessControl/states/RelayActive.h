#pragma once

#include "StateInterface.h"

#ifndef APP_RELAY_DURATION_MS
#define APP_RELAY_DURATION_MS 3000
#endif

class RelayActive : public StateInterface
{
  private:
    Relay &relay;

    unsigned long relayOnUntil = 0;

  public:
    RelayActive(Relay &relay)
    : relay(relay)
    {
    }

    virtual void onEnter()
    {
      unsigned long now = millis();
      relayOnUntil = now + APP_RELAY_DURATION_MS;
      if (relayOnUntil < now) {
        relayOnUntil = 0;
        relayOnUntil--;
      }

      relay.on();
    }

    virtual StateIdentifier run()
    {
      if (millis() > relayOnUntil) {
        return StateIdentifier::normalOperation;
      }
      return StateIdentifier::relayActive;
    }

    virtual void onExit()
    {
      relay.off();
    }

};
