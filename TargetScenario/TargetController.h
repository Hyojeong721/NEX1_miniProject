#pragma once
#include "TargetModelInterface.h"
#include "../UDPcommunication/UDPcommunication.h"
#include "../ScenarioControl/Message.h"
#include <Windows.h>


class TargetController {
private:
	TargetModel targetModel;
	UDPcommunication udpCommunication{ 8082, 8080 };

public:
	void RecieveScenario();
	void RecieveCommand();
	void RecieveAttackEvent();
	void SendCommandState();
	void SendTargetPosition(double time);
	void Run();
};