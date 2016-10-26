using System;
using System.Collections.Generic;
using System.Net;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;
using System.Net.Sockets;
using System.Threading;

namespace Lab7_Server_
{
    class Server
    {
        HttpListener listener = new HttpListener();
        protected int port;
        protected string LogName = "SessionLog.log"; 

        public Server(int port)
        {
            Console.CancelKeyPress += (object sender, ConsoleCancelEventArgs e) => { Report(2); };
            this.port = port;
        }
        ~Server()
        {
            listener.Close();
            Report(2);
        }

        public void Run(){
            string prefix = "http://127.0.0.1:" + port + "/";
            listener.Prefixes.Add(prefix);
            Report(1);
            listener.Start();
            
            while (true){
                Console.WriteLine("Listening..");
                HttpListenerContext Context = listener.GetContext();
                
                Thread thread = new Thread(new ParameterizedThreadStart(ParseRequest));
                thread.Start(Context as object);
            }
        }
        private List<Song> GetSongs(string FolderPath){
            List<Song> result = new List<Song>();

            FileInfo[] FilesInDIrectory = new DirectoryInfo(FolderPath).GetFiles();
            for (int i = 0; i < FilesInDIrectory.Length; i++){
                if (Regex.IsMatch(FilesInDIrectory[i].Name, @"([a-zA-Z]*\s*)* - ([a-zA-Z]*\s*)*.mp3" )){
                    // Hard logic
                    string filename;
                    if (FolderPath.EndsWith("\\"))  filename = FolderPath + FilesInDIrectory[i];    
                    else filename = FolderPath + "\\" + FilesInDIrectory[i];
                    
                    string Author = Regex.Match(filename, @"[\s\S]* -").ToString().Remove(filename.IndexOf(" -")).Remove(0, filename.LastIndexOf("\\") + 1);
                    string Title = Regex.Match(filename, @"- [\s\S]*").ToString().Remove(Regex.Match(filename, @"- [\s\S]*").ToString().IndexOf(".")).Remove(0, 2);
                    string Path = filename;
                    
                    result.Add(new Song(Author, Title, SongStyle.None, filename));
                }   
            }

            return result;
        }
        private void ParseRequest(object objectContext)
        {
            HttpListenerContext context = (HttpListenerContext)objectContext;
            switch (context.Request.HttpMethod.ToUpper())
            {
                case "GET": HandleGetRequest(ref context); break;
                case "POST": HandlePostRequest(ref context); break;
            }
            Report(context.Request);
        }
        public void Report(int phase)
        {
            string text = null;

            switch(phase)
            {
                case 0: text = "There's a bug to fix"; break;
                case 1: text = "Server started work."; break; 
                case 2: text = "Server stopped work."; break;
            }
            using (StreamWriter writer = new StreamWriter(LogName, true))
                writer.WriteLine(System.DateTime.Now + text);
        }
        public void Report(HttpListenerRequest request)
        {
            using (StreamWriter writer = new StreamWriter(LogName, true))
                writer.WriteLine(request.UserHostAddress + " " + System.DateTime.Now + " " + request.HttpMethod + " " + request.RawUrl);
        }

        private void HandleGetRequest(ref HttpListenerContext context)
        {
            List<Song> MusicLib = GetSongs(@"C:\Users\Nick\Music\ServerMusicFolder");
            HttpListenerRequest Request = context.Request;
            HttpListenerResponse Response = context.Response;

            if (Request.Url.LocalPath == "/"){
                string ResponseString = "<?xml version=\"1.0\" encoding=\"utf-8\"?><Response>";
                for (int i = 0; i < MusicLib.Count; i++){
                    ResponseString += string.Format("<Song><Author>{0}</Author><Title>{1}</Title><Style>{2}</Style></Song>\n", MusicLib[i].Author, MusicLib[i].Title, MusicLib[i].Style.ToString());
                }
                ResponseString += "</Response>";
                
                Response.StatusCode = (int)HttpStatusCode.OK;
                byte[] ReBytes = Encoding.ASCII.GetBytes(ResponseString);
                Response.ContentLength64 = ReBytes.Length;
                Response.OutputStream.Write(ReBytes, 0, ReBytes.Length);
                Response.OutputStream.Close();
                Console.WriteLine("Handled\n\n-->");
            }
            if (Regex.IsMatch(Request.Url.LocalPath, "/([a-zA-Z]*[\\s,]*){1,7} - ([a-zA-Z]*\\s*){1,7}"))
            {
                for (int i = 0; i < MusicLib.Count; i++){
                    string Pattern = MusicLib[i].ToString();
                    if (Regex.IsMatch(Request.Url.LocalPath, Pattern)){
                        Response.StatusCode = (int)HttpStatusCode.OK;

                        byte[] ReBytes = Encoding.ASCII.GetBytes(File.ReadAllBytes(MusicLib[i].Path).Length.ToString());
                        Response.ContentLength64 = ReBytes.Length;
                        Response.OutputStream.Write(ReBytes, 0, ReBytes.Length);
                        Response.OutputStream.Close();
                        
                        UploadSong(MusicLib[i].Path);
                        break;
                    }
                }
            Console.WriteLine("Get Request Handled\n\n-->");
            }
        }
        private void HandlePostRequest(ref HttpListenerContext context)
        {
            HttpListenerResponse Response = context.Response;
            HttpListenerRequest Request = context.Request;

            Response.StatusCode = (int)HttpStatusCode.OK;
            int Length = Int32.Parse(Request.Headers["Length"]);
            byte[] ReBytes = Encoding.ASCII.GetBytes("Ready for downloadling");
            Response.ContentLength64 = ReBytes.Length;
            Response.OutputStream.Write(ReBytes, 0, ReBytes.Length);
            Response.OutputStream.Close();
            byte[] ByteSong = DownloadSong(11000, Length);
            if (ByteSong.Length != 0){
                string path = "C:\\Users\\Nick\\Music\\ServerMusicFolder\\";
                string filePath = string.Format("{0}{1}", path, Request.Headers["name"] + ".mp3");
                using (BinaryWriter bWriter = new BinaryWriter(new FileStream(filePath, FileMode.Create)))
                    bWriter.Write(ByteSong);       
                Console.WriteLine("Post Request Handled\n\n-->");
            }
            else { Console.WriteLine("Error Handled"); }
        }
        
        private void UploadSong(string SongPath)
        {
            IPHostEntry ipHost = Dns.GetHostEntry("localhost");
            IPAddress ipAddr = ipHost.AddressList[0];
            IPEndPoint ipEndPoint = new IPEndPoint(ipAddr, 11000);
            Socket sListener = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            Socket handler = null;

            try{
                sListener.Bind(ipEndPoint);
                sListener.Listen(10);

                Console.WriteLine("Waiting for a connection establishment at {0}", ipEndPoint);
                handler = sListener.Accept();

                byte[] msg = File.ReadAllBytes(SongPath);
                handler.Send(msg);

                Console.WriteLine("The song has been successfully sent...\n\n-->");
            }
            catch (Exception ex){
                Console.WriteLine("Can't send a song.. Coz of some unexpected problems\n" + ex.ToString() + "\n\n-->");
            }
            finally{
                handler.Shutdown(SocketShutdown.Both);
                handler.Close();
                sListener.Close();
            }
        }
        private static byte[] DownloadSong(int port, int SongLength)
        {
            byte[] bytes = new byte[SongLength];
            IPHostEntry ipHost = Dns.GetHostEntry("localhost");
            IPAddress ipAddr = ipHost.AddressList[0];
            IPEndPoint ipEndPoint = new IPEndPoint(ipAddr, 11000);
            Socket sListener = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            Socket handler = null;
            try{
                sListener.Bind(ipEndPoint);
                sListener.Listen(10);
                while (true){
                    handler = sListener.Accept();
                    handler.Receive(bytes);

                    Console.Write("The song has been successfully recieved...\n--->");
                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                }
            }
            catch (Exception ex){
                Console.WriteLine("Can't send a song.. Coz of some unexpected problems\n" + ex.ToString() + "\n\n-->");
                byte[] Error = new byte[0];
            }
            finally{
                handler.Shutdown(SocketShutdown.Both);
                handler.Close();
                sListener.Close();
            }

            return bytes;
        }
    }
        
    class Program
    {
        static void Main(){
            Server server = new Server(8080);
            server.Run();

            Console.WriteLine("Shutting down the serever, because no connection with DataBase\n press any key...");
            server.Report(0);
            Console.ReadKey(); 
            return;
        }
    }
}