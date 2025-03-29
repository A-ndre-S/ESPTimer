#pragma once
#include <Arduino.h>
#include "SerialPrinter.h"
#include "OTA.h"
#include "Keyboard4x4.h"
#include "SevenSegmentDisplay.h"
#include "Relay.h"
#include "Pedal.h"

class Timer {
public:
  enum class Status {
    setup,
    light,
    focusing,
  };

  Timer();
  ~Timer();

  void Loop();
protected:
  void ParseInput();
  void SetupStatus();
  void LightStatus();
  void FocusingStatus();

  void UpdateTime();

  void SetLight(bool status);

  Printer* printer;
  OTA* ota;
  Keyboard4x4 keyboard;
  SevenSegmentDisplay display;
  Relay relay;
  Status status;
  Pedal pedal;
  
  int64_t time_us;
  int64_t target_time_us;

  double current_value;

  static const long int sec_to_usec = 1000000L;
};