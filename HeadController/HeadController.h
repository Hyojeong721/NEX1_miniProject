#pragma once
#include "HeadControllerIICD.h"
#include "ScenarioSetting.h"

class HeadController
{
public: 
	HeadController() { };		//통신 주기 설정
	
	void starSimulation(double dt);							// 시뮬레이션 수행
	void stopSimulation();									// 시뮬레이션 중지

	void setMissleScenario(double cord[2], double range = 50000);		// int _sx, int _sy
	void setTargetScenario(double cord[4], char kind, double speed);
	
	inline State getMisslePosition() { return m_missleState; };
	inline State getTargetPosition() { return m_targetState; };
private:
	void update();			//상태에 따른 모의기 운영
private:
	HEAD_CONTROLLER_STATUS m_status {HEAD_CONTROLLER_STATUS::READY};
	ScenarioSetting m_scen;
	State m_missleState;
	State m_targetState;
};

