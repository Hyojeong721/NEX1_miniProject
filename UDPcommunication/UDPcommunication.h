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



	template<typename T>
	void send_(char identification, T data, int dest_num = 0);
	template<typename T>
	void get_data(char identification, T& data, int struct_size);

};