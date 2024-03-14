#ifndef Shiftlib_h
#define ShiftLib_h

#include "Arduino.h"

class ShiftLib
{
  public:
    ShiftLib(int registerAmount, int latchPin, int clockPin, int dataPin);
    void set(int pin, boolean state);
  private:
    int _latchPin;
    int _clockPin;
    int _dataPin;
    int _registerAmount;
    int intToLed(int toChange);
};

#endif
