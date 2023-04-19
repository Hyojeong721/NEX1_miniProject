#pragma once
#include "MissileModel.h"
#include "../UDPcommunication/UDPcommunication.h"
#include <Windows.h>

class MissileController {
private:
	MissileModel missileModel;
	UDPcommunication udpCommunication{ 8081, 8080 };

	void RecieveScenario();
	void RecieveCommand();
	void RecieveAttackEvent();
	void SendCommandState();
	void SendMissilePosition();

public:

	void Run();
};