#pragma once
enum class HEAD_CONTROLLER_STATUS : unsigned int
{
	READY = 0U,		//����غ����
	RUN,		    //����� ����
	EVENT_CHECK,	//���Ȯ�� ����
	END				//������� ����
};


// ����ź ����
struct MissileInfo {
	double _x, _y;
	double range;
};

// ���� ������ ����
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