#pragma once

//1. 
enum class HEAD_CONTROLLER_STATUS : unsigned int
{
	READY = 0U,      //����غ����
	RUN,          //����� ����
	EVENT_CHECK,   //���Ȯ�� ����
	END,            //������� ����
	Trash
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

// ����ź �ó�����
//3.
struct MissileInfo {
	double _x, _y;          // �߻���
};

// ���� ������ �ó����� ���� 
//4.
struct TargetInfo {
	double _sx, _sy;      // �߻���
	double _ex, _ey;      // ź����
	char kind;            // ������ ����
	double speed;         // ������ �ӵ�
};

// ���� ��� ���� ����
//5.
struct State
{
	double position[2]{ 0, };      //      
};

// ��� Ȯ�� (��/����)
//6.
struct CheckSum
{
	COMM_STATUS status{ COMM_STATUS::NS };         // ��Ż���
	double tick{ 0.0 };            //��������� ���� �ð�
};

//7.
struct AttackEventMessge
{
	bool isSuccess{ false };      // ����  / ����
};

// ��� �̺�Ʈ ����
// 8.
struct AttackInfo {
	bool checkAttackAvailable;   // ��� ���� ����
	double launchTime;         // ����ź �߻� �ð�
	double attackPoint_x;      // ��� ���� x ��ǥ
	double attackPoint_y;      // ��� ���� y ��ǥ
};