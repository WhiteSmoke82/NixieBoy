#include <Arduino.h>
#include <ShiftLib.h>

#define CLOCK 25
#define LATCH 32
#define DATA 33

#define REGAMOUNT 1

#define TUBEAMOUNT 6

ShiftLib shifters(REGAMOUNT, LATCH, CLOCK, DATA);

class NixieTube{

  public:
    int indexArray[4];
    bool valueArray[4];

    NixieTube(int a, int b, int c, int d){  
      indexArray[0] = a; 
      indexArray[1] = b;
      indexArray[2] = c;
      indexArray[3] = d;
    }

    void set(int n){
      for(int i = 0; i < 4; i++){
        valueArray[i] = bitRead(n, i);
      }
      apply();
    }

    void turnOff(){
      for(int i = 0; i < 4; i++){
        valueArray[i] = true;
      }
      apply();
    }

    void apply(){
      for(int i = 0; i < 4; i++){
        shifters.set(indexArray[i], !valueArray[i]);
      }
    }
};

NixieTube *tubes[TUBEAMOUNT];

void setup(){
  for(int i = 0; i < TUBEAMOUNT; i++){
    tubes[i] = new NixieTube(4*i, 4*i + 1, 4*i + 2, 4*i + 3);
  }
}

void loop(){
  tubes[0]->set(random(0, 10));
  delay(420);
}