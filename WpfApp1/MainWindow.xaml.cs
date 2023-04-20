using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using CPPWAPPRER;

namespace WpfApp1
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public static class Wrapper
    {
        public static CHeadControllerWrapper simulationCtrl = new CHeadControllerWrapper();
        public static bool[] isExcute = new bool[] { false, false, false, false, false,false,false,false };
    }

    public partial class MainWindow : Window
    {
        
        public MainWindow()
        {
            InitializeComponent();
            StateDisplay.Text = "상태";
            Wrapper.simulationCtrl.MyEvent += new CHeadControllerWrapper.MyEventHandler(doAction);
            Wrapper.simulationCtrl.excuteSim();
        }

        public void doAction(string message)
        {
            // 다른 스레드에서 UI 스레드로 작업 요청
            Dispatcher.Invoke(DispatcherPriority.Normal, new Action(
            delegate
            {
                // 사용할 메서드 및 동작을 여기 기입
                int status = Wrapper.simulationCtrl.getSimulatorStatus();
                if (status == 0)
                {
                    StateDisplay.Text = "운용 준비 상태";

                    if(Wrapper.simulationCtrl.getCheckMissileComm() && Wrapper.isExcute[0] == false)
                    {
                        EventLogBox.Text += "유도탄 모의기 통신 완료";
                        EventLogBox.Text += "\n";
                        Wrapper.isExcute[0] = true;
                    }

                    if (Wrapper.simulationCtrl.getCheckTargetComm() && Wrapper.isExcute[1] == false)
                    {
                        EventLogBox.Text += "위협 모의기 통신 완료";
                        EventLogBox.Text += "\n";
                        Wrapper.isExcute[1] = true;
                    }

                    if (Wrapper.simulationCtrl.getAttackAvable() && Wrapper.isExcute[4] == false)
                    {
                        EventLogBox.Text += "요격 가능";
                        EventLogBox.Text += "\n";
                        Wrapper.isExcute[4] = true;
                    }
                }
                else if (status == 1)
                {

                    double scale = 1.0 / (100 * 1000 / 350);

                    StateDisplay.Text = "운용중";

                    // 현재 타켓 위치 GUI
                    double tx = 0.0;
                    double ty = 0.0;

                    double TPosx = 0.0;
                    double TPosy = 0.0;
                    unsafe
                    {
                    
                        Wrapper.simulationCtrl.getTargetPosition(&tx, &ty);
                        Wrapper.simulationCtrl.getTargetPosition(&TPosx, &TPosy);
                    }

                    //if (Double.IsNaN(tx) == false && Double.IsNaN(ty) == false)
                    //{

                    //string strtx = tx.ToString();
                    //string strty = ty.ToString();

                    //Target_Outputbox_X.Text = strtx;
                    //Target_Outputbox_Y.Text = strty;

                    //tx = tx * scale;
                    //ty = ty * scale;


                    //ty = 620 - ty;

                    //currentTarget.Margin = new System.Windows.Thickness { Left = tx, Top = ty, Right = 0, Bottom = 0 };
                    //}
                    // 현재 유도탄 위치 GUI
                    double mx = 0.0;
                    double my = 0.0;
                    double cmy = 0.0;

                    double MPosx = 0.0;
                    double MPosy = 0.0;

                    unsafe
                    {
                        Wrapper.simulationCtrl.getMisslePosition(&mx, &my);
                        Wrapper.simulationCtrl.getMisslePosition(&MPosx, &MPosy);
                    }

                    if (Math.Abs(MPosx - TPosx) > 5.0 && Math.Abs(MPosy - TPosy) > 5.0)
                    {
                        string strtx = tx.ToString();
                        string strty = ty.ToString();

                        Target_Outputbox_X.Text = strtx;
                        Target_Outputbox_Y.Text = strty;

                        tx = tx * scale;
                        ty = ty * scale;


                        ty = 620 - ty;

                        currentTarget.Margin = new System.Windows.Thickness { Left = tx, Top = ty, Right = 0, Bottom = 0 };

                        string strmx = mx.ToString();
                        string strmy = my.ToString();

                        Missile_Outputbox_X.Text = strmx;
                        Missile_Outputbox_Y.Text = strmy;
                        // 유도탄 초기 설정값으로 위치 이동

                        mx = mx * scale;
                        my = my * scale;

                        cmy = 620 - my;
                        currentMissile.Margin = new System.Windows.Thickness { Left = mx, Top = cmy, Right = 0, Bottom = 0 };

                        //mx = mx - 160;
                        //my = 475 - my;

                        if (Double.IsNaN(TPosx) == false && Double.IsNaN(TPosy) == false && Double.IsNaN(MPosx) == false && Double.IsNaN(MPosy) == false)
                        {
                            double distance = (TPosx - MPosx) * (TPosx - MPosx) + (TPosy - MPosy) * (TPosy - MPosy);

                            if (Math.Sqrt(distance) <= 50000.0 && Wrapper.isExcute[3] == false)
                            {
                                EventLogBox.Text += "위협 모의기 탐지";
                                EventLogBox.Text += "\n";
                                Wrapper.isExcute[3] = true;
                            }

                            if (Math.Sqrt(distance) <= 500.0 && Wrapper.isExcute[7] == false)
                            {
                                Wrapper.simulationCtrl.setStatus(2);
                                Wrapper.isExcute[7] = true;
                            }
                        }
                    }
                    //MissileCanvas.Margin = new System.Windows.Thickness { Left = mx, Top = my, Right = 0, Bottom = 0 }

                }
                else if (status == 2)
                {
                    StateDisplay.Text = "요격확인";
                    if (Wrapper.isExcute[5] == false)
                    {
                        EventLogBox.Text += "요격 성공";
                        EventLogBox.Text += "\n";
                        Wrapper.isExcute[5] = true;
                    }
                }
                else if (status == 3)
                {
                    if ( Wrapper.isExcute[2] == false)
                    {
                        if(Wrapper.simulationCtrl.getAttackAvable())
                        {
                            EventLogBox.Text += "요격 성공";
                            EventLogBox.Text += "\n";
                        }
                        else
                        {
                            EventLogBox.Text += "요격 불가";
                            EventLogBox.Text += "\n";
                        }
                        Wrapper.isExcute[2] = true;
                    }
                    StateDisplay.Text = "운용종료";
                }
            }));
        }

        private void TargetSet_Click(object sender, RoutedEventArgs e)
        {

            Window TargetScenario = new TargetScenario();

            TargetScenario.Owner = Application.Current.MainWindow; // 메인화면 중앙에 팝업창 띄우기
            TargetScenario.WindowStartupLocation = WindowStartupLocation.CenterOwner;
            TargetScenario.ShowDialog();

            if (Wrapper.simulationCtrl.getTargetStatus() == true)
            {

                double scale = 1.0 / (100 * 1000 / 350);

                EventLogBox.Text += "위협기 시나리오 설정 완료";
                EventLogBox.Text += "\n";
                // 메인화면에 공중위협 설정값 띄우기
                double sx = 0.0;
                double sy = 0.0;
                double ex = 0.0;
                double ey = 0.0;
                int kind = 0;
                double speed = 0.0;
                string strKind = "";
                unsafe
                {
                    Wrapper.simulationCtrl.getTargetScenario(&sx, &sy, &ex, &ey, &kind, &speed);
                }


                string strSX = sx.ToString();
                string strSY = sy.ToString();
                string strEX = ex.ToString();
                string strEY = ey.ToString();
                
                if(kind == 1)
                {
                    strKind = "Aircraft";
                }
                else
                {
                    strKind = "Missile";
                }

                string strSpeed = speed.ToString();
                T_StartPointData_X.Text = strSX;
                T_StartPointData_Y.Text = strSY;
                T_FinalPointData_X.Text = strEX;
                T_FinalPointData_Y.Text = strEY;
                VelocityData.Text = strSpeed;
                TargetTypeData.Text = strKind;

                Target_Outputbox_X.Text = strSX;
                Target_Outputbox_Y.Text = strSY;

                sx = (sx) * scale;
                ex = (ex) * scale;

                sy = (sy) * scale;
                ey = (ey) * scale;

                sy = (620 - sy);
                ey = (620 - ey);
                currentTarget.Margin = new System.Windows.Thickness { Left = sx, Top = sy, Right = 0, Bottom = 0 };

                // 공중위협 초기 설정값으로 위치 이동
                targetStartPoint.Margin = new System.Windows.Thickness { Left = sx, Top = sy, Right = 0, Bottom = 0 };
                targetFinalPoint.Margin = new System.Windows.Thickness { Left = ex, Top = ey, Right = 0, Bottom = 0 };
                targetLine.X1 = sx + 20;
                targetLine.Y1 = sy + 30;
                targetLine.X2 = ex + 10;
                targetLine.Y2 = ey + 30;

            }
        }


        private void MissileSet_Click(object sender, RoutedEventArgs e)
        {
            Window MissileScenario = new MissileScenario();

            MissileScenario.Owner = Application.Current.MainWindow; // 메인화면 중앙에 팝업창 띄우기
            MissileScenario.WindowStartupLocation = WindowStartupLocation.CenterOwner;
            
            MissileScenario.ShowDialog();
            
            if (Wrapper.simulationCtrl.getMissleStatus()==true)
            {
                double scale = 1.0 / (100 * 1000 / 350);
                EventLogBox.Text += "유도탄 시나리오 설정 완료";
                EventLogBox.Text += "\n";
                //메인화면에 유도탄 시나리오 설정 값 띄우기
                double x = 0.0;
                double y = 0.0;
                double cy = 0.0;

                unsafe
                {
                    Wrapper.simulationCtrl.getMissleScenario(&x, &y);
                }

                string strX = x.ToString();
                string strY = y.ToString();

                Missile_Outputbox_X.Text = strX;
                Missile_Outputbox_Y.Text = strY;

                M_StartPointData_X.Text = strX;
                M_StartPointData_Y.Text = strY;

                x = (x) * scale;
                y = (y) * scale;

                cy = (620 - y);
            
                currentMissile.Margin = new System.Windows.Thickness { Left = x, Top = cy, Right = 0, Bottom = 0 };

                // 유도탄 초기 설정값으로 위치 이동
                x = (x-160);
                y = (475-y);

                MissileCanvas.Margin = new System.Windows.Thickness { Left = x, Top = y, Right = 0, Bottom = 0 };
                
            }
        }
        
        private void startBtn_Click(object sender, RoutedEventArgs e)
        {
            EventLogBox.Text += "시뮬레이션 시작";
            EventLogBox.Text += "\n";
            Wrapper.simulationCtrl.startSimulator();
        }

        private void StopBtn_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("모의 종료");
            EventLogBox.Text += "대공유도탄 모의 시스템 중지";

            Wrapper.simulationCtrl.stopSimulator();
        }
    }
}
