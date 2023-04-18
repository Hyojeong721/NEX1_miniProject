#pragma once
#include "HeadControllerIICD.h"
#include "ScenarioSetting.h"

class HeadController
{
public: 
	HeadController() {};
	void setMissleScenario(int _sx, int _sy);
	void setTargetScenario(int _sx, int _sy, int _ex, int _ey, char _kind, double _speed);

private:
	HEAD_CONTROLLER_STATUS m_status {HEAD_CONTROLLER_STATUS::READY};
	//ScenarioSetting m_scen;
};