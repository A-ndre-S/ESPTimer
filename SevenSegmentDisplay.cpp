#include "SevenSegmentDisplay.h"

SevenSegmentDisplay::SevenSegmentDisplay() {
  // Module connection pins (Digital Pins)
  const int CLK = 13;
  const int DIO = 14;

  display = new TM1637Display(CLK, DIO);
  display->setBrightness(0x0f);
}

void SevenSegmentDisplay::DisplayNumber(double number) {
  uint8_t digits[4] = { 0x00, 0x00, 0x00, 0x00 };

  int intPart = (int)number;
  int decPart = (int)((number - intPart) * 100);

  // Integer part
  if (intPart >= 10) {
    digits[0] = display->encodeDigit(intPart / 10);
  } else {
    digits[0] = 0x00;  // Skip leading zero
  }

  digits[1] = display->encodeDigit(intPart % 10) | 0x80;  // Set colon

  // Decimal part
  digits[2] = display->encodeDigit(decPart / 10);
  digits[3] = display->encodeDigit(decPart % 10);

  display->setSegments(digits);
}

void SevenSegmentDisplay::DisplayFocusing() {
  uint8_t data[] = { display->encodeDigit(0xf),  display->encodeDigit(0xc), display->encodeDigit(0x5), 0x00 };  // Last digit left blank

  display->setSegments(data);
}

