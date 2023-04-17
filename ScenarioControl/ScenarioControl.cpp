// ScenarioControl.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"

#include "ScenarioControl.h"

void Missile::SetMissile(double coordinate[2], double range) {
	_x = coordinate[0];
	_y = coordinate[1];
	_range = range;
}

void Target::SetTarget(double coordinate[4], char kind, double speed) {
	_sx = coordinate[0];
	_sy = coordinate[1];
	_ex = coordinate[2];
	_ey = coordinate[3];
	_kind = kind;
	_speed = speed;
}

void ScenarioSetting::SetMissile(double cord[2], double range) {
	missile.SetMissile(cord, range);
}

void ScenarioSetting::SetTarget(double cord[4], char kind, double speed) {
	target.SetTarget(cord, kind, speed);
}