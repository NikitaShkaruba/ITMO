using System.Text.RegularExpressions;
using System.Collections.Generic;
using System.Windows.Media;
using System.Net.Sockets;
using System.Threading;
using System.Windows;
using System.Timers;
using System.Text;
using System.Net;
using System.Xml;
using System.IO;
using System;

namespace MusicPlayer_ClientSide {
    public enum Theme { Dark, White, Green }
    public enum MediaState { Playing, Stopped, EndOfFile }
    public enum SongStyle { Instrumental, Rock, DubStep, Pop, Slow, None }

    public class Song : IComparable<Song> {
        public string Title { get; set; }
        public string Author { get; set; }
        public string Path { get; set; }
        public double Length { get{
                ExtendedPlayer Checker = new ExtendedPlayer();

                Checker.Open(new Uri(this.Path, UriKind.RelativeOrAbsolute));
                while (!Checker.NaturalDuration.HasTimeSpan) { } //OMG, the litte delay just tearing me apart

                return Checker.NaturalDuration.TimeSpan.TotalMilliseconds;
            } 
        }
        public double InBytesLength { 
            get {
                byte[] msg = File.ReadAllBytes(this.Path);
                return msg.Length;
            } 
        }
        
        public Song(string author, string title, string path) {
            Title = title;
            Author = author;
            Path = path;
        }
        public Song(string filePath) {
            Author = Regex.Match(filePath, @"[\s\S]* -").ToString().Remove(filePath.IndexOf(" -")).Remove(0, filePath.LastIndexOf("\\") + 1);
            Title = Regex.Match(filePath, @"- [\s\S]*").ToString().Remove(Regex.Match(filePath, @"- [\s\S]*").ToString().IndexOf(".")).Remove(0, 2);
        }
        public Song() {

        }

        public static SongStyle TryParse(string s) {
            switch (s.ToUpper()) {
                case "ROCK": return SongStyle.Rock;
                case "SLOW": return SongStyle.Slow;
                case "INSTRUMENTAL": return SongStyle.Instrumental;
                case "DUBSTEP": return SongStyle.DubStep;
                case "POP": return SongStyle.Pop;

                default: return SongStyle.None;
            }
        }
        public override string ToString() {
            return string.Format("{0} - {1}", this.Author, this.Title);
        }
        public int CompareTo(Song other) {
            int barrier;
            if (this.ToString().Length > other.ToString().Length)
                barrier = other.ToString().Length;
            else 
                barrier = this.ToString().Length;

            for (int i = 0; i < barrier; i++) {
                if (this.ToString()[i] < other.ToString()[i])
                    return -1;

                if (this.ToString()[i] > other.ToString()[i])
                    return 1;
                
                if (this.ToString()[i] == other.ToString()[i])
                    continue;
            }
            return 0;
        }
    }

    public class ExtendedPlayer : MediaPlayer {
        public System.Timers.Timer timer = new System.Timers.Timer(500); // it's a second/2.
        public MediaState State { get; private set; }
        public double Step;
        public bool ChangedByUserHands;

        public ExtendedPlayer() {
            State = MediaState.Stopped;
            ChangedByUserHands = false;
            this.Volume = 0.5;
            this.Pause();
        }

        public new void Open(Uri source){
            base.Open(source);
            while (!this.NaturalDuration.HasTimeSpan) { } // Damn, dunno how to fix this !#@
            this.Step = (10 / this.NaturalDuration.TimeSpan.TotalSeconds) / 2;
            
            Play();
        }
        public new void Play(){
            base.Play();
            timer.Start();
            this.State = MediaState.Playing;
        }
        public new void Pause(){
            base.Pause();
            timer.Stop();
            if (State != MediaState.EndOfFile)
                this.State = MediaState.Stopped;
        }
    }

    public static class HttpClient {
        public static List<Song> GetSongList() {
            List<Song> result = new List<Song>();;

            try {
                HttpWebRequest request = (HttpWebRequest)HttpWebRequest.Create("http://127.0.0.1:8080/");
                HttpWebResponse response = (HttpWebResponse)request.GetResponse();

                using (StreamReader stream = new StreamReader(response.GetResponseStream(), Encoding.UTF8)) {
                    XmlDocument doc = new XmlDocument();
                    string s = stream.ReadToEnd();
                    doc.LoadXml(s);

                    foreach (XmlNode ResponseNode in doc.SelectNodes("Response")) {
                        foreach (XmlNode SongNode in ResponseNode.ChildNodes){
                            Song currentSong = new Song();
                            foreach (XmlNode Attribute in SongNode.ChildNodes) {
                                switch (Attribute.Name) {
                                    case "Author": { currentSong.Author = Attribute.InnerText; break; }
                                    case "Title": { currentSong.Title = Attribute.InnerText; break; }
                                    default: MessageBox.Show("Your Current version is obsolete."); break;
                                }
                            }
                            result.Add(currentSong);
                        }
                    }
                    if (result.Count == 0)
                        MessageBox.Show("There's no songs on server, or it's some kind of an error.\n");
                }

                return result;
            }
            catch (Exception ex) {
                MessageBox.Show(ex.Message);
                result = new List<Song>();
                result.Add(new Song("Error", "Can't connect to a server", "Nope"));
                
                return result;
            }
        }

        public static void DownloadSongRequest(string serverIp, string AuthorTitle) {
            HttpWebRequest request = (HttpWebRequest)HttpWebRequest.Create(String.Format("http://{0}:8080/{1}", serverIp, AuthorTitle));
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            StreamReader dataStream = new StreamReader(response.GetResponseStream());
            int length = Int32.Parse(dataStream.ReadToEnd());

            byte[] ByteSong = GetSong(serverIp, 11000, length);

            using (BinaryWriter bWriter = new BinaryWriter(new FileStream(string.Format("{0}{1}", App.FolderPath, AuthorTitle + ".mp3" ), FileMode.Create))) {
                bWriter.Write(ByteSong);
            }
            MessageBox.Show("Successfully added.");
        }
        private static byte[] GetSong(string serverIP, int port, int SongLength) {
            byte[] bytes = new byte[SongLength];
            try {
                IPHostEntry ipHost = Dns.GetHostEntry("localhost");
                IPAddress ipAddr = ipHost.AddressList[0];
                Socket sender = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                Thread.Sleep(1000);

                IPEndPoint ipEndPoint = new IPEndPoint(ipAddr, port);
                sender.Connect(ipEndPoint);

                sender.Receive(bytes);

                //sender.Shutdown(SocketShutdown.Both);
                //sender.Close();
                return bytes;
            }
            catch(Exception ex) { MessageBox.Show(ex.Message); return bytes; }
        }
        
        public static void UploadSongRequest(String ServerIp, Song sng) {
            HttpWebRequest request = (HttpWebRequest)HttpWebRequest.Create(String.Format("http://{0}:8080/", ServerIp));
            request.Method = "POST";
            request.ContentLength = 0;
            request.Headers.Add("Name", sng.ToString());
            request.Headers.Add("Length", sng.InBytesLength.ToString());
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            StreamReader dataStream = new StreamReader(response.GetResponseStream());
            SendSong(ServerIp, sng.Path);
        
            MessageBox.Show("Successfully added.");
        }
        private static void SendSong(string ServerIp, string SongPath) {
            IPHostEntry ipHost = Dns.GetHostEntry("localhost");
            IPAddress ipAddr = ipHost.AddressList[0];
            IPEndPoint ipEndPoint = new IPEndPoint(ipAddr, 11000);

            Socket sender = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            Thread.Sleep(1000);
            sender.Connect(ipEndPoint);

            byte[] msg = File.ReadAllBytes(SongPath);
            sender.Send(msg);
            
            sender.Shutdown(SocketShutdown.Both);
            sender.Close();
        }
    }
}