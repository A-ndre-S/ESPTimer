#include "Pedal.h"

Pedal::Pedal() {
  // Initialize as an input pin with pull down
  pinMode(pedal_pin, INPUT_PULLDOWN);
}

const bool Pedal::GetPedalStatus() const {
  return (digitalRead(pedal_pin) == HIGH);
}