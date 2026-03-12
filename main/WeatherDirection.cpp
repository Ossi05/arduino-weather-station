#include "WeatherDirection.h"
#include <string.h>

WeatherDirection::WeatherDirection()
  : currentDirection{ Direction::North } {}

String WeatherDirection::directionToString(Direction direction) {
  switch (direction) {
    case Direction::North:
      return "Pohjoinen";
    case Direction::NorthEast:
      return "Koilinen";
    case Direction::East:
      return "Itä";
    case Direction::SouthEast:
      return "Kaakko";
    case Direction::South:
      return "Etelä";
    case Direction::SouthWest:
      return "Lounas";
    case Direction::West:
      return "Länsi";
    case Direction::NorthWest:
      return "Luode";
    case Direction::Unknown:
    default:
      return "Tuntematon ilmansuunta";
  }
}

Direction WeatherDirection::getCurrentDirection() {
  return currentDirection;
}