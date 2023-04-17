#pragma once
#include "HeadControllerIICD.h"
#include "ScenarioSetting.h"

class HeadController
{
public: 
	HeadController() { };		//��� �ֱ� ����
	
	void starSimulation();							// �ùķ��̼� ����
	void stopSimulation();									// �ùķ��̼� ����

	void setMissleScenario(double cord[2]);		// int _sx, int _sy
	void setTargetScenario(double cord[4], char kind, double speed);
	
	inline State getMisslePosition() { return m_missleState; };
	inline State getTargetPosition() { return m_targetState; };
private:
	void update();			//���¿� ���� ���Ǳ� �
	void updateStatus();	// ���� ������Ʈ
	bool checkDetonation();	// �浹 �����Ǵ�
private:
	HEAD_CONTROLLER_STATUS m_status {HEAD_CONTROLLER_STATUS::READY};
	ScenarioSetting m_scen;
	State m_missleState;
	State m_targetState;

};

