#pragma once
#include "ScenarioSetting.h"
#include "AttackEvent.h"

#include <vector>
#include <thread>
#include <memory.h>
#include <mutex>
#include "../UDPcommunication/UDPcommunication.h"

// 함수포인터(function pointer) 타입 정의
typedef void(*CALLBACK_FUNC)();


class HeadController
{
public:
    HeadController();      //통신 주기 설정

    void starSimulation();                     // 시뮬레이션 수행
    void stopSimulation();                     // 시뮬레이션 중지

    void setMissleScenario(double cord[2]);      // int _sx, int _sy
    void setTargetScenario(double cord[4], char kind, double speed);
    void setStatus(int status) { m_status = static_cast<HEAD_CONTROLLER_STATUS>(status); };
    inline int getHeadControlStatus() { return static_cast<int>(m_status); };

    inline ScenarioSetting getScenarioinfo() { return m_scen; };
    inline State getMisslePosition() { return m_missleState; };
    inline State getTargetPosition() { return m_targetState; };

    // 이벤트 스레드 관련 메서드
    void SetHandler(CALLBACK_FUNC cli_cb)
    {
        m_cbf = cli_cb;
    }
    void excuteSimTread();   // 시뮬레이션 스레드 수행

public:
    bool m_checkMissileComm{ false };
    bool m_checkTargetComm{ false };
    bool attackAvable{ false };
    bool checkDetect{ false };

    // 시나리오 설정 확인
    bool m_missileScenSet{ false };
    bool m_targetScenSet{ false };
    

private:
    void readData();      // 데이터 읽기
    void writeStatusData();      // 데이터 쓰기
    void update();         //상태에 따른 모의기 운영
    bool checkDetonation();   // 충돌 여부판단
private:
    AttackEvent attackevent;
    AttackInfo attackInfo;
    HEAD_CONTROLLER_STATUS m_status{ HEAD_CONTROLLER_STATUS::READY };
    ScenarioSetting m_scen;
    State m_missleState;
    State m_targetState;
    UDPcommunication m_udpComm=UDPcommunication(8080,8081,8082);
    double m_tickTime{ 0.0 };

    // callback Pointer
    CALLBACK_FUNC m_cbf{ nullptr };

    bool UIstopInput{ false };
    //thread info
    bool isExcute{ false };
    bool UICtrlInput{ false };
    std::vector<std::thread> threads;
    void* mutex_;
};
