#include "App.h"
#include "Config.h"
#include "Screen.h"
#include "utils.h"
#include "Wind.h"
#include "Rain.h"

// Rain sensors mmPerPulse is 3ml / 55cm^2
App::App()
  : screen{ Config::screen },
    wind{ Config::windSensorPin },
    rain{ Config::RainSensorPin, 0.54545 }  // Rain sensors mmPerPulse is 3ml / 55cm^2
{
}

void App::setup() {
	rain.setup();
}

void App::update() {
	screen.printLine(wind.toString());
	screen.printLine(rain.toString(), 1);
}