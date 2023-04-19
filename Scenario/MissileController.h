#pragma once
#include "MissileModel.h"
#include "../UDPcommunication/UDPcommunication.h"
#include "../ScenarioControl/Message.h"
#include <Windows.h>

class MissileController {
private:
	MissileModel missileModel;
	UDPcommunication udpCommunication{ 8081, 8080 };

public:
	void RecieveScenario();
	void RecieveCommand();
	void RecieveAttackEvent();
	void SendCommandState();
	void SendMissilePosition(double time);
	void Run();
};