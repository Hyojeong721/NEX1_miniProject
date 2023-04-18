#pragma once

//1. 
enum class HEAD_CONTROLLER_STATUS : unsigned int
{
	READY = 0U,      //����غ����
	RUN,          //����� ����
	EVENT_CHECK,   //���Ȯ�� ����
	END            //������� ����
};

//2.
enum class COMM_STATUS : unsigned
{
	NS = 0U,    //�ƹ��͵� �ƴҶ�
	OK,         // ����
	NON         // ������
};


/// <summary>
/// ��� ���
/// </summary>

//3.
struct CommStruct
{
	char* data;
};

// ����ź �ó�����
//4.
struct MissileInfo {
	double _x, _y;          // �߻���
};

// ���� ������ �ó����� ���� 
//5.
struct TargetInfo {
	double _sx, _sy;      // �߻���
	double _ex, _ey;      // ź����
	char kind;            // ������ ����
	double speed;         // ������ �ӵ�
};

// ���� ��� ���� ����
//6.
struct State
{
	double position[2]{ 0, };      //      
};

// ��� Ȯ�� (��/����)
//7.
struct CheckSum
{
	COMM_STATUS status{ COMM_STATUS::NS };         // ��Ż���
	double tick{ 0.0 };            //��������� ���� �ð�
};

//8.
struct AttackEventMessge
{
	bool isSuccess{ false };      // ����  / ����
};