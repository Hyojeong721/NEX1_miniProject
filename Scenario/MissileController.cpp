#include "MissileController.h"

void MissileController::RecieveScenario() {
	MissileInfo missileInfoArray[2];
	for (int i = 0; i < 2; i++) {
		udpCommunication.get_data('4', missileInfoArray[i], sizeof(MissileInfo));
	}
	missileModel.SetMissileInformations(missileInfoArray);
}

void MissileController::RecieveCommand() {
	HEAD_CONTROLLER_STATUS status;
	udpCommunication.get_data('1', status, sizeof(HEAD_CONTROLLER_STATUS));
	missileModel.SetControllerStatus(status);
}

void MissileController::RecieveAttackEvent() {
	AttackEventMessge msg;
	udpCommunication.get_data('8', msg, sizeof(AttackEventMessge));
	
	if (msg.isSuccess == true) {
		missileModel.StopSimulator();
	}
}

void MissileController::SendMissilePosition() {
	MissileInfo info = missileModel.OutMissilePosition(3.0);
	udpCommunication.send_('1', info, sizeof(MissileInfo));
}