#pragma once
#include <Ethernet.h>
#include <PubSubClient.h>

class Mqtt {
private:
	EthernetClient ethClient;
	PubSubClient client;

	const char* outTopic;
	const char* clientId;

	byte ip[4];
	unsigned int port;
	byte macAddress[6];


	void connectToEthernet();
	void connectToServer();

public:
	Mqtt(const byte ip[4], unsigned int port, const byte mac[6], const char* clientId, const char* outTopic);

	void setup();
	void loop();

	bool sendMessage(const char* message);
	bool isConnected() const;

	const byte* getIp() const;
	String ipToString(const byte ipArray[4]) const;
};