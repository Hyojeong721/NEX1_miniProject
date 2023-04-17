#pragma once
enum class HEAD_CONTROLLER_STATUS : unsigned int
{
	READY = 0U,		//운용준비상태
	RUN,		    //운용중 상태
	EVENT_CHECK,	//요격확인 상태
	END				//운용종료 상태
};


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

struct State
{
	double position[2]{0,};
};