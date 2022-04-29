#ifndef RELAY_H
#define RELAY_H

class Relay
{
  private:
    int pin;

  public:
    Relay(int pin) {
      this->pin = pin;
      pinMode(this->pin, OUTPUT);
    }

    void on() {
      digitalWrite(this->pin, HIGH);
    }

    void off() {
      digitalWrite(this->pin, LOW);
    }
};

#endif // RELAY_H
