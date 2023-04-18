#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include<thread>
#include<vector>
#include<queue>
using namespace std;

#pragma comment(lib, "ws2_32.lib")


#define PACKET_LENGTH    1024
class UDPcommunication {

	SOCKET hSocket;
	SOCKADDR_IN tDestAddr[2];
	SOCKADDR_IN rcv_DestAddr;
	char recv_Packet[PACKET_LENGTH] = {};
	char send_Packet[PACKET_LENGTH] = {};



	queue<char*>buffer[10];

	int iDestLength[2];

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