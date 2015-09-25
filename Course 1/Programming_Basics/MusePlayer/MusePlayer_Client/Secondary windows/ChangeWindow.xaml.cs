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
using Microsoft.Win32;
using System.Text.RegularExpressions;

namespace MusicPlayer_ClientSide{
    public partial class AddWindow : Window {
        public SongStyle songStyle;

        public AddWindow(){
            InitializeComponent();
            this.songStyle = SongStyle.None;
            SetTheme();
            SetLanguage();
        }

        private void RadioButton_Checked(object sender, RoutedEventArgs e){
            var checkedRadioButton = sender as RadioButton;
            
            this.songStyle = Song.TryParse(checkedRadioButton.Content.ToString());
        }

        private void FindPath_Click(object sender, RoutedEventArgs e){
            OpenFileDialog dlg = new OpenFileDialog();
            Nullable<bool> result = dlg.ShowDialog();
            
            if (result == true){
                string filename = dlg.FileName;

                AuthorTB.Text = Regex.Match(filename, @"[\s\S]* -").ToString().Remove(filename.IndexOf(" -")).Remove(0, filename.LastIndexOf("\\") + 1);
                TitleTB.Text = Regex.Match(filename, @"- [\s\S]*").ToString().Remove(Regex.Match(filename, @"- [\s\S]*").ToString().IndexOf(".")).Remove(0, 2);
                PathTB.Text = filename;
            }
        }
        private void OkButton_Click(object sender, RoutedEventArgs e){
            MediaPlayer checker = new MediaPlayer();

            checker.Open(new Uri(PathTB.Text, UriKind.RelativeOrAbsolute));
            if (PathTB.Text == "" || AuthorTB.Text == "" || TitleTB.Text == ""){
                MessageBox.Show("Author or Title or Path is Empty");
                return; }
            else this.Close(); 
        }
        private void CButton_Click(object sender, RoutedEventArgs e){
            this.Close();
        }

        private void Border_MouseDown(object sender, MouseButtonEventArgs e) {
            DragMove();
        }
        private void SetGeneralElementsColor(SolidColorBrush MainWindowColor, SolidColorBrush ButtBackColor, SolidColorBrush ButtForgColor, SolidColorBrush TextColor){                    
            AddWindowXaml.Background = MainWindowColor;
            OkButt.Background = ButtBackColor; 
            OkButt.Foreground = ButtForgColor; 
            AuthorTB.BorderBrush = TextColor;
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
            switch(App.Language){
                case "Russian": OkButt.Content="Хорошо"; CButt.Content="Отмена"; FindButt.Content="Найти"; PathLabl.Content="Путь"; AuthorLabel.Content="Исполнитель"; TitleLabel.Content="Название"; break;
                case "English": OkButt.Content="Ok"; CButt.Content="Cancel"; FindButt.Content="Find"; PathLabl.Content="Path"; AuthorLabel.Content="Author"; TitleLabel.Content="Title"; break;
            }
        }
    }
}