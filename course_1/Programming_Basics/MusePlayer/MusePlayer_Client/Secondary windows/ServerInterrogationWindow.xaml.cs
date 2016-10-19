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

namespace MusicPlayer_ClientSide {
    public partial class ServerInterrogationWindow : Window{
        public ServerInterrogationWindow(){
            InitializeComponent();
            SongListBox.SelectedIndex = 0;
            SetTheme();
            SetLanguage();
        }

        private void GetSongButt_Click(object sender, RoutedEventArgs e){
            MusicPlayer_ClientSide.HttpClient.DownloadSongRequest(App.ServerIp ,SongListBox.SelectedItem as String);
        }
        private void Border_MouseDown(object sender, RoutedEventArgs e){
            DragMove();
        }
        private void ExitButt_Click(object sender, RoutedEventArgs e){
            this.Close();
        }
        private void SetGeneralElementsColor(SolidColorBrush MainWindowColor, SolidColorBrush ButtBackColor, SolidColorBrush ButtForgColor, SolidColorBrush TextColor){                    
            ServerWindowXAML.Background = MainWindowColor;
            GetSongButt.Background = ButtBackColor; 
            GetSongButt.Foreground = ButtForgColor; 
            SongListBox.BorderBrush = TextColor;
        }
        private void SetTheme(){
            switch (App.Theme){
                case Theme.Dark: {
                    SolidColorBrush LikeBlue = new SolidColorBrush(Color.FromArgb(255, 019, 128, 203));
                    SolidColorBrush LikeBlack = new SolidColorBrush(Color.FromArgb(255, 018, 019, 019));
                    SolidColorBrush LikeWhiteBlack = new SolidColorBrush(Color.FromArgb(255, 041, 039, 039));
                    
                    SetGeneralElementsColor(LikeWhiteBlack, LikeBlack, LikeBlue, LikeBlue); 
                    break; }
                case Theme.White: {
                    SolidColorBrush LikeWhite = new SolidColorBrush(Color.FromArgb(255, 197, 197, 197));
                    SolidColorBrush LikeBlack = new SolidColorBrush(Color.FromArgb(255, 018, 019, 019));
                    
                    SetGeneralElementsColor(LikeWhite, LikeBlack, LikeWhite, LikeBlack);
                    break; }
                case Theme.Green: {
                    SolidColorBrush LikeDarkGreen = new SolidColorBrush(Color.FromArgb(255, 004, 027, 005));
                    SolidColorBrush LikeGreen = new SolidColorBrush(Color.FromArgb(255, 018, 077, 029));
                    SolidColorBrush LikeGrey = new SolidColorBrush(Color.FromArgb(255, 155, 167, 176));
                    
                    SetGeneralElementsColor(LikeGreen, LikeGrey, LikeDarkGreen, Brushes.YellowGreen); 
                    break; }
            }
        }
        private void SetLanguage(){
            switch (App.Language){
                case "English": GetSongButt.Content = "Get Song"; ExitButt.Content = "Exit"; Header.Content = "Music at server"; break;
                case "Russian": GetSongButt.Content = "Скачать"; ExitButt.Content = "Выйти"; Header.Content = "Музыка на сервере"; break;
            }
        }
    }
}
