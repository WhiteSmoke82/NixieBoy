#include "Arduino.h"
#include "ShiftLib.h"

int regValues[100];

ShiftLib::ShiftLib(int registerAmount, int latchPin, int clockPin, int dataPin)
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  _latchPin = latchPin;
  _clockPin = clockPin;
  _dataPin = dataPin;
  _registerAmount = registerAmount;
  regValues[_registerAmount];
}

void ShiftLib::set(int pin, boolean state)
{
  int arrayLength = int(ceil(float(pin + 1)/8));

  int array[arrayLength];

  int i = 0;
  while(pin > 7){
    array[i] = 0;
    pin = pin - 8;
    i++;
  }
  array[i] = pin;

  if(bitRead(regValues[arrayLength - 1], pin) == 0 && state == HIGH){
    regValues[arrayLength - 1] = regValues[arrayLength - 1] + ShiftLib::intToLed(pin);
  }

  if(bitRead(regValues[arrayLength - 1], pin) == 1 && state == LOW){
    regValues[arrayLength - 1] = regValues[arrayLength - 1] - ShiftLib::intToLed(pin);
  }

  digitalWrite(_latchPin, LOW);

  for(int i = 0; i < _registerAmount; i++){
    shiftOut(_dataPin, _clockPin, MSBFIRST, byte(regValues[i]));
  }

  digitalWrite(_latchPin, HIGH);
}

int ShiftLib::intToLed(int toChange)
{
  return ceil(pow(2,toChange));
}
