#include "Timer.h"

Timer *timer;

void setup() {
  timer = new Timer;
}

void loop() {
  timer->Loop();
}
