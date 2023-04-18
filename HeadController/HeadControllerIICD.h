#pragma once
enum class HEAD_CONTROLLER_STATUS : unsigned int
{
	READY = 0U,		//운용준비상태
	RUN,		    //운용중 상태
	EVENT_CHECK,	//요격확인 상태
	END				//운용종료 상태
};


struct MissleState
{

};