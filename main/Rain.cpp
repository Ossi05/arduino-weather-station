#include "Rain.h"
#include <Arduino.h>

Rain* Rain::instance{ nullptr };

Rain::Rain(int pin, float mmPerPulse)
  : dataPin{ pin }, mmPerPulse{ mmPerPulse }, pulseCount{ 0 } {

	if (instance != nullptr) {
		Serial.println("FATAL ERROR: Multiple Rain instances created!");
		return;
	}

	instance = this;
}


void Rain::setup() const {
	pinMode(dataPin, INPUT);
	attachInterrupt(digitalPinToInterrupt(dataPin), Rain::isrWrapper, FALLING);
}


float Rain::getTotalRainfallMm() const {
	noInterrupts();
	unsigned long currentPulses = pulseCount;
	interrupts();

	return currentPulses * mmPerPulse;
}

void Rain::isrWrapper() {
	if (instance != nullptr) {
		instance->registerPulse();
	}
}

void Rain::registerPulse() {
	++pulseCount;
}

void Rain::reset() {
	noInterrupts();
	pulseCount = 0;
	interrupts();
}

String Rain::toString() const {
	return "Rainfall " + String(getTotalRainfallMm()) + " mm";
}
