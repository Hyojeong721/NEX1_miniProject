#include "MissileModel.h"

void MissileModel::SetMissileInformations(MissileInfo missileInfo[2]) {
	init = missileInfo[0];
	goal = missileInfo[1];
}

void MissileModel::SetAttackInfo(AttackInfo msg) {
	attackEventMessage = msg;
}

void MissileModel::SetControllerStatus(HEAD_CONTROLLER_STATUS status) {
	controllerStatus = status;
}


//void MissileModel::InitializationMissile(double init_x, double init_y, double goal_x, double goal_y, double vel)
//{
//	init._x = init_x;
//	init._y = init_y;
//	goal._x = goal_x;
//	goal._y = goal_y;
//	velocity = vel;
//}

MissileInfo MissileModel::UpdatePosition(double time)
{
	// 1. �ӵ� ��ȯ
	velocity *= 340;	// Mach -> m/s

	// 2. ���� ���
	vector[0] = goal._x - init._x;
	vector[1] = goal._y - init._y;

	double length = sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
	vector[0] /= length;
	vector[1] /= length;

	// �̵� �Ÿ� ���
	double distance = time * velocity;
	double del_x = vector[0] * distance;
	double del_y = vector[1] * distance;

	// ���� ��ġ ���
	nowPosition._x = init._x + del_x;
	nowPosition._y = init._y + del_y;

	return nowPosition;
}

MissileInfo MissileModel::OutMissilePosition(double time)
{
	if (time < attackEventMessage.launchTime)
		return { init._x, init._y }; // �߻��������� �ʱ� ��ġ�� ������
	else
		return UpdatePosition(time - attackEventMessage.launchTime);
}

HEAD_CONTROLLER_STATUS MissileModel::GetControllerStatus() {
	return controllerStatus;
}


void MissileModel::StopSimulator()
{
	// ���� �ʿ�
	exit(0);
}
