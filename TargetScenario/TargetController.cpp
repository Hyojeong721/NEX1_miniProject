#include "TargetController.h"

void TargetController::RecieveScenario() {
	TargetInfo targetInfo;
	udpCommunication.get_data('5', targetInfo, sizeof(TargetInfo));
	targetModel.SetTargetInformations(targetInfo);
}

void TargetController::RecieveCommand() {
	HEAD_CONTROLLER_STATUS status;
	udpCommunication.get_data('1', status, sizeof(HEAD_CONTROLLER_STATUS));
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

void TargetController::SendTargetPosition(double time) {
	TargetInfo info = targetModel.OutTargetPosition(3.0);
	udpCommunication.send_('5', info, sizeof(TargetInfo));
}

void TargetController::Run() {
	double time = 0;
	double addTime = 0.5;

	while (true) {
		RecieveCommand();
		HEAD_CONTROLLER_STATUS status = targetModel.GetControlStatus();
		if (status == HEAD_CONTROLLER_STATUS::END) {
			continue;
		}
		else if (status == HEAD_CONTROLLER_STATUS::READY) {
			RecieveScenario();
		}
		else if (status == HEAD_CONTROLLER_STATUS::RUN) {
			SendTargetPosition(time);
			time += addTime;
		}
		else {
			continue;
		}
		Sleep(1000)
	}
}