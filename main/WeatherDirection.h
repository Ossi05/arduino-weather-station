#pragma once
#include <Arduino.h>

enum class Direction {
  Unknown,
  North,
  NorthEast,
  East,
  SouthEast,
  South,
  SouthWest,
  West,
  NorthWest
};

class WeatherDirection {
private:
  Direction currentDirection;
public:
  WeatherDirection();
  String directionToString(Direction direction);
  Direction getCurrentDirection();
};