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
	Direction voltageToDirection(float voltage) const;

public:
	Wind(int dataPin);

	const String& directionToString(Direction direction) const;
	Direction getDirection() const;
	Direction getAveragedDirection(int samples) const;
	const WindData& getWindData(Direction direction) const;
	int getDataPin() const;
	String toString() const;
};