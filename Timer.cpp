#include "Timer.h"
#include <ctype.h>

Timer::Timer() {
  status = Status::setup;
  printer = new SerialPrinter();
  ota = new OTA(printer);

  current_value = 0.0;
  target_time_us = 0;
  time_us = 0;
}

Timer::~Timer() {
  delete printer;
  delete ota;
}

void Timer::Loop() {
  ota->Handle();

  ParseInput();

  switch (status) {
    case Status::setup:
      SetupStatus();
      break;
    case Status::light:
      LightStatus();
      break;

    case Status::focusing:
      FocusingStatus();
      break;
  }
}

void Timer::ParseInput() {
  char ch = keyboard.GetPressedKey();
  if (ch == 'C') {
    // Rage quit / reset
    current_value = 0.0;
    relay.SetRelayStatus(false);
    status = Status::setup;
    current_value = 0;
  }

  if (status == Status::light)
    return;

  if (ch >= '0' && ch <= '9' && current_value < 100.0)
    // Update current value
    current_value = current_value * 10 + (ch - '0');
  else if (ch == 'A') {
    // Duplicate current value
    current_value = current_value * 2.0;
  } else if (ch == 'B') {
    // Halve current value
    current_value = current_value / 2.0;
  } else if (ch == 'D') {
    // Implement functions for D
  } else if (ch == '#' || pedal.GetPedalStatus()) {
    // Start light status
    UpdateTime();
    target_time_us = time_us + (current_value * sec_to_usec);
    status = Status::light;
    relay.SetRelayStatus(true);
  } else if (ch == '*') {
    // Toggle focusing status. Return to setup status after focusing
    status == Status::focusing
      ? (status = Status::setup, relay.SetRelayStatus(false))
      : (status = Status::focusing, relay.SetRelayStatus(true));
  };
}

void Timer::SetupStatus() {
  display.DisplayNumber(current_value);
}

void Timer::LightStatus() {
  UpdateTime();
  double time_sec = round(((target_time_us - time_us) * 100.0) / sec_to_usec) / 100.0;  // Round to 2 decimal places
  display.DisplayNumber(time_sec);
  if (time_us > target_time_us) {
    relay.SetRelayStatus(false);
    status = Status::setup;
  }
}

void Timer::FocusingStatus() {
  display.DisplayFocusing();
}

void Timer::UpdateTime() {
  struct timeval tv_now;

  if (gettimeofday(&tv_now, NULL) == 0) {
    time_us = (int64_t)tv_now.tv_sec * sec_to_usec + (int64_t)tv_now.tv_usec;
  }
}
