﻿// UDPcommunication.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "framework.h"
#include "UDPcommunication.h"

#include <WinSock2.h>
#include<thread>
#include<queue>
// TODO: 라이브러리 함수의 예제입니다.
void fnUDPcommunication()
{
}


using namespace std;

#pragma comment(lib, "ws2_32.lib")


#define PACKET_LENGTH    1024
class UDPcommunication : public IUDPcommunication{

	SOCKET hSocket;
	SOCKADDR_IN tDestAddr[2];
	SOCKADDR_IN rcv_DestAddr;
	char recv_Packet[PACKET_LENGTH] = {};
	char send_Packet[PACKET_LENGTH] = {};



	queue<char*>buffer[10];

	int iDestLength[2];

	void init(int port, int dest_port) {
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);

		// <<< Create Socket >>>
		// PF_INET : IPv4 protocol family
		// SOCK_DGRAM : UDP 프로토콜 전송 방식
		// IPPROTO_UDP : 실제로 사용할 프로토콜 통신 방식 결정(UDP)
		// 마찬가지로 IPPROTO_HOPOPTS 값(0)을 설정하면 TCP인지 UDP인지 자동으로 잡힌다.
		hSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

		// <<< bind 준비 >>>
		SOCKADDR_IN tAddr = {};
		tAddr.sin_family = AF_INET;
		tAddr.sin_port = htons(port);
		tAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		// <<< bind >>>
		bind(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));

		tDestAddr[0] = {};
		iDestLength[0] = sizeof(tDestAddr[0]);

		tDestAddr[0].sin_family = AF_INET;
		tDestAddr[0].sin_port = htons(dest_port);
		tDestAddr[0].sin_addr.s_addr = inet_addr("127.0.0.1");


	}
	template<typename T>
	void messageTobyte(char identification, T data) {
		string str = typeid(data).name();
		send_Packet[0] = identification;
		memcpy(send_Packet + 1, &data, sizeof(data));
		/*if (str == "char") {
			send_Packet[1] = data;

		}
		else if (str == "double") {


		}
		else if (str == "bool") {

		}
		else if (str=="int") {

		}*/
	}
	void recv_() {


		memset(recv_Packet, 0, sizeof(recv_Packet));
		int rcv_length = sizeof(rcv_DestAddr);
		recvfrom(hSocket, recv_Packet, sizeof(recv_Packet), 0, (SOCKADDR*)&rcv_DestAddr, &rcv_length);

		if (recv_Packet[0] == '1') {
			buffer[1].push(recv_Packet);
		}
		else if (recv_Packet[0] == '2') {
			buffer[2].push(recv_Packet);
		}
		else if (recv_Packet[0] == '3') {
			buffer[3].push(recv_Packet);
		}
		else if (recv_Packet[0] == '4') {
			buffer[4].push(recv_Packet);
		}
		else if (recv_Packet[0] == '5') {
			buffer[5].push(recv_Packet);
		}
		else if (recv_Packet[0] == '6') {
			buffer[6].push(recv_Packet);
		}
		else if (recv_Packet[0] == '7') {
			buffer[7].push(recv_Packet);
		}
		else if (recv_Packet[0] == '8') {
			buffer[8].push(recv_Packet);
		}

		cout << recv_Packet << endl;



	}
	void recv_thread() {


		vector<std::thread>threads;

		for (int i = 0; i < 7; ++i) {
			threads.emplace_back(std::thread(&UDPcommunication::recv_, this));
		}

		for (auto& thread : threads)
			thread.detach();

	}


public:


	~UDPcommunication() {
		closesocket(hSocket);

		// 윈속 종료
		WSACleanup();
	}
	UDPcommunication(int port, int dest_port) {
		init(port, dest_port);
		recv_thread();
	}
	UDPcommunication(int port, int dest_port, int dest_port2) {
		init(port, dest_port);

		tDestAddr[1] = {};
		iDestLength[1] = sizeof(tDestAddr[1]);

		tDestAddr[1].sin_family = AF_INET;
		tDestAddr[1].sin_port = htons(dest_port2);
		tDestAddr[1].sin_addr.s_addr = inet_addr("127.0.0.1");
		recv_thread();
	}
	//template<typename T>



	template<typename T>
	void send_(char identification, T data, int dest_num = 0) {

		memset(send_Packet, 0, PACKET_LENGTH);
		messageTobyte(identification, data);

		sendto(hSocket, send_Packet, strlen(send_Packet), 0, (SOCKADDR*)&tDestAddr[dest_num], iDestLength[dest_num]);

	}
	template<typename T>
	void get_data(char identification, T& data, int struct_size) {
		int idx = identification - '0';
		if (!buffer[idx].empty()) {

			memcpy(&data, buffer[idx].front() + 1, struct_size);
			buffer[idx].pop();
		}
	}

};
