#pragma once

enum class HEAD_CONTROLLER_STATUS : unsigned int
{
	READY = 0U,		//����غ����
	RUN,		    //����� ����
	EVENT_CHECK,	//���Ȯ�� ����
	END				//������� ����
};

enum class COMM_STATUS : unsigned
{
	NS = 0U,    //�ƹ��͵� �ƴҶ�
	OK,			// ����
	NON			// ������
};

struct CONTROLLER_STATUS
{
	HEAD_CONTROLLER_STATUS status{ HEAD_CONTROLLER_STATUS::READY };
	double tickTime{0.0};
};
/// <summary>
/// ��� ���
/// </summary>
 
struct CommStruct
{
	char* data;
};

// ����ź �ó�����
struct MissileInfo {
	double _x, _y;		    // �߻���
};

// ���� ������ �ó����� ���� 
struct TargetInfo {
	double _sx, _sy;		// �߻���
	double _ex, _ey;		// ź����
	int kind;				// ������ ����
	double speed;			// ������ �ӵ�
};


// ���� ��� ���� ����
struct State
{	
	double position[2]{0,};		//		
};

// ��� Ȯ�� (��/����)
struct checkSum
{
	COMM_STATUS status{COMM_STATUS::NS};		   // ��Ż���
};

struct attackEventMessge
{
	bool isSuccess{ false };		// ����  / ����
};

// ��� �̺�Ʈ ����
struct AttackInfo {
	bool checkAttackAvailable;	// ��� ���� ����
	double launchTime;			// ����ź �߻� �ð�
	double attackPoint_x;		// ��� ���� x ��ǥ
	double attackPoint_y;		// ��� ���� y ��ǥ
};