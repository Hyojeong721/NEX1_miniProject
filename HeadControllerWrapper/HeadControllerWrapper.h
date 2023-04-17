#pragma once
using namespace System;
#include<HeadController.h>

namespace CPPWAPPRER {
	public ref class CHeadControllerWrapper
	{
	public:
		CHeadControllerWrapper() 
		{
			m_headCtrl = new HeadController();
		};
		~CHeadControllerWrapper() {};
		void setMissleScenario(double _x, double _y);
		void setTargetScenario(double _sx, double _sy, double _ex, double _ey, char kind, double speed);
		void getMisslePosition(double& _x, double& _y);
		void getTargetPosition(double& _x, double& _y);
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.

	private:
		HeadController* m_headCtrl;
	};
}
