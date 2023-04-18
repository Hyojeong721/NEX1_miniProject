#pragma once
#include "Message.h"

//시나리오 입력
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

//유도탄 시작 지점 x,y 좌표
class Missile {
private:
	MissileInfo missileInfo;

public:
	void SetMissile(double coordinate[2], double range);
	MissileInfo GetMissile();
};

//공중위협 시작 지점 x,y 좌표
//공중위협 종료 지점 x,y 좌표
class Target {
private:
	TargetInfo targetInfo;

public:
	void SetTarget(double coordinate[4], char kind, double speed);
	TargetInfo GetTarget();
};