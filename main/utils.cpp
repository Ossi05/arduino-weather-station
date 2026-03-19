#include "utils.h"
#include <Arduino.h>


float analogToVoltage(int analogValue) {
  float referenceVoltage{ 5.0 };
  float maxAdcResolution{ 1023.0 };

  return analogValue * (referenceVoltage / maxAdcResolution);
}

float getAverageVoltage(int numSamples, int dataPin) {
  if (numSamples <= 0) { return 0.0f; }
  float total{ 0.0f };

  for (int i = 0; i < numSamples; i++) {
    total += analogToVoltage(analogRead(dataPin));
    delay(1);
  }
  return total / numSamples;
}