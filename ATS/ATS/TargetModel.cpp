#include "TargetModel.h"

void TargetModel::SetTargetInformations(TargetInfo targetInfo) {
	init = targetInfo;
}

void TargetModel::SetAttackInfo(AttackInfo msg) {
	attackEventMessage = msg;
}

void TargetModel::SetControllerStatus(HEAD_CONTROLLER_STATUS status) {
	controllerStatus = status;
}

State TargetModel::UpdatePosition(double time) {
	// 1. 속도 변환
	velocity *= 340;	// Mach -> m/s

	// 2. 벡터 계산
	vector[0] = init._ex - init._sx;	//goal._x - init._x;
	vector[1] = init._ey - init._sy;

	double length = sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
	vector[0] /= length;
	vector[1] /= length;

	// 이동 거리 계산
	double distance = time * velocity;
	double del_x = vector[0] * distance;
	double del_y = vector[1] * distance;

	// 현재 위치 계산
	nowPosition.position[0] = init._sx + del_x;
	nowPosition.position[1] = init._sy + del_y;

	return nowPosition;
}

HEAD_CONTROLLER_STATUS TargetModel::GetControlStatus() {
	return controllerStatus;
}

State TargetModel::OutTargetPosition(double time) {
	return UpdatePosition(time);
}

void TargetModel::StopSimulator() {

}