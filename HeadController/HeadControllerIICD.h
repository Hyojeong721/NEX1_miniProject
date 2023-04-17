#pragma once
enum class HEAD_CONTROLLER_STATUS : unsigned int
{
	READY = 0U,		//운용준비상태
	RUN,		    //운용중 상태
	EVENT_CHECK,	//요격확인 상태
	END				//운용종료 상태
};

enum class COMM_STATUS : unsigned
{
	NS = 0U,    //아무것도 아닐때
	OK,			// 정상
	NON			// 비정상
};


/// <summary>
/// 통신 목록
/// </summary>
/// 

// 유도탄 시나리오
struct MissileInfo {
	double _x, _y;		    // 발사점
};

// 공중 위협기 시나리오 정보 
struct TargetInfo {
	double _sx, _sy;		// 발사점
	double _ex, _ey;		// 탄착점
	char kind;				// 위협기 종류
	double speed;			// 위협기 속도
};

// 모의 결과 수신 정보
struct State
{	
	double position[2]{0,};		//		
};

// 통신 확인 (송/수신)
struct checkSum
{
	COMM_STATUS status{COMM_STATUS::NS};		   // 통신상태
	double tick{0.0};			   //운용통제기 현재 시간
};