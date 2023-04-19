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
        public static bool[] isExcute = new bool[] { false, false, false, false, false };
    }

    public partial class MainWindow : Window
    {
        
        public MainWindow()
        {
            InitializeComponent();
            
            StateDisplay.Text = "상태";
            Wrapper.simulationCtrl.MyEvent += new CHeadControllerWrapper.MyEventHandler(doAction);
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
                }
                else if (status == 1)
                {
                    StateDisplay.Text = "운용중 상태";

                    if (Wrapper.simulationCtrl.getCheckDetect() && Wrapper.isExcute[3] == false)
                    {
                        EventLogBox.Text += "위협 모의기 탐지";
                        EventLogBox.Text += "\n";
                        Wrapper.isExcute[3] = true;
                    }
                    // 현재 타켓 위치 GUI
                    double tx = 0.0;
                    double ty = 0.0;
                    unsafe
                    {
                        Wrapper.simulationCtrl.getTargetPosition(&tx, &ty);
                    }
                    ty = 620 - ty;
                    currentTarget.Margin = new System.Windows.Thickness { Left = tx, Top = ty, Right = 0, Bottom = 0 };
                    // 현재 유도탄 위치 GUI
                  
                    double mx = 0.0;
                    double my = 0.0;

                    unsafe
                    {
                        Wrapper.simulationCtrl.getMissleScenario(&mx, &my);
                    }
                    // 유도탄 초기 설정값으로 위치 이동
                    mx = mx - 160;
                    my = 475 - my;

                    MissileCanvas.Margin = new System.Windows.Thickness { Left = mx, Top = my, Right = 0, Bottom = 0 };
                }
                else if (status == 2)
                {
                    StateDisplay.Text = "요격확인 상태";
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
                            EventLogBox.Text += "요격 실패";
                            EventLogBox.Text += "\n";
                        }
                        Wrapper.isExcute[2] = true;
                    }
                    StateDisplay.Text = "운용종료 상태";
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

                sy = 620 - sy;
                ey = 620 - ey;
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
                EventLogBox.Text += "유도탄 시나리오 설정 완료";
                EventLogBox.Text += "\n";
                //메인화면에 유도탄 시나리오 설정 값 띄우기
                double x = 0.0;
                double y = 0.0;
                
                unsafe
                {
                    Wrapper.simulationCtrl.getMissleScenario(&x, &y);
                }
                string strX = x.ToString();
                string strY = y.ToString();

                M_StartPointData_X.Text = strX;
                M_StartPointData_Y.Text = strY;
                // 유도탄 초기 설정값으로 위치 이동
                x = x-160;
                y = 475-y;

                MissileCanvas.Margin = new System.Windows.Thickness { Left = x, Top = y, Right = 0, Bottom = 0 };
                
            }
        }
        
        
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }


        private void getPosition(object sender, MouseButtonEventArgs e)
        {
            Point pos = e.GetPosition((IInputElement)sender);

            int positionX = (int)pos.X;
            int positionY = (int)pos.Y;

            string strX = positionX.ToString();
            string strY = positionY.ToString();

            outputboxX.Text = strX;
            outputboxY.Text = strY;

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
            EventLogBox.Text += "모의 종료";
            Window.GetWindow(this).Close();

            //Thickness marginThickness = MissleCanvas.Margin;
            //MissleCanvas.Margin = new Thickness(300);
            //유도탄 위치 바꿀때 쓰면 됩니다. (a,b) 이동시 x -> x+a , y -> y-b
            //MissileCanvas.Margin = new System.Windows.Thickness { Left = 20, Bottom = 150 };
        }


        private void stopBtn_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("모의 종료");
            EventLogBox.Text += "모의 종료";
            Wrapper.simulationCtrl.stopSimulator();
        }
    }
}
