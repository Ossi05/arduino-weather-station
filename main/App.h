#pragma once
#include "Rain.h"
#include "Screen.h"
#include "Wind.h"

class App {
private:
	Screen screen;
	Wind wind;
	Rain rain;
public:
	App();
	void setup();
	void update();
};
