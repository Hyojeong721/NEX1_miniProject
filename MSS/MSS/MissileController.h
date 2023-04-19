#pragma once
#include "MissileModel.h"
#include "UDPcommunication.h"
#include "Message.h"
#include <Windows.h>

class MissileController {
private:
	MissileModel missileModel;
	UDPcommunication udpCommunication{ 8081, 8080 };

	void RecieveScenario();
	void RecieveCommand();
	void RecieveAttackEvent();
	void SendCommandState();
	void SendMissilePosition(double time);

public:
	
	void Run();
};