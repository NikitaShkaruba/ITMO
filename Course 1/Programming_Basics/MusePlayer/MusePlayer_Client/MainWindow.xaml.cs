using System.Text.RegularExpressions;
using System.Collections.ObjectModel;
using System.Collections.Generic;
using System.Windows.Media;
using System.Diagnostics;
using Microsoft.Win32;
using System.Windows;
using System.Timers;
using System.Text;
using System.Linq;
using System.Xml;
using System.IO;
using System;

namespace MusicPlayer_ClientSide {
    public partial class MainWindow : Window {
        private ExtendedPlayer Player = new ExtendedPlayer();
        private ObservableCollection<Song> Library = new ObservableCollection<Song>();
       
        public MainWindow() {
            InitializeComponent();
            FrontSongList.ItemsSource = Library;
            SetPrimalSettings();
            RefreshLibrary();
        }

        private void PlayButt_Click(object sender, RoutedEventArgs e) {
            string PlayContent = null, StopContent = null;
     
            switch(App.Language) {
                case "English": StopContent = "Stop"; PlayContent = "Play"; break;
                case "Russian": StopContent = "Пауза"; PlayContent = "Играть"; break;
            }
            switch (Player.State) {
                case MediaState.Playing: {
                    Player.Pause();
                    PlayButt.Content = PlayContent;
                    break;
                }
                case MediaState.Stopped: {
                    Player.Play();
                    PlayButt.Content = StopContent;
                    break;
                }
            }
        }
        private void AddButt_Click(object sender, RoutedEventArgs e) {
            OpenFileDialog ChooseDialog = new OpenFileDialog();
            Nullable<bool> result = ChooseDialog.ShowDialog();
            if (result == true)
                Library.Add(new Song(ChooseDialog.FileName));
        }
        private void RemoveButt_Click(object sender, RoutedEventArgs e) {
            if (Library.Count > 0)
                Library.RemoveAt(FrontSongList.SelectedIndex);
        }
        private void ChangeButt_Click(object sender, RoutedEventArgs e) {
            AddWindow Window = new AddWindow();
            int index = FrontSongList.SelectedIndex;
            Window.AuthorTB.Text = Library[index].Author;
            Window.TitleTB.Text = Library[index].Title;
            Window.PathTB.Text = Library[index].Path;
            Window.Show();

            Window.Closing += (object sender2, System.ComponentModel.CancelEventArgs e2) => {
                Library[index] =  new Song(Window.AuthorTB.Text, Window.TitleTB.Text, Window.PathTB.Text);
            };
        }
        private void RefreshButt_Click(object sender, RoutedEventArgs e) {
            RefreshLibrary();
        }
        private void SettingsButt_Click(object sender, RoutedEventArgs e) {
            SettingsWindow setWindow = new SettingsWindow();
            setWindow.Show();
            setWindow.Closing += (object sender2, System.ComponentModel.CancelEventArgs e2) => {
                App.FolderPath = setWindow.PathTB.Text;
                SetTheme(setWindow.ThemeSettingsLB.Items[setWindow.ThemeSettingsLB.SelectedIndex].ToString());
                App.ServerIp = setWindow.ServerIpLB.Text;
                SetLanguage(setWindow.LanguageCB.Text);
            };
        }
        private void GetSongButt_Click(object sender, RoutedEventArgs e) {
            MusicPlayer_ClientSide.ServerInterrogationWindow servWindow = new MusicPlayer_ClientSide.ServerInterrogationWindow();
            servWindow.Show();
            servWindow.Closing += (object sender2, System.ComponentModel.CancelEventArgs e2) => { RefreshLibrary(); };
            foreach (Song sng in HttpClient.GetSongList()) {
                servWindow.SongListBox.Items.Add(sng.ToString());
            }
        }
        private void SendSongButt_Click(object sender, RoutedEventArgs e) {
            HttpClient.UploadSongRequest(App.ServerIp, Library[FrontSongList.SelectedIndex]);
        }
        private void ExitButt_Click(object sender, RoutedEventArgs e) {
            Application.Current.Shutdown();
        }

        private void KeyShortCuts(object sender, System.Windows.Input.KeyEventArgs e) {
            switch (e.Key.ToString()) {
                case "A": AddButt_Click(this, null); break;
                case "R": RefreshButt_Click(this, null); break;
                case "Escape": ExitButt_Click(this, null); break;
                case "Space": PlayButt_Click(this, null); break;
            }
        }
        private void Border_MouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            DragMove();
        }
        private void VolumeSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
            Player.Volume = VolumeSlider.Value / 10;
        }
        private void BotSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
            if (Player.ChangedByUserHands)
                Player.Position = TimeSpan.FromMilliseconds(Player.NaturalDuration.TimeSpan.TotalMilliseconds * BotSlider.Value * 0.1);
        }
        private void MusicListBox_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e) {
            if (FrontSongList.SelectedIndex <= 0) 
                FrontSongList.SelectedIndex = 0;
            Player.Open(new Uri(Library[FrontSongList.SelectedIndex].Path, UriKind.RelativeOrAbsolute));
            BotSlider.Value = 0;
            SongLengthLabel.Content = Player.NaturalDuration.TimeSpan.ToString(@"m\:ss");
            PlayButt.Content = "Pause";
            CurrentPositionLabel.Content = "0:00";
        }
        private void TimerTick(object sender, ElapsedEventArgs e) {
            // i am too bored to refactor this, mb another time
            Player.ChangedByUserHands = false;
            Dispatcher.Invoke(() =>{
                BotSlider.Value += Player.Step;
                CurrentPositionLabel.Content = Player.Position.ToString(@"m\:ss");
            });
            Player.ChangedByUserHands = true;
        }

        private void RefreshLibrary() {
            string FolderPath = App.FolderPath;
            string[] Files = Directory.GetFiles(FolderPath, "*.mp3" );

            for (int i = 0; i < Files.Length; i++) {
                string Author = Regex.Match(Files[i], @"[\s\S]* -").ToString().Remove(Files[i].IndexOf(" -")).Remove(0, Files[i].LastIndexOf("\\") + 1);
                string Title = Regex.Match(Files[i], @"- [\s\S]*").ToString().Remove(Regex.Match(Files[i], @"- [\s\S]*").ToString().IndexOf(".")).Remove(0, 2);
                string Path = Files[i];
                Song CreatedSong = new Song(Author, Title, Files[i]);
                    
                if (!(Library.Any(p => p.Author == CreatedSong.Author && p.Title == CreatedSong.Title)))
                    Library.Add(CreatedSong);
            }   
        }

        private void SetPrimalSettings() {
            using (StreamReader reader = new StreamReader("Settings.xml", Encoding.UTF8)) {
                XmlDocument SettingsDocument = new XmlDocument();
                SettingsDocument.LoadXml(reader.ReadToEnd());

                foreach (XmlNode Scobe in SettingsDocument.SelectNodes("Settings")) {
                    foreach (XmlNode Setting in Scobe.ChildNodes) {
                        switch (Setting.Name.ToLower()) {
                            case "folderpath": App.FolderPath = Setting.InnerText; break;
                            case "colortheme": SetTheme(Setting.InnerText); break;
                            case "serverip": App.ServerIp = Setting.InnerText; break;
                            case "language": SetLanguage(Setting.InnerText); break;
                            
                            default: throw new Exception("Parsing Settings File Exception");
                        }
                    }
                }
            }

            this.Player.timer.Elapsed += TimerTick;
            this.Player.MediaEnded += (object sender, EventArgs e) => { FrontSongList.SelectedIndex++; };
        }
        private void SetLanguage(string language) {
            // Good game, Nickitos.
            App.Language = language;
            switch(App.Language) {
                case "Russian": 
                    SomeTextAtBottom.Content = "Получи опрокидывание"; 
                    PlayButt.Content = "Играть";
                    AddButt.Content = "Добавить";
                    RemoveButt.Content = "Удалить";
                    ChangeButt.Content = "Изменить";
                    SendSongButt.Content = "Отправить";
                    GetSongButt.Content = "Скачать";
                    break;
                case "English":
                    SomeTextAtBottom.Content = "GetRqt"; 
                    PlayButt.Content = "Play";
                    AddButt.Content = "Add";
                    RemoveButt.Content = "Remove";
                    ChangeButt.Content = "Change";
                    SendSongButt.Content = "SendSong";
                    GetSongButt.Content = "Download";
                    break;

                default: throw new Exception("Trying to set not implemented language.");
            }
        }
        private void SetTheme(string ThemeName) {
            // Dirty, gonna fix this next time
            App.Theme = (Theme)Enum.Parse(typeof(Theme), ThemeName);

            switch (App.Theme) {
                case Theme.Dark: {
                    SolidColorBrush LikeBlue = new SolidColorBrush(Color.FromArgb(255, 019, 128, 203));
                    SolidColorBrush LikeBlack = new SolidColorBrush(Color.FromArgb(255, 018, 019, 019));
                    SolidColorBrush LikeWhiteBlack = new SolidColorBrush(Color.FromArgb(255, 041, 039, 039));
                    
                    SetBindedElementsColor(LikeWhiteBlack, LikeBlack, LikeBlue, LikeBlue); 
                    break; 
                }
                case Theme.White: {
                    SolidColorBrush LikeWhite = new SolidColorBrush(Color.FromArgb(255, 197, 197, 197));
                    SolidColorBrush LikeBlack = new SolidColorBrush(Color.FromArgb(255, 018, 019, 019));
                    
                    SetBindedElementsColor(LikeWhite, LikeBlack, LikeWhite, LikeBlack);
                    break; 
                }
                case Theme.Green: {
                    SolidColorBrush LikeDarkGreen = new SolidColorBrush(Color.FromArgb(255, 004, 027, 005));
                    SolidColorBrush LikeGreen = new SolidColorBrush(Color.FromArgb(255, 018, 077, 029));
                    SolidColorBrush LikeGrey = new SolidColorBrush(Color.FromArgb(255, 155, 167, 176));
                    
                    SetBindedElementsColor(LikeGreen, LikeGrey, LikeDarkGreen, Brushes.YellowGreen); 
                    break; 
                }
                default: throw new Exception("Can't set unimplemented theme.");
            }
        }
        private void SetBindedElementsColor(SolidColorBrush MainWindowColor, SolidColorBrush ButtBackColor, SolidColorBrush ButtForgColor, SolidColorBrush TextColor) {
            MainWindowXAML.Background = MainWindowColor;
            PlayButt.Background = ButtBackColor; 
            PlayButt.Foreground = ButtForgColor; 
            FrontSongList.BorderBrush = TextColor;
        }

        // Tests
        private void test_PlayButt_Click() {
            if (Player.State == MediaState.Playing)
                Player.Pause();

            PlayButt_Click(null, null);
            Debug.Assert(Player.State == MediaState.Playing);
                        
            PlayButt_Click(null, null);
            Debug.Assert(Player.State == MediaState.Stopped);
        }
        private void test_RemoveButt_Click() {
                int before = Library.Count;
                RemoveButt_Click(null, null);
                Debug.Assert(Library.Count == before - 1 || before == 0);
        }
        private void test_RefreshLibrary() {
            string[] Files = Directory.GetFiles(App.FolderPath, "*.mp3" );
            RefreshLibrary();
            Debug.Assert(Library.Count == Files.Count());
        }
        private void test_SetLanguage() {
            SetLanguage("Russian");
            Debug.Assert(PlayButt.Content == "Играть");

            SetLanguage("English");
            Debug.Assert(PlayButt.Content == "Play");
            
            try {
                SetLanguage("France");
            } catch(Exception) {}
        }
        private void test_SetTheme() {
            SetTheme("Black");
            Debug.Assert(MainWindowXAML.Background != new SolidColorBrush(Color.FromArgb(255, 041, 039, 039)));

            SetTheme("White");
            Debug.Assert(MainWindowXAML.Background != new SolidColorBrush(Color.FromArgb(255, 197, 197, 197)));

            SetTheme("Green");
            Debug.Assert(MainWindowXAML.Background != new SolidColorBrush(Color.FromArgb(255, 018, 077, 029)));

            try {
                SetTheme("Violet");
            } catch (Exception) {}
        }
    }
}