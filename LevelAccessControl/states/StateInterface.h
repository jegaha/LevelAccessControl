#pragma once

enum StateIdentifier {
  normalOperation = 0,
  relayActive,

  count
};

class StateInterface
{
  public:
    virtual int run();
};
