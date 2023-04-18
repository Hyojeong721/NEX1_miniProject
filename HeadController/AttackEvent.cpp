#include"pch.h"
#include"AttackEvent.h"

AttackInfo AttackEvent::CalculateAttackEvent(MissileInfo missileinfo, TargetInfo targetInfo)
{
	//------------------------------------------------
	// 	1. 시나리오 파라미터 세팅(유도탄, 공중위협 - 속도, 초기위치, 목표위치)
	SettingParameters(missileinfo, targetInfo);
	//------------------------------------------------
	//  2. 리턴값 초기화
	AttackInfo attackinfo;
	attackinfo = InitializationAttackEvent();
	//------------------------------------------------
	//  3. 탐지 가능 여부 확인
	attackinfo.checkAttackAvailable = CheckAttackAvailable();
	if (attackinfo.checkAttackAvailable == false)
		return attackinfo;				// 탐지가 불가능 하면 종료 -> attackinfo에 false 저장
	//------------------------------------------------
	// 4. 요격 위치, 시간 계산
	//---------------------------------
	// 4.1 유도탄의 시간/거리 배열 생성
	const int noArray = 101;			// 시간/거리 베열의 요소 개수

	double arrMisTime[noArray];			// 유도탄 비행시간
	double arrMisRange[noArray];		// 유도탄 비행시간에 따른 사격 거리

	arrMisTime[0] = 0.0;
	arrMisRange[0] = 0.0;

	for (int i = 1; i < noArray; i++)
	{
		arrMisRange[i] = arrMisRange[i - 1] + missileRange / ((double)noArray - 1);	// 50km를 noArray개수 만큼 나눔
		arrMisTime[i] = arrMisRange[i] / mis_vel;									// 각 arrMisRange 요소에 해당되는 거리에 도달하는데 소요되는 시간
	}
	//---------------------------------
	// 4.2 공중위협이 요격 가능한지 확인
	bool endflag = false;	// 공중위협 요격 가능 여부

	double attackTime = 0.0;
	double distance = 0.0;
	double distanceAttack = 0.0;
	double attackPoint_x = 0.0;
	double attackPoint_y = 0.0;

	for (int i = 0; i < noArray - 1; i++) {
		attackTime = detectTime + arrMisTime[i]; // (예상요격시간) = (탐지시간) + (유도탄 비행시간)

		tar_x = tar_x_0 + vecTarget[0] * attackTime * tar_vel;	// 예상요격시간에 공중위협의 위치 계산
		tar_y = tar_y_0 + vecTarget[1] * attackTime * tar_vel;

		distance = CalculateDistance(tar_x, tar_y);		// "예상요격지점"에서 "유도탄 초기위치" 까지 거리 

		for (int k = 0; k < noArray - 1; k++) {
			if ((attackTime - detectTime) > arrMisTime[k]) {		// "(요격예상시간)-(탐지시간)" 이 "유도탄 비행시간" 보다 클 때 실행
				distanceAttack = distance;						// (요격지점)과 (유도탄 초기위치)까지 거리

				attackPoint_x = tar_x;		// (요격 지점) == (공중위협 예상 위치)
				attackPoint_y = tar_y;

				endflag = true;
				break;		// 요격 가능 지점을 찾았으므로 중단
			}
			else
				break;		// 유도탄이 비행해서 요격할 수 없는 구간
		}
		if (endflag)		// 요격 가능 지점을 찾았으므로 중단
			break;
	}
	if (endflag == false) {	// 요격 가능 지점을 찾지 못한 경우
		attackinfo.checkAttackAvailable = false;
		return attackinfo;	// 탐지는 하였으나 요격이 불가능한 경우
	}
	//---------------------------------
	// 4.3 유도탄 발사 시간 계산
	attackinfo.launchTime = attackTime - (distanceAttack / mis_vel);	// 유도탄 발사시간 = 요격예상시간 - (요격지점과 유도탄초기위치거리/유도탄 속도)

	//---------------------------------
	// 4.4 유도탄 요격 위치 == 유도탄 목표 위치
	attackinfo.attackPoint_x = attackPoint_x;
	attackinfo.attackPoint_y = attackPoint_y;



	return attackinfo;
}


void AttackEvent::SettingParameters(MissileInfo missileinfo, TargetInfo targetInfo)
{
	mis_x_0 = missileinfo._x;
	mis_y_0 = missileinfo._y;
	mis_vel = 1.0 * 340;				// mach->m/s (default)
	missileRange = 50000;				// 50 km(default)

	tar_x_0 = targetInfo._sx;
	tar_y_0 = targetInfo._sy;
	tar_x_f = targetInfo._ex;
	tar_y_f = targetInfo._ey;
	tar_vel = targetInfo.speed * 340;	// mach->m/s
}

AttackInfo AttackEvent::InitializationAttackEvent()
{
	AttackInfo attackInfo;

	attackInfo.checkAttackAvailable = false;
	attackInfo.attackPoint_x = 0.0;
	attackInfo.attackPoint_y = 0.0;
	attackInfo.launchTime = 0.0;

	return AttackInfo();
}

bool AttackEvent::CheckAttackAvailable()
{
	bool checkAvailable = false;
	//--------------------------------------
	// Parameters Setting
	double dt = 0.1;
	double time_f = 10000.0;	// 가능한 큰 값
	double time = 0.0;
	//---------------------------------------
	// 공중위협 이동 경로의 방향 벡터 계산
	double length = 0.0;
	length += pow(tar_x_f - tar_x_0, 2);
	length += pow(tar_y_f - tar_y_0, 2);
	length = sqrt(length);
	vecTarget[0] = (tar_x_f - tar_x_0) / length;
	vecTarget[1] = (tar_y_f - tar_y_0) / length;
	//---------------------------------------
	// Loop
	double distance = 0.0;

	for (time; time <= time_f; time += dt)
	{
		tar_x = tar_x_0 + vecTarget[0] * time * tar_vel;
		tar_y = tar_y_0 + vecTarget[1] * time * tar_vel;

		distance = CalculateDistance(tar_x, tar_y);

		if (distance <= missileRange)
		{
			checkAvailable = true;
			break;
		};

		if (tar_x == tar_x_f && tar_y == tar_y_f)
			break;

		// 미사일 탐지 영역에 들어온 시간
		detectTime = time;
	}


	return checkAvailable;
}

double AttackEvent::CalculateDistance(double tar_x, double tar_y)
{
	double distance;
	distance = sqrt(pow(tar_x - mis_x_0, 2) + pow(tar_y - mis_y_0, 2));

	return distance;
}
