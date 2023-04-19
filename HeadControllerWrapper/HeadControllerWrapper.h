#pragma once
using namespace System;
using namespace System::Runtime::InteropServices;

#include <HeadController.h>

namespace CPPWAPPRER {
	public ref class CHeadControllerWrapper
	{
	public:
		CHeadControllerWrapper() 
		{
			m_headCtrl = new HeadController();

			// 이벤트 쓰레드 관련
			CbHandler^ fp = gcnew CbHandler(this, &CHeadControllerWrapper::onRecv);
			gch = GCHandle::Alloc(fp);
			IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);

			// SetHandler 는 mylib.h 의 C++ 에서 제공하는 함수이다.
			// 핸들러를 설정한다.
			m_headCtrl->SetHandler(static_cast<CALLBACK_FUNC>(ip.ToPointer()));
		};
		~CHeadControllerWrapper() {};
		void startSimulator();
		void setMissleScenario(double _x, double _y);
		void setTargetScenario(double _sx, double _sy, double _ex, double _ey, int kind, double speed);
		void getMisslePosition(double& _x, double& _y);
		void getTargetPosition(double& _x, double& _y);
		
		inline int getSimulatorStatus() { return m_headCtrl->getHeadControlStatus(); };
		inline bool getMissleStatus() { return isMissleSet; };
		inline bool getTargetStatus() { return isTargetSet; };
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	public:
		// 이벤트 델리게이트 선언
		delegate void MyEventHandler(String^ message);
		delegate void CbHandler();
		// 이벤트 선언
		event MyEventHandler^ MyEvent;

		// C++ 에 핸들러로 등록되어있어서,
		// C++ 에서 뭔가 발생하면 이 메소드가 자동으로 수행됨
		void onRecv()
		{
			MyEvent("Hello");
		}
	private:
		GCHandle gch;
		HeadController* m_headCtrl;
		bool isMissleSet{ false };
		bool isTargetSet{ false };
	};
}
