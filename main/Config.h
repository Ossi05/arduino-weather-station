#pragma once
#include <Arduino.h>

namespace Config {
	// APP
	constexpr unsigned long MqttSendInterval{ 10000 };  // How often to send data to the MQTT server in milliseconds

	// SCREEN
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

	constexpr ScreenConfig screen{ 8, 7, 6, 5, 4, 3, 20, 4 };  // RS, E, D4, D5, D6, D7, COLS, ROWS
	constexpr uint8_t windSensorPin{ A0 };                     // Pin that is used to read the wind direction

	// RAIN
	constexpr float rainMmPerPulse{ 0.54545f };   // 3ml / 55cm^2 
	constexpr uint8_t rainSensorPin{ 2 };         // D2
	constexpr uint8_t rainIntervalSeconds{ 5 };   // Max 8.3
	constexpr uint8_t rainTimerTickCount{ 2 };    // Number of timer ticks before updating the rain data (must be >= 1)

	// MQTT Server
	constexpr byte mqttServerIp[4]{ 10, 6, 0, 23 };
	constexpr unsigned int mqttServerPort{ 1883 };
	constexpr uint8_t mqttMacAddress[6]{ 0x44, 0x76, 0x58, 0x10, 0x00, 0x62 };
	constexpr const char* mqttClientId{ "tl" };
	constexpr const char* mqttOutTopic{ "ICT4_out_2020" };
	constexpr const char* sNamePrefix{ "tl" };
}