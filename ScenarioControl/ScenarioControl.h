#pragma once
#include "Message.h"

//�ó����� �Է�
class ScenarioSetting {
private:
	Missile missile;
	Target target;

public:
	void SetMissile(double cord[2], double range);
	void SetTarget(double cord[4], char kind, double speed);
	MissileInfo GetMissile();
	TargetInfo GetTarget();
};

//����ź ���� ���� x,y ��ǥ
class Missile {
private:
	MissileInfo missileInfo;

public:
	void SetMissile(double coordinate[2], double range);
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