#pragma once
#include "../UDPcommunication/kimbabo.h"
#include <iostream>
#include <stdlib.h>

/**
 * @brief Position of Missile at given time
 */
class MissileModel
{
private:
	MissileInfo init, goal, nowPosition;
	AttackInfo attackEventMessage;
	CONTROLLER_STATUS controllerStatus;
	double velocity;
	double vector[2];

	MissileInfo UpdatePosition(double time);

public:
	MissileModel() {};
	~MissileModel() {};

	void SetMissileInformations(MissileInfo missileInfo[2]);
	void SetAttackInfo(AttackInfo msg);
	void SetControllerStatus(CONTROLLER_STATUS status);
	CONTROLLER_STATUS GetControllerStatus();
	//void InitializationMissile(double init_x, double init_y, double goal_x, double goal_y, double vel);
	MissileInfo OutMissilePosition();
	void StopSimulator();

};