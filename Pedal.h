#pragma once
#include <Arduino.h>

class Pedal {
public:
  Pedal();

  const bool GetPedalStatus() const;

private:
  static constexpr int pedal_pin = 25;
};