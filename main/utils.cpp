#include "utils.h"

float analogToVoltage(int analogValue) {
  float referenceVoltage{ 5.0 };
  float maxAdcResolution{ 1023.0 };

  return analogValue * (referenceVoltage / maxAdcResolution);
}