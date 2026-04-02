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

constexpr ScreenConfig screen = { 8, 7, 6, 5, 4, 3, 20, 4 };  // RS, E, D4, D5, D6, D7, COLS, ROWS
constexpr uint8_t windSensorPin = A0;                         // Pin that is used to read the wind direction

constexpr uint8_t rainSensorPin = 2;        // D2
constexpr uint8_t rainIntervalSeconds = 5;  // Max 8.3
constexpr uint8_t rainTimerTickCount = 2; // Number of timer ticks before updating the rain data (must be >= 1)

}