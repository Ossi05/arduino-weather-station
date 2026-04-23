#include "App.h"
#include "Arduino.h"
#include "Config.h"
#include "Rain.h"
#include "Screen.h"
#include "utils.h"
#include "Wind.h"

App::App()
	:
	// Screen
	screen{ Config::screen },

	// Wind
	wind{ Config::windSensorPin },

	// Rain
	rain{ Config::rainSensorPin,
			Config::rainMmPerPulse,
			Config::rainIntervalSeconds,
			Config::rainTimerTickCount },

	// MQTT
	mqtt{
		Config::mqttServerIp,
		Config::mqttServerPort,
		Config::mqttMacAddress,
		Config::mqttClientId,
		Config::mqttOutTopic
			},

	// App
	lastMqttSendTime{ 0 },
	MqttSendInterval{ Config::MqttSendInterval } {
}

void App::setup() {
	mqtt.setup();
	rain.setup();
}

void App::loop() {

	// 1. Keep MQTT connection alive
	mqtt.loop();

	// 2. Update screen
	updateScreen();

	// 3. Handle MQTT publishing
	handleMqttPublishing();

	delay(500); // 500 ms delay 
}

void App::updateScreen() {
	RainData rainData{ rain.getLatestIntervalData() };

	// Row 0: IP-address
	screen.printLine(mqtt.ipToString(mqtt.getIp()), 0);

	// Row 1: MQTT connection status
	String mqttStatus = mqtt.isConnected() ? "MQTT: OK" : "MQTT: NOT OK";
	screen.printLine(mqttStatus, 1);

	// Row 2: Wind direction
	screen.printLine("Wind dir: " + wind.directionToString(wind.getDirection()), 2);

	// Row 3: Hourly rain fall
	screen.printLine("Rain: " + String(rainData.hourlyRainfallMm) + " mm/h", 3);
}

void App::handleMqttPublishing() {
	unsigned long currentMillis = millis();

	// Check if it's time to send the next message
	if (currentMillis - lastMqttSendTime >= MqttSendInterval) {
		lastMqttSendTime = currentMillis;
		buildAndSendMqttPayload();
	}
}

void App::buildAndSendMqttPayload() {
	// 1. Get average wind data
	int numSamples{ 100 };
	Direction currentWindDir = wind.getAveragedDirection(numSamples);
	const WindData& windData = wind.getWindData(currentWindDir);

	// 2. Get rain data
	RainData rainData = rain.getLatestIntervalData();

	// 3. Create payload
	String payload = buildMqttPayload(windData, rainData);

	// 4. Send payload to MQTT server
	Serial.println("Sending MQTT message:");
	Serial.println(payload);
	mqtt.sendMessage(payload.c_str());
}

String App::buildMqttPayload(const WindData& windData, const RainData& rainData) const {
	String payload = "IOTJS={\"S_name1\":\"";
	payload += Config::sNamePrefix;
	payload += "_wind_deg\",\"S_value1\":";
	payload += windData.degree;
	payload += ",\"S_name2\":\"";
	payload += Config::sNamePrefix;
	payload += "_h_rain_mm\",\"S_value2\":";
	payload += String(rainData.hourlyRainfallMm, 2);
	payload += "}";

	return payload;
}
