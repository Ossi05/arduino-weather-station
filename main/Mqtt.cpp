#include "Mqtt.h"
#include <Ethernet.h>
#include <PubSubClient.h>

Mqtt::Mqtt(const byte ip[4], unsigned int port, const byte mac[6], const char* clientId, const char* outTopic)
	: client(ethClient),
	outTopic(outTopic),
	clientId(clientId),
	port{ port } {
	memcpy(macAddress, mac, 6);
	memcpy(this->ip, ip, 4);
}

void Mqtt::setup() {

	client.setServer(ip, port);
	connectToEthernet();
}

void Mqtt::loop() {
	if (isConnected()) {
		client.loop();
	}
}

bool Mqtt::isConnected() const {
	return client.connected();
}

const byte* Mqtt::getIp() const {
	return ip;
}

String Mqtt::ipToString(const byte[4]) const
{
	return String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
}

void Mqtt::connectToEthernet() {
	bool connectionSuccess = Ethernet.begin(macAddress);

	if (!connectionSuccess) {
		Serial.println(F("Failed to access Ethernet controller"));
		return;
	}

	Serial.print(F("Connected with IP: "));
	Serial.println(Ethernet.localIP());
}
void Mqtt::connectToServer() {
	Serial.println(F("Connecting to MQTT..."));

	if (!client.connect(clientId)) {
		Serial.print(F("Connection failed. Error state: "));
		Serial.println(client.state());
		return;
	}
	Serial.println(F("Connected OK"));
}

bool Mqtt::sendMessage(const char* message) {
	if (!client.connected()) {
		connectToServer();
	}

	if (!client.connected()) {
		Serial.println(F("Failed to send message: not connected to MQTT server."));
		return false;
	}

	client.publish(outTopic, message);
	Serial.println(F("Message sent to MQTT server."));
	return true;
}
