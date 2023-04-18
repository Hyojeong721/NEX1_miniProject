#pragma once
#include "HeadControllerIICD.h"
#include "pch.h"

//유도탄 시작 지점 x,y 좌표
class Missile {
private:
	MissileInfo missileInfo;

public:
	void SetMissile(double coordinate[2]);
	MissileInfo GetMissile();
};

//공중위협 시작 지점 x,y 좌표
//공중위협 종료 지점 x,y 좌표
class Target {
private:
	TargetInfo targetInfo;

public:
	void SetTarget(double coordinate[4], int kind, double speed);
	TargetInfo GetTarget();
};

class ScenarioSetting {
public:
	void SetMissile(double cord[2]);
	void SetTarget(double cord[4], int kind, double speed);
	MissileInfo GetMissile();
	TargetInfo GetTarget();

private:
	Missile missile;
	Target target;
};