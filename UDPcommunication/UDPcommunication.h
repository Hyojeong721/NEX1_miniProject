
#include "../HeadController/HeadControllerIICD.h"
class UDPcommunication {


	void init(int port, int dest_port);
	//template<typename T>
	void messageTobyte(char identification, HEAD_CONTROLLER_STATUS data);
	void messageTobyte(char identification, COMM_STATUS data);
	void messageTobyte(char identification, CONTROLLER_STATUS data);
	void messageTobyte(char identification, MissileInfo data);
	void messageTobyte(char identification, TargetInfo data);
	void messageTobyte(char identification, State data);
	void messageTobyte(char identification, CheckSum data);
	void messageTobyte(char identification, AttackEventMessge data);
	void messageTobyte(char identification, AttackInfo data);

	void recv_();
	void recv_thread();


public:


	~UDPcommunication();
	UDPcommunication(int port, int dest_port);
	UDPcommunication(int port, int dest_port, int dest_port2);
	//template<typename T>



	//template<typename T>
	void send_(char identification, HEAD_CONTROLLER_STATUS data, int dest_num = 0);
	void send_(char identification, COMM_STATUS data, int dest_num);
	void send_(char identification, CONTROLLER_STATUS data, int dest_num);
	void send_(char identification, MissileInfo data, int dest_num);
	void send_(char identification, TargetInfo data, int dest_num);
	void send_(char identification, State data, int dest_num);
	void send_(char identification, CheckSum data, int dest_num);
	void send_(char identification, AttackEventMessge data, int dest_num);
	void send_(char identification, AttackInfo data, int dest_num);

	//template<typename T>
	void get_data(char identification, HEAD_CONTROLLER_STATUS& data, int struct_size, int from = 2);
	void get_data(char identification, COMM_STATUS& data, int struct_size, int from = 2);
	void get_data(char identification, CONTROLLER_STATUS& data, int struct_size, int from = 2);
	void get_data(char identification, MissileInfo& data, int struct_size, int from = 2);
	void get_data(char identification, TargetInfo& data, int struct_size, int from = 2);
	void get_data(char identification, State& data, int struct_size, int from = 2);
	void get_data(char identification, CheckSum& data, int struct_size, int from = 2);
	void get_data(char identification, AttackEventMessge& data, int struct_size, int from = 2);
	void get_data(char identification, AttackInfo& data, int struct_size, int from = 2);


};