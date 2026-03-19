#include "Wind.h"
#include <string.h>
#include "utils.h"
#include <Arduino.h>
#include <math.h>

const WindData Wind::windData[9] = {
	{ Direction::None, "Tuntematon ilmansuunta", -1.0f, -1 },
	{ Direction::North, "Pohjoinen", 0.0f, 0 },
	{ Direction::NorthEast, "Koillinen", 0.48f, 45 },
	{ Direction::East, "Itä", 0.96f, 90 },
	{ Direction::SouthEast, "Kaakko", 1.43f, 135 },
	{ Direction::South, "Etelä", 1.91f, 180 },
	{ Direction::SouthWest, "Lounas", 2.37f, 225 },
	{ Direction::West, "Länsi", 2.87f, 270 },
	{ Direction::NorthWest, "Luode", 3.32f, 315 }
};

Wind::Wind(int dataPin)
  : dataPin{ dataPin } {
}

String Wind::directionToString(Direction direction) {
	return getWindData(direction).name;
}

Direction Wind::voltageToDirection(float voltage) {
	Direction direction{ Direction::None };
	float minDifference{ 100.0f };
	float offset{ 0.15f };

	for (int i = 1; i < 9; i++) {
		if (windData[i].voltage <= voltage + offset) {
			direction = windData[i].dir;
		}
	}

	return direction;
}

Direction Wind::getDirection() {
	int windAnalogValue{ analogRead(dataPin) };
	float voltage{ analogToVoltage(windAnalogValue) };

	return voltageToDirection(voltage);
}

const WindData& Wind::getWindData(Direction direction) {
	for (int i = 1; i < 9; i++) {
		if (windData[i].dir == direction) {
			return windData[i];
		}
	}
	return windData[0];
}

int Wind::getDataPin() {
	return dataPin;
}

String Wind::toString() {
	Direction dir{ getDirection() };
	String dirStr{ directionToString(dir) };
	int numSamples{ 100 };
	return dirStr + ": " + "Avg: " + String(getAverageVoltage(dataPin, numSamples)) + "V";
}
