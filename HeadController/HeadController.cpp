// HeadController.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "HeadController.h"

/// STL 라이브러리
#include <cmath>
#include <vector>
#include <thread>
#include <memory.h>
#include <mutex>

// TODO: 라이브러리 함수의 예제입니다.
void fnHeadController()
{
}

HeadController::HeadController()
{
    std::mutex tmp;
    mutex_ = &tmp;
    m_udpComm = new UDPcommunication(8080, 8081, 8082);
}

// 스타트 버튼 누르면 호출 호출 시 스레드 시작
void HeadController::starSimulation()
{
    if (!isExcute)
    {
        isExcute = true;
    }

    //// 시나리오 설정 상태 확인
    UICtrlInput = true;
}

void HeadController::stopSimulation()
{
    UIstopInput = true;
    UICtrlInput = false;
}

void HeadController::setMissleScenario(double cord[2])
{
    m_scen.SetMissile(cord);
    m_udpComm->send_('4', m_scen.GetMissile(), 0); // 미사일 시나리오
    m_missileScenSet = true;
}

void HeadController::setTargetScenario(double cord[4], char kind, double speed)
{
    m_scen.SetTarget(cord, kind, speed);
    m_udpComm->send_('5', m_scen.GetTarget(), 1); // 타켓 정보 보내기
    m_targetScenSet = true;
}

void HeadController::readData()
{
    //객체가 소멸시에 unlock 되는 특성을 가지고 있습니다.
    std::lock_guard<std::mutex> lg{ *(std::mutex*)mutex_ };

    // 통신으로 데이터 받기 구현
}

void HeadController::writeStatusData()
{
    //객체가 소멸시에 unlock 되는 특성을 가지고 있습니다.
    //std::lock_guard<std::mutex> lg{ *(std::mutex *)mutex_ };

    // 통신으로 데이터 보내기 구현
    CONTROLLER_STATUS trans;
    trans = { m_status,m_tickTime };
    m_udpComm->send_('3', trans, 0);      // 운용통제기 상태 보내기
    m_udpComm->send_('3', trans, 1);      // 운용통제기 상태 보내기
}

void HeadController::update()
{
    if (UIstopInput == true)
    {
        m_status = HEAD_CONTROLLER_STATUS::END;   // UI에서 종료 명령이 들어오면 STOP한다.
    }
    if (m_status == HEAD_CONTROLLER_STATUS::READY)
    {
        // 시나리오 배포 및 배포 확인(통신으로)
        if (m_checkMissileComm == false)
        {
            CheckSum missileCheck;
            m_udpComm->get_data('7', missileCheck, sizeof(missileCheck),0);


            if (missileCheck.status == COMM_STATUS::OK) m_checkMissileComm = true; // 로그창에서 대공 유도탄 모의기 연결 확인 추가 (wrapper에도 받는 기능 추가)
        }
        if (m_checkTargetComm == false)
        {
            CheckSum targetCheck;
            m_udpComm->get_data('7', targetCheck, sizeof(targetCheck),1);



            if (targetCheck.status == COMM_STATUS::OK) m_checkTargetComm = true; // 로그창에서 대공 유도탄 모의기 연결 확인 추가 (wrapper에도 받는 기능 추가)
        }


        if (m_checkMissileComm == true && m_checkTargetComm == true)
        {
            // 통신확인후 모의기에 운용통제기 정보 전송
            writeStatusData();

            //유도탄 에 시나리오 설정로그 띄우기 ///////////////////////////////////////////////////////

            // 위협기에  시나리오 로그 띄우기///////////////////////////////////////////////////////////////////

            if (m_missileScenSet == true && m_targetScenSet == true && attackAvable == false) {
                // 3. 요격 상태정보 계산후 보내기
                attackInfo = attackevent.CalculateAttackEvent(m_scen.GetMissile(), m_scen.GetTarget());

                if (attackevent.CalculateAttackEvent(m_scen.GetMissile(), m_scen.GetTarget()).checkAttackAvailable == false) // 요격계산 or 탐지 실패한 경우
                {
                    m_status = HEAD_CONTROLLER_STATUS::END;   // 요격이 안되면 운용상태 종료로 // 절차 //종료상태일때, "요격 불가" 로그에 띄위기
                }
                else
                {
                    attackAvable = true;      // 절차 //종료상태일때, "요격 가능" 로그에 띄위기
                    m_udpComm->send_('9', attackInfo, 0);
                }
            }
        }

        if (UICtrlInput)
        {
            m_status = HEAD_CONTROLLER_STATUS::RUN;
        }
    }
    else if (m_status == HEAD_CONTROLLER_STATUS::RUN)
    {
        // 운용중 수도코드
        /*
        * 0. 타이머 업데이트
        * 1. 유도탄 정보 받기
        * 2. 위협기 모의정보 받기
        * 3. 충돌여부 판단
        */

        ///  0. 타이머 업데이트 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        m_tickTime += 0.5;

        // // 0, 상태보내기 (공통)/////////////////////////////////////////////////////////////////////////////////////////////
        writeStatusData();

        // 1. 유도탄 정보 받기 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        m_udpComm->get_data('6', m_missleState, sizeof(m_missleState),0);

        //  2. 위협기 모의정보 받기 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        m_udpComm->get_data('6', m_targetState, sizeof(m_targetState),1);


        //  3. 충돌여부 판단 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (checkDetonation() == true)
        {
            m_status = HEAD_CONTROLLER_STATUS::EVENT_CHECK;
            // "공중위협 요격 성공" 로그에 표시
        }
    }
    else if (m_status == HEAD_CONTROLLER_STATUS::EVENT_CHECK)
    {
        writeStatusData();
    }
    else if (m_status == HEAD_CONTROLLER_STATUS::END)
    {
        writeStatusData();
    }

    // 인터페이스에서 GUI화면 업데이트 이벤트 호출
    if (m_cbf)
    {
        m_cbf();
    }
}

void HeadController::excuteSimTread()
{
    std::thread t1([&]() {
        while (m_status != HEAD_CONTROLLER_STATUS::END)
        {
            update();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        });

    t1.detach();
}

bool HeadController::checkDetonation()
{
    bool res = false;
    double distance = sqrt(pow(m_missleState.position[0], 2) - pow(m_targetState.position[0], 2) + pow(m_missleState.position[1], 2) - pow(m_targetState.position[1], 2));
    if (distance <= 50.0)
    {
        res = true;
    }
    else;
    if (distance <= 50000.0)
    {
        checkDetect = true;
        // "공중위협 탐지" 로그에 출려
    }
    else;
    return res;
}