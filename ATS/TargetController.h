#pragma once
#include "TargetModel.h"
#include "../UDPcommunication/UDPcommunication.h"
#include <Windows.h>


class TargetController {
private:
	TargetModel targetModel;
	UDPcommunication udpCommunication{ 8080,8082 };

	void RecieveScenario();
	void RecieveCommand();
	void RecieveAttackEvent();
	void SendCommandState();
	void SendTargetPosition();

public:

	void Run();
};