#include "Rain.h"
#include <Arduino.h>
#include <TimerOne.h>

Rain* Rain::instance{ nullptr };

Rain::Rain(uint8_t pin, float mmPerPulse, uint8_t intervalSeconds, uint8_t timerTickCount)
	: dataPin{ pin }, mmPerPulse{ mmPerPulse }, intervalSeconds{ intervalSeconds }, totalPulseCount{ 0 }, intervalPulseCount{ 0 }, lastIntervalPulses{ 0 }, currentFrequencyHz{ 0.0 }, currentRainfallMmPerHour{ 0.0 }, maxTimerTickCount{ timerTickCount }, currentTimerTickCount{ 0 } {

	if (instance != nullptr) {
		Serial.println("FATAL ERROR: Multiple Rain instances created!");
		return;
	}

	instance = this;
}


void Rain::setup() const {
	pinMode(dataPin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(dataPin), Rain::isrWrapper, FALLING);

	Timer1.initialize((unsigned long)intervalSeconds * 1000000UL);
	Timer1.attachInterrupt(Rain::timerIsrWrapper);
}


float Rain::getTotalRainfallMm() const {
	noInterrupts();
	unsigned long currentPulses{ totalPulseCount };
	interrupts();

	return currentPulses * mmPerPulse;
}

void Rain::isrWrapper() {
	if (instance != nullptr) {
		instance->registerPulse();
	}
}

void Rain::timerIsrWrapper() {
	if (instance != nullptr) {
		instance->updateMetrics();
	}
}

void Rain::updateMetrics() {

	if (++currentTimerTickCount >= maxTimerTickCount) {
		lastIntervalPulses = intervalPulseCount;
		intervalPulseCount = 0;
		currentTimerTickCount = 0;

		currentFrequencyHz = calculateFrequencyFromPulses(lastIntervalPulses, intervalSeconds * 2);
		currentRainfallMmPerHour = calculateRainFallMmPerHour(currentFrequencyHz);
	}

}

void Rain::registerPulse() {
	++totalPulseCount;
	++intervalPulseCount;
}

void Rain::reset() {
	noInterrupts();
	totalPulseCount = 0;
	resetIntervalPulses();
	interrupts();
}

String Rain::toString() const {
	return "Rain: " + String(getTotalRainfallMm(), 2) + " mm";
}


unsigned long Rain::getAndResetIntervalPulses() {
	noInterrupts();
	unsigned long currentPulses{ intervalPulseCount };
	intervalPulseCount = 0;
	interrupts();

	return currentPulses;
}

float Rain::calculateFrequencyFromPulses(unsigned long pulses, uint8_t intervalSeconds) const {
	if (intervalSeconds <= 0.0) return 0.0;
	return (float)pulses / intervalSeconds;
}

float Rain::calculateRainFallMmPerHour(float frequencyHz) const {
	return frequencyHz * mmPerPulse * 3600.0;
}

void Rain::resetIntervalPulses() {
	noInterrupts();
	intervalPulseCount = 0;
	interrupts();
}

RainData Rain::getLatestIntervalData() const {

	noInterrupts();
	RainData data{
		currentRainfallMmPerHour,  // Hourly Rainfall
		currentFrequencyHz,        // Frequency
		lastIntervalPulses         // Pulses in the last interval
	};
	interrupts();

	return data;
}