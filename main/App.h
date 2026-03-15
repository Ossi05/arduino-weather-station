#pragma once
#include "Screen.h"
#include "Wind.h"

class App {
private:
	Screen screen;
	Wind wind;
public:
	App();
	void update();
};
