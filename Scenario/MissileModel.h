#pragma once
#include "../ScenarioControl/Message.h"
#include <iostream>
#include <stdlib.h>

/**
 * @brief Position of Missile at given time
 */
class MissileModel
{
private:
	MissileInfo init, goal, nowPosition;
	HEAD_CONTROLLER_STATUS controllerStatus;
	double velocity;
	double vector[2];

	MissileInfo UpdatePosition(double time);

public:
	MissileModel() {};
	~MissileModel() {};

	void SetMissileInformations(MissileInfo missileInfo[2]);
	void SetControllerStatus(HEAD_CONTROLLER_STATUS status);
	//void InitializationMissile(double init_x, double init_y, double goal_x, double goal_y, double vel);
	MissileInfo OutMissilePosition(double time);
	void StopSimulator();

};