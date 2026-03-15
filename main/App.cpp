#include "Wind.h"
#include "Screen.h"
#include "Config.h"

App::App() : screen{ Config::screen }, wind{ Config::windSensorPin } {}

void App::update() {
	Direction windDirection = wind.getDirection();
	screen.printLine(wind.directionToString(windDirection));
	delay(1000);
}