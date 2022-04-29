#ifndef APPLICATION_H
#define APPLICATION_H

#include "Relay.h"
#include "CardReader.h"

class Application
{
  private:
    Relay relay;
    CardReader cardReader;

  public:
    Application(Relay relay, CardReader cardReader)
    : relay(relay)
    , cardReader(cardReader)
    {
    }

    void run() {
      relay.on();
      delay(500);
      relay.off();
      delay(500);
    }
};

#endif // APPLICATION_H
