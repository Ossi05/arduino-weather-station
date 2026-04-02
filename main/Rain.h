#pragma once
#include <Arduino.h>

struct RainData {
	float hourlyRainfallMm;
	float frequency;
	unsigned long pulses;
};

class Rain {
private:
	static Rain* instance;
	static void isrWrapper();
	static void timerIsrWrapper();

	// TimerOne
	volatile unsigned long lastIntervalPulses;
	volatile float currentFrequencyHz;
	volatile float currentRainfallMmPerHour;
	volatile uint8_t currentTimerTickCount;
	uint8_t maxTimerTickCount;

	// Pulses
	volatile unsigned long totalPulseCount;
	volatile unsigned long intervalPulseCount;

	uint8_t dataPin;
	float mmPerPulse;
	uint8_t intervalSeconds;

	unsigned long getAndResetIntervalPulses();
	float calculateFrequencyFromPulses(unsigned long pulses, uint8_t intervalSeconds) const;  // Laskee signaalin taajuuden
	float calculateRainFallMmPerHour(float frequencyHz) const;                                // Muuntaa taajuuden säädataksi
	void resetIntervalPulses();

	// TimerOne
	void updateMetrics();

public:
	Rain(uint8_t dataPin, float mmPerPulse, uint8_t intervalSeconds, uint8_t rainTimerTickCount);
	void registerPulse();
	float getTotalRainfallMm() const;
	void reset();
	void setup() const;
	String toString() const;

	RainData getLatestData() const;
};