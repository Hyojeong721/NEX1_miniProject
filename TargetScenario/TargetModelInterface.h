#pragma once

#include "../ScenarioControl/Message.h"

class TargetModel {
private:
	TargetInfo init, goal, nowPosition;
	HEAD_CONTROLLER_STATUS controllerStatus;
	double velocity;
	double vector[2];

	TargetInfo UpdatePosition(double time);

public:
	TargetModel() {};
	~TargetModel() {};

	void SetTargetInformations(TargetInfo targetInfo[2]);
	void SetControllerStatus(HEAD_CONTROLLER_STATUS status);
	//void InitializationTarget(double init_x, double init_y, double goal_x, double goal_y, double vel);
	TargetInfo OutTargetPosition(double time);
	void StopSimulator();
};