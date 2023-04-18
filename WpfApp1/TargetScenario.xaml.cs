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
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// TargetScenario.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class TargetScenario : Window
    {
        public TargetScenario()
        {
            InitializeComponent();
        }

        private void Cancle_Button_Click(object sender, RoutedEventArgs e)
        {
            Window.GetWindow(this).Close();
        }

        private void Set_Button_Click(object sender, RoutedEventArgs e)
        {
            double targetSx = Double.Parse(TargetStartPoint_X_Set.Text);
            double targetSy = Double.Parse(TargetStartPoint_Y_Set.Text);
            double targetEx = Double.Parse(TargetFinalPoint_X_Set.Text);
            double targetEy = Double.Parse(TargetFinalPoint_Y_Set.Text);
            double targetVel = Double.Parse(TargetVel.Text);
            int kind = 0;

            if(AirCraftRadioBtn.IsChecked == true)
            {
                kind = 1;
            }
            else if(MissleRadioBtn.IsChecked == true)
            {
                kind = 2;
            }

            Wrapper.simulationCtrl.setTargetScenario(targetSx, targetSy, targetEx, targetEy, (sbyte)kind, targetVel);
            MessageBox.Show("타겟 시나리오 설정 완료");
            Window.GetWindow(this).Close();
        }
    }
}
