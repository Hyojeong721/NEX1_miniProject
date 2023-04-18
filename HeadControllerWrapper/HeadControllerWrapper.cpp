#include "pch.h"

#include "HeadControllerWrapper.h"

void CPPWAPPRER::CHeadControllerWrapper::setMissleScenario(double _x, double _y)
{
	double cord[2] = { _x,_y };
	m_headCtrl->setMissleScenario(cord);
	isTargetSet = true;
}

void CPPWAPPRER::CHeadControllerWrapper::setTargetScenario(double _sx, double _sy, double _ex, double _ey, int kind, double speed)
{
	double cord[4] = { _sx,_sy,_ex,_ey };
	m_headCtrl->setTargetScenario(cord, kind, speed);
	isMissleSet = true;
}

void CPPWAPPRER::CHeadControllerWrapper::getMisslePosition(double& _x, double& _y)
{
	_x = m_headCtrl->getMisslePosition().position[0];
	_y = m_headCtrl->getMisslePosition().position[1];
}

void CPPWAPPRER::CHeadControllerWrapper::getTargetPosition(double& _x, double& _y)
{
	_x = m_headCtrl->getTargetPosition().position[0];
	_y = m_headCtrl->getTargetPosition().position[1];
}
