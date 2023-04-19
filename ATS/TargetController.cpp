#include "TargetController.h"

void TargetController::RecieveScenario() {
	TargetInfo targetInfo;
	udpCommunication.get_data('5', targetInfo, sizeof(TargetInfo));
	targetModel.SetTargetInformations(targetInfo);
}

void TargetController::RecieveCommand() {
	CONTROLLER_STATUS status;
	udpCommunication.get_data('3', status, sizeof(CONTROLLER_STATUS));
	targetModel.SetControllerStatus(status);
}

void TargetController::RecieveAttackEvent() {
	AttackEventMessge msg;
	udpCommunication.get_data('8', msg, sizeof(AttackEventMessge));

	if (msg.isSuccess == true) {
		targetModel.StopSimulator();
	}
}

void TargetController::SendCommandState() {
	COMM_STATUS state = COMM_STATUS::OK;
	udpCommunication.send_('2', state, sizeof(COMM_STATUS));
}

void TargetController::SendTargetPosition() {
	State info = targetModel.OutTargetPosition();
	udpCommunication.send_('5', info, sizeof(State));
}

void TargetController::Run() {

	while (true) {
		RecieveCommand();
		CONTROLLER_STATUS state = targetModel.GetControlStatus();
		if (state.status == HEAD_CONTROLLER_STATUS::END) {
			continue;
		}
		else if (state.status == HEAD_CONTROLLER_STATUS::READY) {
			RecieveScenario();
		}
		else if (state.status == HEAD_CONTROLLER_STATUS::RUN) {
			SendTargetPosition();
		}
		else {
			continue;
		}
		Sleep(1000);
	}
}