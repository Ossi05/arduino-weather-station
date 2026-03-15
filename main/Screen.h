#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Config.h"

class Screen {
private:
	LiquidCrystal lcd;
	int cols;
	int rows;

public:
	Screen(Config::ScreenConfig config);

	void printWrapped(const String& message, int startRow = 0);
	void printLine(const String& msg, int startRow = 0);

	void clear();
};