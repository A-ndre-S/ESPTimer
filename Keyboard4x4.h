#pragma once
#include <Keypad.h>
#include <Arduino.h>

class Keyboard4x4 {
public:
  Keyboard4x4();

  char GetPressedKey();
private:
  Keypad *keypad;

  static const byte ROW_NUM = 4;
  static const byte COLUMN_NUM = 4;
  
  char keys[ROW_NUM][COLUMN_NUM] = {
    { '1', '2', '3', 'A' },
    { '4', '5', '6', 'B' },
    { '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' }
  };

  byte pin_rows[ROW_NUM] = { 17, 5, 18, 19 };
  byte pin_column[COLUMN_NUM] = { 2, 0, 4, 16 };
};
