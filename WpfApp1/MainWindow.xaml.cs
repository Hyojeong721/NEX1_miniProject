﻿using System;
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

    }
}
