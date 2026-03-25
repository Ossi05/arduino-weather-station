#pragma once
#include <Arduino.h>

class Rain {
private:
	int dataPin;
	float mmPerPulse;
	volatile unsigned long pulseCount;
	static Rain* instance;
	static void isrWrapper();
public:
	Rain(int dataPin, float mmPerPulse);
	void registerPulse();
	float getTotalRainfallMm() const;
	void reset();
	void setup() const;
	String toString() const;
};