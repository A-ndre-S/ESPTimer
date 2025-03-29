#pragma once
#include <Arduino.h>

class Relay {
public:
  Relay();

  void SetRelayStatus(const bool status);
  const bool GetRelayStatus() const;
private:
  bool relay_status{ false };
  static constexpr int relay_pin = 27;
};