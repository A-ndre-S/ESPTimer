#include "Relay.h"

Relay::Relay() {
  // Initialize GPIO 27 as an output pin
  pinMode(relay_pin, OUTPUT);

  SetRelayStatus(false);
}

void Relay::SetRelayStatus(const bool status) {
  if (status)
    digitalWrite(relay_pin, HIGH);
  else
    digitalWrite(relay_pin, LOW);

  relay_status = status;
}

const bool Relay::GetRelayStatus() const {
  return relay_status;
}