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
    /// MissileScenario.xaml에 대한 상호 작용 논리
    /// </summary>
    /// 

    public partial class MissileScenario : Window
    {
        public MissileScenario()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Window.GetWindow(this).Close();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            double targetSx = Double.Parse(MissileFinalPoint_X_Set.Text);
            double targetSy = Double.Parse(MissileFinalPoint_Y_Set.Text);
            Wrapper.simulationCtrl.setMissleScenario(targetSx, targetSy);
            MessageBox.Show("유도탄 시나리오 설정 완료");
            Window.GetWindow(this).Close();
        }
    }
}
