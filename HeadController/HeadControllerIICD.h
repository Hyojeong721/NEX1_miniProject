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
	char kind;				// ������ ����
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
	double tick{0.0};			   //��������� ���� �ð�
};

struct attackEventMessge
{
	bool isSuccess{ false };
};