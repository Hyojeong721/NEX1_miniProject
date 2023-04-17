// HeadController.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "HeadController.h"

// TODO: 라이브러리 함수의 예제입니다.
void fnHeadController()
{
}

void HeadController::starSimulation(double _dt)
{
	m_status = HEAD_CONTROLLER_STATUS::RUN;
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

void HeadController::update()
{
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
