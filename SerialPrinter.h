#pragma once
#include "Printer.h"

class SerialPrinter : public Printer
{
public:
  SerialPrinter();

  void PrintMessage(String message) override;
};