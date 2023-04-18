#pragma once
#include "HeadControllerIICD.h"
#include "pch.h"

//����ź ���� ���� x,y ��ǥ
class Missile {
private:
	MissileInfo missileInfo;

public:
	void SetMissile(double coordinate[2]);
	MissileInfo GetMissile();
};

//�������� ���� ���� x,y ��ǥ
//�������� ���� ���� x,y ��ǥ
class Target {
private:
	TargetInfo targetInfo;

public:
	void SetTarget(double coordinate[4], char kind, double speed);
	TargetInfo GetTarget();
};

class ScenarioSetting {
public:
	void SetMissile(double cord[2]);
	void SetTarget(double cord[4], char kind, double speed);
	MissileInfo GetMissile();
	TargetInfo GetTarget();

private:
	Missile missile;
	Target target;
};