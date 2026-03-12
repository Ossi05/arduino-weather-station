#include "WeatherDirection.h"

void setup() {
  Serial.begin(9600);
  WeatherDirection weatherDirection{};
  Serial.println(weatherDirection.directionToString(weatherDirection.getCurrentDirection()));
}

void loop() {
}
