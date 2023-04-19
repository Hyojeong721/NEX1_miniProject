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
	CONTROLLER_STATUS status;
	udpCommunication.get_data('1', status, sizeof(CONTROLLER_STATUS));
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

void MissileController::SendMissilePosition() {
	MissileInfo info = missileModel.OutMissilePosition();
	udpCommunication.send_('3', info, sizeof(MissileInfo));
}

void MissileController::Run() {

	while (true) {
		RecieveCommand();
		CONTROLLER_STATUS state = missileModel.GetControllerStatus();
		if (state.status == HEAD_CONTROLLER_STATUS::END) {
			continue;
		}
		else if (state.status == HEAD_CONTROLLER_STATUS::READY) {
			RecieveScenario();
		}
		else if (state.status == HEAD_CONTROLLER_STATUS::RUN) {
			SendMissilePosition();
		}
		else {
			continue;
		}
		Sleep(1000);
	}
}