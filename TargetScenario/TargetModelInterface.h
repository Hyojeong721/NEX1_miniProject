#pragma once

#include "../ScenarioControl/Message.h"
#include <iostream>

class TargetModel {
private:
	TargetInfo init, nowPosition;
	AttackInfo attackEventMessage;
	HEAD_CONTROLLER_STATUS controllerStatus;
	double velocity;
	double vector[2];

	TargetInfo UpdatePosition(double time);

public:
	TargetModel() {};
	~TargetModel() {};

	void SetTargetInformations(TargetInfo targetInfo);
	void SetAttackInfo(AttackInfo msg);
	void SetControllerStatus(HEAD_CONTROLLER_STATUS status);
	//void InitializationTarget(double init_x, double init_y, double goal_x, double goal_y, double vel);
	HEAD_CONTROLLER_STATUS GetControlStatus();
	TargetInfo OutTargetPosition(double time);
	void StopSimulator();
};