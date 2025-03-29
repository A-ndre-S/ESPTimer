#include "Keyboard4x4.h"

Keyboard4x4::Keyboard4x4() {
  keypad = new Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
  keypad->setDebounceTime(50);  //Imposto debounce a 50ms
}

char Keyboard4x4::GetPressedKey() {
  char key = keypad->getKey();
  return key;
}
