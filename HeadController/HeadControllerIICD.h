#pragma once

enum class HEAD_CONTROLLER_STATUS : int
{
	READY = 0U,		//운용준비상태
	RUN,		    //운용중 상태
	EVENT_CHECK,	//요격확인 상태
	END,
	TRASH//운용종료 상태
};

enum class COMM_STATUS : unsigned
{
	NS = 0U,    //아무것도 아닐때
	OK,			// 정상
	NON			// 비정상
};

struct CONTROLLER_STATUS
{
	HEAD_CONTROLLER_STATUS status{ HEAD_CONTROLLER_STATUS::READY };
	double tickTime{0.0};
};

// 유도탄 시나리오
struct MissileInfo {
	double _x, _y;		    // 발사점
};

// 공중 위협기 시나리오 정보 
struct TargetInfo {
	double _sx, _sy;		// 발사점
	double _ex, _ey;		// 탄착점5
	int kind;				// 위협기 종류
	double speed;			// 위협기 속도
};


// 모의 결과 수신 정보
struct State
{	
	double position[2]{0,};		//		
};

// 통신 확인 (송/수신)
struct CheckSum
{
	COMM_STATUS status{COMM_STATUS::NS};		   // 통신상태
};

struct AttackEventMessge
{
	bool isSuccess{ false };		// 성공  / 실패
};

// 요격 이벤트 정보
struct AttackInfo {
	bool checkAttackAvailable;	// 요격 가능 여부
	double launchTime;			// 유도탄 발사 시간
	double attackPoint_x;		// 요격 지점 x 좌표
	double attackPoint_y;		// 요격 지점 y 좌표



};