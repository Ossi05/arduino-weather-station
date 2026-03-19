#include "App.h"
#include "Wind.h"
#include "Screen.h"
#include "Config.h"
#include "utils.h"

App::App()
  : screen{ Config::screen }, wind{ Config::windSensorPin } {}

void App::update() {
	screen.printLine(wind.toString());
}