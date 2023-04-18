#pragma once
#include "HeadControllerIICD.h"
#include "ScenarioSetting.h"

#include <vector>
#include <thread>
#include <mutex>

class HeadController
{
public: 
	HeadController() { };		//��� �ֱ� ����
	
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
	void updateStatus();	// ���� ������Ʈ
	void excuteSimTread();	// �ùķ��̼� ������ ����
	bool checkDetonation();	// �浹 �����Ǵ�
private:
	
	HEAD_CONTROLLER_STATUS m_status {HEAD_CONTROLLER_STATUS::READY};
	ScenarioSetting m_scen;
	State m_missleState;
	State m_targetState;


	//thread info
	bool isExcute{ false };
	std::vector<std::thread> threads;
	std::mutex mutex_;
};

