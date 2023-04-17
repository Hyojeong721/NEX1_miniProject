#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include<thread>
#include<vector>
#include<queue>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define PORT             7890
#define PACKET_LENGTH    1024
class UDPcommunication {
	SOCKET hSocket;
	SOCKADDR_IN tDestAddr[2];
	SOCKADDR_IN rcv_DestAddr;
	char recv_Packet[PACKET_LENGTH] = {};
	char send_Packet[PACKET_LENGTH] = {};
	//char recv_Packet2[PACKET_LENGTH] = {};
	int iDestLength[2];
	
	void init(int port, int dest_port);

	void messageTobyte();
	void byteTomessage();
public:
	~UDPcommunication();
	
	UDPcommunication(int port, int dest_port);	
	UDPcommunication(int port, int dest_port, int dest_port2);

	void recv_();
	void send_(int dest_num = 0);

	void recv_thread();
};