#include "App.h"
#include "Config.h"
#include "Rain.h"
#include "Screen.h"
#include "utils.h"
#include "Wind.h"
#include "Arduino.h"

// Rain sensors mmPerPulse is 3ml / 55cm^2
App::App()
  : screen{ Config::screen },
    wind{ Config::windSensorPin },
    rain{ Config::rainSensorPin,
	        0.54545,  // Rain sensors mmPerPulse is 3ml / 55cm^2
			Config::rainIntervalSeconds,
	Config::rainTimerTickCount }
{
}

void App::setup() {
	rain.setup();
}

void App::update() {
	//screen.printLine(wind.toString());
	//screen.printLine(rain.toString(), 0);

	RainData data {rain.getLatestData()};
	screen.printLine(rain.toString(), 0);
	screen.printLine(String(data.hourlyRainfallMm) + " mm/h", 1);
	screen.printLine(String(data.frequency) + " Hz", 2);
	screen.printLine(String(data.pulses) + " pulses", 3);
}