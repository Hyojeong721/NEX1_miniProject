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

namespace WpfApp1
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
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

        }

        private void MissileSet_Click(object sender, RoutedEventArgs e)
        {
            Window MissileScenario = new MissileScenario();

            MissileScenario.Owner = Application.Current.MainWindow; // 메인화면 중앙에 팝업창 띄우기
            MissileScenario.WindowStartupLocation = WindowStartupLocation.CenterOwner;

            MissileScenario.ShowDialog();
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
