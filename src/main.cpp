#include <Arduino.h>
#include <LedMatrix.h>
#include "matrices.h"


LedMatrix ledMatrix(D1, D2, D3);


void setup() {
  ledMatrix.setup();
}


void loop() {
  ledMatrix.drawMatrix(happyFace);
}