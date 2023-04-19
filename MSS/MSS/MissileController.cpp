#include "MissileController.h"

void MissileController::RecieveScenario() {
	MissileInfo missileInfoArray[2];
	AttackInfo msg;

	for (int i = 0; i < 2; i++) {
		udpCommunication.get_data('3', missileInfoArray[i], sizeof(MissileInfo));
	}

	missileModel.SetMissileInformations(missileInfoArray);

	udpCommunication.get_data('8', msg, sizeof(AttackInfo));
	missileModel.SetAttackInfo(msg);
}

void MissileController::RecieveCommand() {
	HEAD_CONTROLLER_STATUS status{ HEAD_CONTROLLER_STATUS::Trash };
	udpCommunication.get_data('1', status, sizeof(HEAD_CONTROLLER_STATUS));
	missileModel.SetControllerStatus(status);

	//if (status != HEAD_CONTROLLER_STATUS::Trash) {
	//	missileModel.SetControllerStatus(status);
	//}
}

void MissileController::RecieveAttackEvent() {
	AttackEventMessge msg;
	udpCommunication.get_data('7', msg, sizeof(AttackEventMessge));

	if (msg.isSuccess == true) {
		missileModel.StopSimulator();
	}
}

void MissileController::SendCommandState() {
	COMM_STATUS state = COMM_STATUS::OK;
	udpCommunication.send_('2', state, sizeof(COMM_STATUS));
}

void MissileController::SendMissilePosition(double time) {
	MissileInfo info = missileModel.OutMissilePosition(time);
	udpCommunication.send_('3', info, sizeof(MissileInfo));
}

void MissileController::Run() {
	double time = 0;
	double addTime = 0.5;

	while (true) {
		RecieveCommand();
		HEAD_CONTROLLER_STATUS status = missileModel.GetControllerStatus();
		if (status == HEAD_CONTROLLER_STATUS(3)) {
			continue;
		}
		else if (status == HEAD_CONTROLLER_STATUS(0)) {
			RecieveScenario();
		}
		else if (status == HEAD_CONTROLLER_STATUS(1)) {
			SendMissilePosition(time);
			time += addTime;
		}
		else {
			continue;
		}
		Sleep(1000);
	}
}