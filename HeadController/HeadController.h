#pragma once
#include "ScenarioSetting.h"
#include "AttackEvent.h"
//#include "UDPcommunication.h"

#include <vector>
#include <thread>
#include <memory.h>
#include <mutex>

// 함수포인터(function pointer) 타입 정의
typedef void(*CALLBACK_FUNC)();


class HeadController
{
public:
	HeadController();		//통신 주기 설정

	void starSimulation();							// 시뮬레이션 수행
	void stopSimulation();							// 시뮬레이션 중지

	void setMissleScenario(double cord[2]);		// int _sx, int _sy
	void setTargetScenario(double cord[4], char kind, double speed);

	inline int getHeadControlStatus() { return static_cast<int>(m_status); };
	inline State getMisslePosition() { return m_missleState; };
	inline State getTargetPosition() { return m_targetState; };

	// 이벤트 스레드 관련 메서드
	void SetHandler(CALLBACK_FUNC cli_cb)
	{
		m_cbf = cli_cb;
	}
private:
	void readData();		// 데이터 읽기
	void writeData();		// 데이터 쓰기
	void update();			//상태에 따른 모의기 운영
	void excuteSimTread();	// 시뮬레이션 스레드 수행
	bool checkDetonation();	// 충돌 여부판단
private:
	AttackEvent attackevent;
	AttackInfo attackInfo;
	HEAD_CONTROLLER_STATUS m_status{ HEAD_CONTROLLER_STATUS::READY };
	ScenarioSetting m_scen;
	State m_missleState;
	State m_targetState;						
	//UDPcommunication* m_udpComm;
	double m_tickTime{ 0.0 };

	// callback Pointer
	CALLBACK_FUNC m_cbf{ nullptr };

	//thread info
	bool isExcute{ false };
	bool UICtrlInput{ false };
	std::vector<std::thread> threads;
	void* mutex_;
};

