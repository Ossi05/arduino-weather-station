#pragma once
#include <Arduino.h>

enum class Direction {
	None,
	North,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest
};

struct WindData {
	Direction dir;
	String name;
	float voltage;
	int degree;
};

class Wind {
private:
	static const WindData windData[9];
	const int dataPin;
	Direction voltageToDirection(float voltage);

public:
	Wind(int dataPin);

	String directionToString(Direction direction);
	Direction getDirection();
	const WindData& getWindData(Direction direction);
	int getDataPin();
	String toString();
};