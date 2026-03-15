#pragma once
#include <Arduino.h>

namespace Config {
	struct ScreenConfig {
		uint8_t rs;
		uint8_t e;
		uint8_t d4;
		uint8_t d5;
		uint8_t d6;
		uint8_t d7;
		uint8_t cols;
		uint8_t rows;
	};

	constexpr ScreenConfig screen = { 8, 7, 6, 5, 4, 3, 16, 2 }; // RS, E, D4, D5, D6, D7, COLS, ROWS
	constexpr uint8_t windSensorPin = A0; // Pin that is used to read the wind direction
}