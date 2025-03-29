#include "SerialPrinter.h"

SerialPrinter::SerialPrinter() {
  Serial.begin(115200);
}

void SerialPrinter::PrintMessage(String message) {
  Serial.println(message);
}
