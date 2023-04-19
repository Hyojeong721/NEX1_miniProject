#include "pch.h"

#include "HeadControllerWrapper.h"

void CPPWAPPRER::CHeadControllerWrapper::startSimulator()
{
	m_headCtrl->starSimulation();
}

void CPPWAPPRER::CHeadControllerWrapper::setMissleScenario(double _x, double _y)
{
	double cord[2] = { _x,_y };
	m_headCtrl->setMissleScenario(cord);
}

void CPPWAPPRER::CHeadControllerWrapper::setTargetScenario(double _sx, double _sy, double _ex, double _ey, int kind, double speed)
{
	double cord[4] = { _sx,_sy,_ex,_ey };
	m_headCtrl->setTargetScenario(cord, kind, speed);
}

void CPPWAPPRER::CHeadControllerWrapper::getMissleScenario(double& x, double& y)
{
	x = m_headCtrl->getScenarioinfo().GetMissile()._x;
	y = m_headCtrl->getScenarioinfo().GetMissile()._y;
}

void CPPWAPPRER::CHeadControllerWrapper::getTargetScenario(double& _sx, double& _sy, double& _ex, double& _ey, int &_kind, double &_speed)
{
	_sx = m_headCtrl->getScenarioinfo().GetTarget()._sx;
	_sy = m_headCtrl->getScenarioinfo().GetTarget()._sy;
	_ex = m_headCtrl->getScenarioinfo().GetTarget()._ex;
	_ey = m_headCtrl->getScenarioinfo().GetTarget()._ey;
	_kind = m_headCtrl->getScenarioinfo().GetTarget().kind;
	_speed = m_headCtrl->getScenarioinfo().GetTarget().speed;
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
