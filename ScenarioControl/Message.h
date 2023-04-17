#pragma once

struct MissileInfo {
	double _x, _y;
	double range;
};

struct TargetInfo {
	double _sx, _sy;
	double _ex, _ey;
	char kind;
	double speed;
};