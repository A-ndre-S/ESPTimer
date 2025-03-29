#pragma once
#include <Arduino.h>

class Printer
{
public:
  virtual void PrintMessage(String message) = 0;
};
