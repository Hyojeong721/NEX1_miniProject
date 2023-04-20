#include"pch.h"
#include"AttackEvent.h"
#include<fstream>
#include<string>
AttackInfo AttackEvent::CalculateAttackEvent(MissileInfo missileinfo, TargetInfo targetInfo)
{
	//------------------------------------------------
	// 	1. �ó����� �Ķ���� ����(����ź, �������� - �ӵ�, �ʱ���ġ, ��ǥ��ġ)
	SettingParameters(missileinfo, targetInfo);
	//------------------------------------------------
	//  2. ���ϰ� �ʱ�ȭ
	AttackInfo attackinfo;
	attackinfo = InitializationAttackEvent();
	//------------------------------------------------
	//  3. Ž�� ���� ���� Ȯ��
	attackinfo.checkAttackAvailable = CheckAttackAvailable();
	if (attackinfo.checkAttackAvailable == false)
	{
		return attackinfo;				// Ž���� �Ұ��� �ϸ� ���� -> attackinfo�� false ����
	}
		
	//------------------------------------------------
	// 4. ��� ��ġ, �ð� ���
	//---------------------------------
	// 4.1 ����ź�� �ð�/�Ÿ� �迭 ����
	const int noArray = 301;			// �ð�/�Ÿ� ������ ��� ����

	double arrMisTime[noArray];			// ����ź ����ð�
	double arrMisRange[noArray];		// ����ź ����ð��� ���� ��� �Ÿ�

	arrMisTime[0] = 0.0;
	arrMisRange[0] = 0.0;

	for (int i = 1; i < noArray; i++)
	{
		arrMisRange[i] = arrMisRange[i - 1] + 50000 / ((double)noArray - 1);	// 50km�� noArray���� ��ŭ ����
		arrMisTime[i] = arrMisRange[i] / 340;									// �� arrMisRange ��ҿ� �ش�Ǵ� �Ÿ��� �����ϴµ� �ҿ�Ǵ� �ð�
	}
	//---------------------------------
	// 4.2 ���������� ��� �������� Ȯ��
	bool endflag = false;	// �������� ��� ���� ����

	double attackTime = 0.0;
	double distance = 0.0;
	double distanceAttack = 0.0;
	double attackPoint_x = 0.0;
	double attackPoint_y = 0.0;

	//std::ofstream file_; file_.open("C:\\Users\\User\\Desktop\\�ǽ�\\SW����\\miniPJT\\output2.txt");
	////if (file_.is_open()) {
	////}
	////file_.close();
	for (int i = 0; i < noArray - 1; i++) {
		attackTime = detectTime + arrMisTime[i]; // (�����ݽð�) = (Ž���ð�) + (����ź ����ð�)

		tar_x = tar_x_0 + vecTarget[0] * attackTime * tar_vel;	// �����ݽð��� ���������� ��ġ ���
		tar_y = tar_y_0 + vecTarget[1] * attackTime * tar_vel;



		distance = CalculateDistance(tar_x, tar_y);		// "����������"���� "����ź �ʱ���ġ" ���� �Ÿ� 
		
		for (int k = 0; k < noArray - 1; k++) {
			if ((attackTime - detectTime) > arrMisTime[k]) {		// "(��ݿ���ð�)-(Ž���ð�)" �� "����ź ����ð�" ���� Ŭ �� ����
				if (distance <= arrMisRange[k]) {
					distanceAttack = distance;						// (�������)�� (����ź �ʱ���ġ)���� �Ÿ�

					attackPoint_x = tar_x;		// (��� ����) == (�������� ���� ��ġ)
					attackPoint_y = tar_y;

					endflag = true;
					break;		// ��� ���� ������ ã�����Ƿ� �ߴ�
				}
			}
			else
				break;		// ����ź�� �����ؼ� ����� �� ���� ����
		}
		if (endflag)		// ��� ���� ������ ã�����Ƿ� �ߴ�
			break;
	}



	if (endflag == false) {	// ��� ���� ������ ã�� ���� ���
		{
			attackinfo.checkAttackAvailable = false;
			return attackinfo;				// Ž���� �Ұ��� �ϸ� ���� -> attackinfo�� false ����
		}
	}
	//---------------------------------
	// 4.3 ����ź �߻� �ð� ���
	attackinfo.launchTime = attackTime - detectTime;	// ����ź �߻�ð� = ��ݿ���ð� - (��������� ����ź�ʱ���ġ�Ÿ�/����ź �ӵ�)


	/*file_ << std::to_string(attackinfo.launchTime) << "\n";

	file_.close();*/
	//---------------------------------
	// 4.4 ����ź ��� ��ġ == ����ź ��ǥ ��ġ
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
	double time_f = 10000.0;	// ������ ū ��
	double time = 0.0;
	//---------------------------------------
	// �������� �̵� ����� ���� ���� ���
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

		// �̻��� Ž�� ������ ���� �ð�
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
