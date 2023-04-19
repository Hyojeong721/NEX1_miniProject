// UDPcommunication.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "UDPcommunication.h"

// TODO: 라이브러리 함수의 예제입니다.
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include<thread>
#include<queue>
#include<string>
using namespace std;

#pragma comment(lib, "ws2_32.lib")


#define PACKET_LENGTH    1024

SOCKET hSocket;
SOCKADDR_IN tDestAddr[2];
SOCKADDR_IN rcv_DestAddr;
char recv_Packet[PACKET_LENGTH] = {};
char send_Packet[PACKET_LENGTH] = {};



//queue<char*>buffer[10];

queue<char*>buffer_each[3][12];

int iDestLength[2];

void fnUDPcommunication()
{
}

void UDPcommunication::init(int port, int dest_port) {
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

	//int idx;


}


void UDPcommunication::messageTobyte(char identification, HEAD_CONTROLLER_STATUS data) {
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
void UDPcommunication::messageTobyte(char identification, COMM_STATUS data) {
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
void UDPcommunication::messageTobyte(char identification, CONTROLLER_STATUS data) {
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
void UDPcommunication::messageTobyte(char identification, MissileInfo data) {
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
void UDPcommunication::messageTobyte(char identification, TargetInfo data) {
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
void UDPcommunication::messageTobyte(char identification, State data) {
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

void UDPcommunication::messageTobyte(char identification, CheckSum data) {
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
void UDPcommunication::messageTobyte(char identification, AttackEventMessge data) {
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
void UDPcommunication::messageTobyte(char identification, AttackInfo data) {
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

void UDPcommunication::recv_() {
	int idx = -1;

	memset(recv_Packet, 0, sizeof(recv_Packet));
	int rcv_length = sizeof(rcv_DestAddr);
	recvfrom(hSocket, recv_Packet, sizeof(recv_Packet), 0, (SOCKADDR*)&rcv_DestAddr, &rcv_length);

	if (rcv_DestAddr.sin_port == htons(8080)) {
		idx = 2;
	}
	else if (rcv_DestAddr.sin_port == htons(8081)) {
		idx = 0;
	}
	else if (rcv_DestAddr.sin_port == htons(8082)) {
		idx = 1;
	}



	if (recv_Packet[0] == '1') {
		buffer_each[idx][1].push(recv_Packet);
	}
	else if (recv_Packet[0] == '2') {
		buffer_each[idx][2].push(recv_Packet);
	}
	else if (recv_Packet[0] == '3') {
		buffer_each[idx][3].push(recv_Packet);
	}
	else if (recv_Packet[0] == '4') {
		buffer_each[idx][4].push(recv_Packet);
	}
	else if (recv_Packet[0] == '5') {
		buffer_each[idx][5].push(recv_Packet);
	}
	else if (recv_Packet[0] == '6') {
		buffer_each[idx][6].push(recv_Packet);
	}
	else if (recv_Packet[0] == '7') {
		buffer_each[idx][7].push(recv_Packet);
	}
	else if (recv_Packet[0] == '8') {
		buffer_each[idx][8].push(recv_Packet);
	}
	else if (recv_Packet[0] == '9') {
		buffer_each[idx][9].push(recv_Packet);
	}





}
void UDPcommunication::recv_thread() {


	vector<std::thread>threads;

	for (int i = 0; i < 7; ++i) {
		threads.emplace_back(std::thread(&UDPcommunication::recv_, this));
	}

	for (auto& thread : threads)
		thread.detach();

}


UDPcommunication::~UDPcommunication() {
	closesocket(hSocket);

	// 윈속 종료
	WSACleanup();
}
UDPcommunication::UDPcommunication(int port, int dest_port) {
	init(port, dest_port);
	recv_thread();
}
UDPcommunication::UDPcommunication(int port, int dest_port, int dest_port2) {
	init(port, dest_port);

	tDestAddr[1] = {};
	iDestLength[1] = sizeof(tDestAddr[1]);

	tDestAddr[1].sin_family = AF_INET;
	tDestAddr[1].sin_port = htons(dest_port2);
	tDestAddr[1].sin_addr.s_addr = inet_addr("127.0.0.1");
	recv_thread();
}


//template<typename T>

void UDPcommunication::send_(char identification, HEAD_CONTROLLER_STATUS data, int dest_num) {

	memset(send_Packet, 0, PACKET_LENGTH);
	messageTobyte(identification, data);

	sendto(hSocket, send_Packet, strlen(send_Packet), 0, (SOCKADDR*)&tDestAddr[dest_num], iDestLength[dest_num]);

}
void UDPcommunication::send_(char identification, COMM_STATUS data, int dest_num) {

	memset(send_Packet, 0, PACKET_LENGTH);
	messageTobyte(identification, data);

	sendto(hSocket, send_Packet, strlen(send_Packet), 0, (SOCKADDR*)&tDestAddr[dest_num], iDestLength[dest_num]);

}
void UDPcommunication::send_(char identification, CONTROLLER_STATUS data, int dest_num) {

	memset(send_Packet, 0, PACKET_LENGTH);
	messageTobyte(identification, data);

	sendto(hSocket, send_Packet, strlen(send_Packet), 0, (SOCKADDR*)&tDestAddr[dest_num], iDestLength[dest_num]);

}
void UDPcommunication::send_(char identification, MissileInfo data, int dest_num) {

	memset(send_Packet, 0, PACKET_LENGTH);
	messageTobyte(identification, data);

	sendto(hSocket, send_Packet, strlen(send_Packet), 0, (SOCKADDR*)&tDestAddr[dest_num], iDestLength[dest_num]);

}
void UDPcommunication::send_(char identification, TargetInfo data, int dest_num) {

	memset(send_Packet, 0, PACKET_LENGTH);
	messageTobyte(identification, data);

	sendto(hSocket, send_Packet, strlen(send_Packet), 0, (SOCKADDR*)&tDestAddr[dest_num], iDestLength[dest_num]);

}
void UDPcommunication::send_(char identification, State data, int dest_num) {

	memset(send_Packet, 0, PACKET_LENGTH);
	messageTobyte(identification, data);

	sendto(hSocket, send_Packet, strlen(send_Packet), 0, (SOCKADDR*)&tDestAddr[dest_num], iDestLength[dest_num]);

}
void UDPcommunication::send_(char identification, CheckSum data, int dest_num) {

	memset(send_Packet, 0, PACKET_LENGTH);
	messageTobyte(identification, data);

	sendto(hSocket, send_Packet, strlen(send_Packet), 0, (SOCKADDR*)&tDestAddr[dest_num], iDestLength[dest_num]);

}
void UDPcommunication::send_(char identification, AttackEventMessge data, int dest_num) {

	memset(send_Packet, 0, PACKET_LENGTH);
	messageTobyte(identification, data);

	sendto(hSocket, send_Packet, strlen(send_Packet), 0, (SOCKADDR*)&tDestAddr[dest_num], iDestLength[dest_num]);

}
void UDPcommunication::send_(char identification, AttackInfo data, int dest_num) {

	memset(send_Packet, 0, PACKET_LENGTH);
	messageTobyte(identification, data);

	sendto(hSocket, send_Packet, strlen(send_Packet), 0, (SOCKADDR*)&tDestAddr[dest_num], iDestLength[dest_num]);

}


//template<typename T>
void UDPcommunication::get_data(char identification, HEAD_CONTROLLER_STATUS& data, int struct_size, int from) {
	int idx = identification - '0';
	if (!buffer_each[from][idx].empty()) {

		memcpy(&data, buffer_each[from][idx].front() + 1, struct_size);
		buffer_each[from][idx].pop();
	}
}
void UDPcommunication::get_data(char identification, COMM_STATUS& data, int struct_size, int from) {
	int idx = identification - '0';
	if (!buffer_each[from][idx].empty()) {

		memcpy(&data, buffer_each[from][idx].front() + 1, struct_size);
		buffer_each[from][idx].pop();
	}
}

void UDPcommunication::get_data(char identification, CONTROLLER_STATUS& data, int struct_size, int from) {
	int idx = identification - '0';
	if (!buffer_each[from][idx].empty()) {

		memcpy(&data, buffer_each[from][idx].front() + 1, struct_size);
		buffer_each[from][idx].pop();
	}
}
void UDPcommunication::get_data(char identification, MissileInfo& data, int struct_size, int from) {
	int idx = identification - '0';
	if (!buffer_each[from][idx].empty()) {

		memcpy(&data, buffer_each[from][idx].front() + 1, struct_size);
		buffer_each[from][idx].pop();
	}
}
void UDPcommunication::get_data(char identification, TargetInfo& data, int struct_size, int from) {
	int idx = identification - '0';
	if (!buffer_each[from][idx].empty()) {

		memcpy(&data, buffer_each[from][idx].front() + 1, struct_size);
		buffer_each[from][idx].pop();
	}
}
void UDPcommunication::get_data(char identification, State& data, int struct_size, int from) {
	int idx = identification - '0';
	if (!buffer_each[from][idx].empty()) {

		memcpy(&data, buffer_each[from][idx].front() + 1, struct_size);
		buffer_each[from][idx].pop();
	}
}
void UDPcommunication::get_data(char identification, CheckSum& data, int struct_size, int from) {
	int idx = identification - '0';
	if (!buffer_each[from][idx].empty()) {

		memcpy(&data, buffer_each[from][idx].front() + 1, struct_size);
		buffer_each[from][idx].pop();
	}
}
void UDPcommunication::get_data(char identification, AttackEventMessge& data, int struct_size, int from) {
	int idx = identification - '0';
	if (!buffer_each[from][idx].empty()) {

		memcpy(&data, buffer_each[from][idx].front() + 1, struct_size);
		buffer_each[from][idx].pop();
	}
}
void UDPcommunication::get_data(char identification, AttackInfo& data, int struct_size, int from) {
	int idx = identification - '0';
	if (!buffer_each[from][idx].empty()) {

		memcpy(&data, buffer_each[from][idx].front() + 1, struct_size);
		buffer_each[from][idx].pop();
	}
}
