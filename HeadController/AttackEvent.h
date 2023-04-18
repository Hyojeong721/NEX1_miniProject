#pragma once
#include "HeadControllerIICD.h"
#include <iostream>
#include < cmath >

class AttackEvent
{
public:
	AttackEvent() {};
	~AttackEvent() {};
	AttackInfo CalculateAttackEvent(MissileInfo missileinfo, TargetInfo targetInfo);
private:
	void SettingParameters(MissileInfo missileinfo, TargetInfo targetInfo);
	AttackInfo InitializationAttackEvent();
	bool CheckAttackAvailable();
	//
	double CalculateDistance(double tar_x, double tar_y);
	//-------------------------------------
	double mis_x_0;		 // �̻��� x �ʱ� ��ġ
	double mis_y_0;		 // �̻��� y �ʱ� ��ġ
	double mis_vel;		 // �̻��� �ӵ� = dedault
	double missileRange; // �̻��� ��Ÿ�

	double tar_x_0;	// �������� x �ʱ� ��ġ
	double tar_y_0;	// �������� y �ʱ� ��ġ
	double tar_x_f;	// �������� x ��ǥ ��ġ
	double tar_y_f;	// �������� y ��ǥ ��ġ
	double tar_vel;	// �������� �ӵ� (mach)
	//--------------------------------------
	double vecTarget[2];	// �������� �̵� ����� ���� ���� (x,y)
	double tar_x, tar_y;	// �������� ���� ��ġ

	double detectTime;		// ���������� ����ź ��ݰ��� ������ ��� �� �ð�
	//--------------------------------------

};
