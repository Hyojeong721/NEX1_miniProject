#pragma once
#include "MissileModel.h"
#include "../UDPcommunication/UDPcommunication.h"
#include "../ScenarioControl/Message.h"

class MissileController {
private:
	MissileModel missileModel;
	UDPcommunication udpCommunication{ 1030, 2030 };

public:
	void RecieveScenario();
	void RecieveCommand();
	void RecieveAttackEvent();
	void SendMissilePosition();
};