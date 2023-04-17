// ScenarioControl.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"

#include "ScenarioControl.h"

void Missile::SetMissile(double coordinate[2], double range) {
	missileInfo._x = coordinate[0];
	missileInfo._y = coordinate[1];
	missileInfo.range = range;
}

MissileInfo Missile::GetMissile() {
	return missileInfo;
}

void Target::SetTarget(double coordinate[4], char kind, double speed) {
	targetInfo._sx = coordinate[0];
	targetInfo._sy = coordinate[1];
	targetInfo._ex = coordinate[2];
	targetInfo._ey = coordinate[3];
	targetInfo.kind = kind;
	targetInfo.speed = speed;
}

TargetInfo Target::GetTarget() {
	return targetInfo;
}

void ScenarioSetting::SetMissile(double cord[2], double range) {
	missile.SetMissile(cord, range);
}

void ScenarioSetting::SetTarget(double cord[4], char kind, double speed) {
	target.SetTarget(cord, kind, speed);
}

MissileInfo ScenarioSetting::GetMissile() {
	return missile.GetMissile();
}

TargetInfo ScenarioSetting::GetTarget() {
	return target.GetTarget();
}