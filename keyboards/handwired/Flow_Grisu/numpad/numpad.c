#include "numpad.h"

void matrix_init_kb(void) {
  setPinOutput(D4);
  setPinOutput(B6);
  //writePinHigh(B4);
  //writePinLow(B5);
  matrix_init_user();
}
