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
}

void HeadController::starSimulation()
{
	m_status = HEAD_CONTROLLER_STATUS::RUN;

	if (!isExcute)
	{
		threads.push_back(std::thread(&HeadController::excuteSimTread, this));
	}

	for (auto& thread : threads)
	{
		thread.detach();
	}
}

void HeadController::stopSimulation()
{
	m_status = HEAD_CONTROLLER_STATUS::END;
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
	updateStatus();
	if (m_status == HEAD_CONTROLLER_STATUS::READY)
	{

	}
	else if (m_status == HEAD_CONTROLLER_STATUS::RUN)
	{

	}
	else if (m_status == HEAD_CONTROLLER_STATUS::EVENT_CHECK)
	{

	}
	else if (m_status == HEAD_CONTROLLER_STATUS::END)
	{

	}
}

void HeadController::updateStatus()
{
	// 충돌 상태가 될 시 이벤트 처리 상태로 전환
	if (m_status == HEAD_CONTROLLER_STATUS::RUN && checkDetonation())
	{
		m_status = HEAD_CONTROLLER_STATUS::EVENT_CHECK;
	}
	else if(m_status == HEAD_CONTROLLER_STATUS::EVENT_CHECK)
	{
		//  요격 이벤트 전송
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
