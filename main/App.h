#pragma once
#include "Mqtt.h"
#include "Rain.h"
#include "Screen.h"
#include "Wind.h"

class App {
private:
	Screen screen;
	Wind wind;
	Rain rain;
	Mqtt mqtt;

	unsigned long lastMqttSendTime;
	const unsigned long MqttSendInterval;

	void updateScreen();
	void handleMqttPublishing();
	void buildAndSendMqttPayload();
	String buildMqttPayload(const WindData& windData, const RainData& rainData) const;
public:
	App();
	void setup();
	void loop();
};
