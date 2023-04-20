#pragma once

#include "../UDPcommunication/kimbabo.h"
#include <iostream>

class TargetModel {
private:
	TargetInfo init;
	State nowPosition;
	AttackInfo attackEventMessage;
	CONTROLLER_STATUS controllerStatus;
	double velocity;
	double vector[2];

	State UpdatePosition(double time);

public:
	TargetModel() {};
	~TargetModel() {};

	void SetTargetInformations(TargetInfo targetInfo);
	void SetAttackInfo(AttackInfo msg);
	void SetControllerStatus(CONTROLLER_STATUS status);
	//void InitializationTarget(double init_x, double init_y, double goal_x, double goal_y, double vel);
	CONTROLLER_STATUS GetControlStatus();
	State OutTargetPosition();

	void StopSimulator();
};