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
    }

    public partial class MainWindow : Window
    {
        
        public MainWindow()
        {
            InitializeComponent();
            
            //StateDisplay.Text = "잉";
            //Wrapper.simulationCtrl.MyEvent += new CHeadControllerWrapper.MyEventHandler(doAction);
        }

        //public void doAction(string message)
        //{
        //    // 다른 스레드에서 UI 스레드로 작업 요청
        //    Dispatcher.Invoke(DispatcherPriority.Normal, new Action(
        //    delegate
        //    {
        //        // 사용할 메서드 및 동작을 여기 기입
        //        int status = Wrapper.simulationCtrl.getSimulatorStatus();
        //        if (status == 0)
        //        {
        //            StateDisplay.Text = "운용 준비 상태";
        //        }
        //        else if (status == 1)
        //        {
        //            StateDisplay.Text = "운용중 상태";
        //        }
        //        else if (status == 2)
        //        {
        //            StateDisplay.Text = "요격확인 상태";
        //        }
        //        else if (status == 3)
        //        {
        //            StateDisplay.Text = "운용종료 상태";
        //        }
        //    }));
        //}

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

        private void stopBtn_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("모의 종료");
            EventLogBox.Text += "모의 종료";
            Window.GetWindow(this).Close();
        }
    }
}
