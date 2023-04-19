#pragma once
#include "ScenarioSetting.h"
#include "AttackEvent.h"
//#include "UDPcommunication.h"

#include <vector>
#include <thread>
#include <memory.h>
#include <mutex>

class HeadController
{
public:
	HeadController();		//��� �ֱ� ����

	void starSimulation();							// �ùķ��̼� ����
	void stopSimulation();							// �ùķ��̼� ����

	void setMissleScenario(double cord[2]);		// int _sx, int _sy
	void setTargetScenario(double cord[4], char kind, double speed);

	inline unsigned int getHeadControlStatus() { return static_cast<unsigned int>(m_status); };
	inline State getMisslePosition() { return m_missleState; };
	inline State getTargetPosition() { return m_targetState; };
private:
	void readData();		// ������ �б�
	void writeData();		// ������ ����
	void update();			//���¿� ���� ���Ǳ� �
	void excuteSimTread();	// �ùķ��̼� ������ ����
	bool checkDetonation();	// �浹 �����Ǵ�
private:
	AttackEvent attackevent;
	AttackInfo attackInfo;
	HEAD_CONTROLLER_STATUS m_status{ HEAD_CONTROLLER_STATUS::READY };
	ScenarioSetting m_scen;
	State m_missleState;
	State m_targetState;						
	//UDPcommunication* m_udpComm;
	double m_tickTime{ 0.0 };

	//thread info
	bool isExcute{ false };
	bool UICtrlInput{ false };
	std::vector<std::thread> threads;
	void* mutex_;
};

