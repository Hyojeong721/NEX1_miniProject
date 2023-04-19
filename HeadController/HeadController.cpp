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
	//m_udpComm = new UDPcommunication(8080,8081,8082);
}

// 스타트 버튼 누르면 호출 호출 시 스레드 시작
void HeadController::starSimulation()
{
	if (!isExcute)
	{
		isExcute = true;
		excuteSimTread();
	}

	//// 시나리오 설정 상태 확인
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

void HeadController::writeData()
{
	//객체가 소멸시에 unlock 되는 특성을 가지고 있습니다.
	std::lock_guard<std::mutex> lg{ *(std::mutex *)mutex_ };
	
	// 통신으로 데이터 보내기 구현
}

void HeadController::update()
{
	if (m_status == HEAD_CONTROLLER_STATUS::READY)
	{
		// 시나리오 배포 및 배포 확인(통신으로)

		
		// 시나리오 설정이 완료되고 start 버튼이 눌린다면 RUN으로 넘어간다.

		// // 0, 상태보내기 (공통)/////////////////////////////////////////////////////////////////////////////////////////////
		//m_udpComm->send_('1', m_status, 0);		// 운용통제기 상태 보내기
		//m_udpComm->send_('1', m_status, 1);		// 운용통제기 상태 보내기

		// 1. 유도탄 시나리오 보내기///////////////////////////////////////////////////////////////////////////////////////////////
		//m_udpComm->send_('3',m_scen.GetMissile(),0);

		// 2. 위협기 시나리오 보내기////////////////////////////////////////////////////////////////////////////////////////
		//m_udpComm->send_('4',m_scen.GetTarget(), 1);

		// 3. 요격 상태정보 계산후 보내기
		attackInfo = attackevent.CalculateAttackEvent(m_scen.GetMissile(), m_scen.GetTarget());
		if (attackevent.CalculateAttackEvent(m_scen.GetMissile(), m_scen.GetTarget()).checkAttackAvailable == false) // 요격계산 or 탐지 실패한 경우
		{
			m_status = HEAD_CONTROLLER_STATUS::END;	// 요격이 안되면 운용상태 종료로 변경
		}
		else
		{
			//m_udpComm->send_('8', attackInfo, 0);
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
		* 3. 시간정보 유도탄 전송
		* 4. 시간정보 위협기 전송
		* 5. 충돌여부 판단
		*/

		///  0. 타이머 업데이트 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_tickTime += 0.5;

		// 1. 유도탄 정보 받기 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//m_udpComm->get_data('6', m_missleState, sizeof(m_missleState));

		//  2. 위협기 모의정보 받기 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//m_udpComm->get_data('6', m_targetState, sizeof(m_targetState));
	}
	else if (m_status == HEAD_CONTROLLER_STATUS::EVENT_CHECK)
	{
		/*
		* 0. 위협기 종료정보 전송
		* 1. 유도탄 종료정보 전송
		* 1. 위협기 종료 확인 정보 받기
		* 2. 유도탄 종료 확인 정보 받기
		* 3. 종료 여부 확인
		*/
	}
	else if (m_status == HEAD_CONTROLLER_STATUS::END)
	{
		/*
		* 0. 종료 상태 설정 (스레드 종료)
		*/
	}

	// 인터페이스에서 GUI화면 업데이트 이벤트 호출
	if (m_cbf)
	{
		m_cbf();
	}
}

void HeadController::excuteSimTread()
{
	std::thread t1([&]() {
		while (m_status != HEAD_CONTROLLER_STATUS::END)
		{
			update();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		});

	t1.detach();
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
