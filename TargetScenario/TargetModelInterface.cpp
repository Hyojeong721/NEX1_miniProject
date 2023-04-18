#include "TargetModelInterface.h"

void TargetModel::SetTargetInformations(TargetInfo targetInfo[2]) {
	init = targetInfo[0];
	goal = targetInfo[1];
}

void TargetModel::SetControllerStatus(HEAD_CONTROLLER_STATUS status) {
	controllerStatus = status;
}

TargetInfo TargetModel::UpdatePosition(double time) {
	// 1. �ӵ� ��ȯ
	velocity *= 340;	// Mach -> m/s

	// 2. ���� ���
	vector[0] = //goal._x - init._x;
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

TargetInfo TargetModel::OutTargetPosition(double time) {
	return UpdatePosition(time);
}