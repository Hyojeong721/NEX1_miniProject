#pragma once
#include "HeadControllerIICD.h"
#include <iostream>
#include < cmath >

class AttackEvent
{
public:
	AttackEvent() {};
	~AttackEvent() {};
	AttackInfo CalculateAttackEvent();
//private:
	AttackInfo CalculateAttackEvent(MissileInfo missileinfo, TargetInfo targetInfo);
private:
	void SettingParameters(MissileInfo missileinfo, TargetInfo targetInfo);
	AttackInfo InitializationAttackEvent();
	bool CheckAttackAvailable();
	//
	double CalculateDistance(double tar_x, double tar_y);
	//-------------------------------------
	double mis_x_0;		 // 미사일 x 초기 위치
	double mis_y_0;		 // 미사일 y 초기 위치
	double mis_vel;		 // 미사일 속도 = dedault
	double missileRange; // 미사일 사거리

	double tar_x_0;	// 공중위협 x 초기 위치
	double tar_y_0;	// 공중위협 y 초기 위치
	double tar_x_f;	// 공중위협 x 목표 위치
	double tar_y_f;	// 공중위협 y 목표 위치
	double tar_vel;	// 공중위협 속도 (mach)
	//--------------------------------------
	double vecTarget[2];	// 공중위협 이동 경로의 방향 벡터 (x,y)
	double tar_x, tar_y;	// 공중위협 예상 위치

	double detectTime;		// 공중위협이 유도탄 사격가능 범위에 들어 온 시간
	//--------------------------------------

};
