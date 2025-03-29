#include <Arduino.h>
#include <TM1637Display.h>


class SevenSegmentDisplay {
public:
  SevenSegmentDisplay();

  void DisplayNumber(double number);
  void DisplayFocusing();
  
private:
  TM1637Display* display;
};
