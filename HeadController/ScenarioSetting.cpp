// ScenarioControl.cpp : ���� ���̺귯���� ���� �Լ��� �����մϴ�.
//
#include "pch.h"
#include "ScenarioSetting.h"
//

void Missile::SetMissile(double coordinate[2]) {
	missileInfo._x = coordinate[0];
	missileInfo._y = coordinate[1];
}

MissileInfo Missile::GetMissile() {
	return missileInfo;
}

void Target::SetTarget(double coordinate[4], int kind, double speed) {
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

void ScenarioSetting::SetMissile(double cord[2]) {
	missile.SetMissile(cord);
}

void ScenarioSetting::SetTarget(double cord[4], int kind, double speed) {
	target.SetTarget(cord, kind, speed);
}

MissileInfo ScenarioSetting::GetMissile() {
	return missile.GetMissile();
}

TargetInfo ScenarioSetting::GetTarget() {
	return target.GetTarget();
}