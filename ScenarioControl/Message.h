#pragma once

// 공통 메세지 설계 파일

// 유도탄 정보
struct MissileInfo {
	double _x, _y;
	double range;
};

// 공중 위협기 정보
struct TargetInfo {
	double _sx, _sy;
	double _ex, _ey;
	char kind;
	double speed;
};