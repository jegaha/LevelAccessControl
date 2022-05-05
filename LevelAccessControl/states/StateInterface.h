#pragma once

enum StateIdentifier {
  normalOperation = 0,
  relayActive,

  count
};

class StateInterface
{
  public:
    virtual void onEnter() {};
    virtual int run();
    virtual void onExit() {};
};
