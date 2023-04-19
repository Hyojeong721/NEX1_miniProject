
#include "../HeadController/HeadControllerIICD.h"
class UDPcommunication {

	
	void init(int port, int dest_port);
	template<typename T>
	void messageTobyte(char identification, T data);
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
	void send_(char identification, checkSum data, int dest_num);
	void send_(char identification, attackEventMessge data, int dest_num);
	void send_(char identification, AttackInfo data, int dest_num);

	//template<typename T>
	void get_data(char identification, HEAD_CONTROLLER_STATUS& data, int struct_size);
	void get_data(char identification, COMM_STATUS& data, int struct_size);
	void get_data(char identification, CONTROLLER_STATUS& data, int struct_size);
	void get_data(char identification, MissileInfo& data, int struct_size);
	void get_data(char identification, TargetInfo& data, int struct_size);
	void get_data(char identification, State& data, int struct_size);
	void get_data(char identification, checkSum& data, int struct_size);
	void get_data(char identification, attackEventMessge& data, int struct_size);
	void get_data(char identification, AttackInfo& data, int struct_size);


};