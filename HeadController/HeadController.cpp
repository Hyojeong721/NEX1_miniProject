// HeadController.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "HeadController.h"

/// STL 라이브러리
#include <cmath>
#include <vector>
#include <thread>
#include <memory.h>
#include <mutex>

// TODO: 라이브러리 함수의 예제입니다.
void fnHeadController()
{
}

HeadController::HeadController()
{
	std::mutex tmp;
	mutex_ = &tmp;
	m_udpComm = new UDPcommunication(8080,8081,8082);
}

// 스타트 버튼 누르면 호출 호출 시 스레드 시작
void HeadController::starSimulation()
{
	if (!isExcute)
	{
		threads.push_back(std::thread(&HeadController::excuteSimTread, this));
	}

	for (auto& thread : threads)
	{
		thread.detach();
	}

	// 시나리오 설정 상태 확인
	UICtrlInput = true;
}

void HeadController::stopSimulation()
{
	UICtrlInput = false;
}

void HeadController::setMissleScenario(double cord[2])
{
	m_scen.SetMissile(cord);
}

void HeadController::setTargetScenario(double cord[4], char kind, double speed)
{
	m_scen.SetTarget(cord, kind, speed);
}

void HeadController::readData()
{
	//객체가 소멸시에 unlock 되는 특성을 가지고 있습니다.
	std::lock_guard<std::mutex> lg{ *(std::mutex*)mutex_ };
	
	// 통신으로 데이터 받기 구현
}

void HeadController::writeStatusData()
{
	//객체가 소멸시에 unlock 되는 특성을 가지고 있습니다.
	std::lock_guard<std::mutex> lg{ *(std::mutex *)mutex_ };
	
	// 통신으로 데이터 보내기 구현
	CONTROLLER_STATUS trans;
	trans = { m_status,m_tickTime };
	m_udpComm->send_('1', trans, 0);		// 운용통제기 상태 보내기
	m_udpComm->send_('1', trans, 1);		// 운용통제기 상태 보내기
}

void HeadController::update()
{
	if (m_status == HEAD_CONTROLLER_STATUS::READY)
	{
		// 시나리오 배포 및 배포 확인(통신으로)

		
		// 시나리오 설정이 완료되고 start 버튼이 눌린다면 RUN으로 넘어간다.

		// // 0, 상태보내기 (공통)/////////////////////////////////////////////////////////////////////////////////////////////
		writeStatusData();

		// 1. 유도탄 시나리오 보내기///////////////////////////////////////////////////////////////////////////////////////////////
		m_udpComm->send_('3',m_scen.GetMissile(),0);

		// 2. 위협기 시나리오 보내기////////////////////////////////////////////////////////////////////////////////////////
		m_udpComm->send_('4',m_scen.GetTarget(), 1);

		// 3. 요격 상태정보 계산후 보내기
		attackInfo = attackevent.CalculateAttackEvent(m_scen.GetMissile(), m_scen.GetTarget());
		if (attackevent.CalculateAttackEvent(m_scen.GetMissile(), m_scen.GetTarget()).checkAttackAvailable == false) // 요격계산 or 탐지 실패한 경우
		{
			m_status = HEAD_CONTROLLER_STATUS::END;	// 요격이 안되면 운용상태 종료로 변경
		}
		else
		{
			m_udpComm->send_('8', attackInfo, 0);
		}

		if (UICtrlInput)
		{
			m_status = HEAD_CONTROLLER_STATUS::RUN;
		}
	}
	else if (m_status == HEAD_CONTROLLER_STATUS::RUN)
	{
		// 운용중 수도코드
		/*
		* 0. 타이머 업데이트
		* 1. 유도탄 정보 받기
		* 2. 위협기 모의정보 받기
		* 3. 충돌여부 판단
		*/

		///  0. 타이머 업데이트 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_tickTime += 0.5;

		// // 0, 상태보내기 (공통)/////////////////////////////////////////////////////////////////////////////////////////////
		writeStatusData();

		// 1. 유도탄 정보 받기 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_udpComm->get_data('6', m_missleState, sizeof(m_missleState));

		//  2. 위협기 모의정보 받기 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_udpComm->get_data('6', m_targetState, sizeof(m_targetState));

		//  3. 충돌여부 판단 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (checkDetonation() == true)
		{
			m_status = HEAD_CONTROLLER_STATUS::EVENT_CHECK;
		}
	}
	else if (m_status == HEAD_CONTROLLER_STATUS::EVENT_CHECK)
	{
		writeStatusData();
		m_status = HEAD_CONTROLLER_STATUS::END;
	}
	else if (m_status == HEAD_CONTROLLER_STATUS::END)
	{
		writeStatusData();
	}
}

void HeadController::excuteSimTread()
{
	while (m_status != HEAD_CONTROLLER_STATUS::END)
	{
		update();
	}
}

bool HeadController::checkDetonation()
{
	bool res = false;
	double distance = sqrt(pow(m_missleState.position[0], 2) - pow(m_targetState.position[0], 2) + pow(m_missleState.position[1], 2) - pow(m_targetState.position[1], 2));
	if (distance <= 2.0)
	{
		res = true;
	}
	else;
	return res;
}
