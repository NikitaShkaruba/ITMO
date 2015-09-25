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
using System.IO;

namespace MusicPlayer_ClientSide {
    public partial class SettingsWindow : Window {
        public SettingsWindow() {
            InitializeComponent();
            this.PathTB.Text = App.FolderPath;
            this.ServerIpLB.Text = App.ServerIp;
            this.SetLanguage();
            this.SetTheme();
            
            ThemeSettingsLB.Items.Add("Dark");
            ThemeSettingsLB.Items.Add("White");
            ThemeSettingsLB.Items.Add("Green");

            for (int i = 0; i < ThemeSettingsLB.Items.Count; i++)
                if (App.Theme.ToString() == ThemeSettingsLB.Items[i].ToString())
                    ThemeSettingsLB.SelectedIndex = i;
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e) {
            try {
                using (StreamWriter writer = new StreamWriter("Settings.xml")) {
                    writer.WriteLine(@"<?xml version=""1.0"" encoding=""utf-8""?>");
                    writer.WriteLine(@"<Settings>");
                    writer.WriteLine(string.Format("\t<FolderPath>{0}</FolderPath>", PathTB.Text));
                    writer.WriteLine(string.Format("\t<ServerIp>{0}</ServerIp>", ServerIpLB.Text));
                    writer.WriteLine(string.Format("\t<ColorTheme>{0}</ColorTheme>", ThemeSettingsLB.Items[ThemeSettingsLB.SelectedIndex].ToString()));
                    writer.WriteLine(string.Format("\t<Language>{0}</Language>", LanguageCB.Text.ToString()));
                    writer.WriteLine(@"</Settings>");
                }
            }
            catch (Exception ex) {
                MessageBox.Show(ex.Message);
                // Backups baby!
                using (StreamWriter writer = new StreamWriter("Settings.xml")) {
                    writer.WriteLine(@"<?xml version=""1.0"" encoding=""utf-8""?>");
                    writer.WriteLine(@"<Settings>");
                    writer.WriteLine(@"\t<FolderPath>C:\Users\Nick\Music</FolderPath>");
                    writer.WriteLine(@"\t<ServerIp>127.0.0.1</ServerIp>");
                    writer.WriteLine(@"\t<ColorTheme>Dark</ColorTheme>");
                    writer.WriteLine(@"\t<Language>English</Language>");
                    writer.WriteLine(@"</Settings>");
                }
            }
            this.Close();
        }

        private void Border_MouseDown(object sender, MouseButtonEventArgs e) {
            DragMove();
        }
        private void SetGeneralElementsColor(SolidColorBrush MainWindowColor, SolidColorBrush ButtBackColor, SolidColorBrush ButtForgColor, SolidColorBrush TextColor) { 
            SettingsWindowXaml.Background = MainWindowColor;
            CloseButt.Background = ButtBackColor; 
            CloseButt.Foreground = ButtForgColor; 
            PathTB.BorderBrush = TextColor;
        }
        private void SetTheme() {
            switch (App.Theme) {
                case Theme.Dark: {
                    SolidColorBrush LikeBlue = new SolidColorBrush(Color.FromArgb(255, 019, 128, 203));
                    SolidColorBrush LikeBlack = new SolidColorBrush(Color.FromArgb(255, 018, 019, 019));
                    SolidColorBrush LikeWhiteBlack = new SolidColorBrush(Color.FromArgb(255, 041, 039, 039));
                    
                    SetGeneralElementsColor(LikeWhiteBlack, LikeBlack, LikeBlue, LikeBlue); 
                    break; 
                }
                case Theme.White: {
                    SolidColorBrush LikeWhite = new SolidColorBrush(Color.FromArgb(255, 197, 197, 197));
                    SolidColorBrush LikeBlack = new SolidColorBrush(Color.FromArgb(255, 018, 019, 019));
                    
                    SetGeneralElementsColor(LikeWhite, LikeBlack, LikeWhite, LikeBlack);
                    break; 
                }
                case Theme.Green: {
                    SolidColorBrush LikeDarkGreen = new SolidColorBrush(Color.FromArgb(255, 004, 027, 005));
                    SolidColorBrush LikeGreen = new SolidColorBrush(Color.FromArgb(255, 018, 077, 029));
                    SolidColorBrush LikeGrey = new SolidColorBrush(Color.FromArgb(255, 155, 167, 176));
                    
                    SetGeneralElementsColor(LikeGreen, LikeGrey, LikeDarkGreen, Brushes.YellowGreen); 
                    break; 
                }
            }
        }
        private void SetLanguage() {
            switch(App.Language) {
                case "English": LanguageCB.SelectedIndex = 0; Header.Content="Settings"; PathLabel.Content="Path to a music folder"; ThemeLabel.Content="Theme"; LanguageLabel.Content="Language"; ServerIPLabel.Content="Server IP adress"; break;
                case "Russian":  LanguageCB.SelectedIndex = 1; Header.Content="Настройки"; PathLabel.Content="Путь к музыкальной директории"; ThemeLabel.Content="Тема"; LanguageLabel.Content="Язык"; ServerIPLabel.Content="IP адрес сервера"; break;
            }
        }
    }
}
