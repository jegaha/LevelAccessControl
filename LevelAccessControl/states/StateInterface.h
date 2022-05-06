#pragma once

enum StateIdentifier {
  normalOperation = 0,
  relayActive,
  learnNewCard,

  count
};

class StateInterface
{
  public:
    virtual void onEnter() {};
    virtual StateIdentifier run();
    virtual void onExit() {};
};
