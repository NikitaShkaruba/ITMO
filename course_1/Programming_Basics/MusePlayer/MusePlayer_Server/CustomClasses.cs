using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using Finisar.SQLite;

namespace Lab7_Server_
{
    public enum SongStyle { Instrumental, Rock, DubStep, Pop, Slow, None }

    public class Song
    {
        public string Title { get; private set; }
        public string Author { get; private set; }
        public string Path { get; private set; }
        public SongStyle Style;

        public Song(string author, string title, SongStyle style, double length, string path)
        {
            Title = title;
            Author = author;
            Style = style;
            Path = path;
        }
        public Song(string author, string title, SongStyle style, string path){
            Title = title;
            Author = author;
            Style = style;
            Path = path;
        }
        public Song(string author, string title)
        {
            Title = title;
            Author = author;
            Path = "Secrets are everywhere";
        }
        public Song(string filePath)
        {
            Path = filePath;
            Author = Regex.Match(filePath, @"[\s\S]* -").ToString().Remove(filePath.IndexOf(" -")).Remove(0, filePath.LastIndexOf("\\") + 1);
            Title = Regex.Match(filePath, @"- [\s\S]*").ToString().Remove(Regex.Match(filePath, @"- [\s\S]*").ToString().IndexOf(".")).Remove(0, 2);
        }

        public Song(Song sng)
        {
            this.Title = sng.Title;
            this.Author = sng.Author;
            this.Path = sng.Path;
            this.Style = sng.Style;
        }

        public static SongStyle TryParse(string s)
        {
            switch (s.ToUpper())
            {
                case "NONE": return SongStyle.None;
                case "ROCK": return SongStyle.Rock;
                case "SLOW": return SongStyle.Slow;
                case "INSTRUMENTAL": return SongStyle.Instrumental;
                case "DUBSTEP": return SongStyle.DubStep;
                case "POP": return SongStyle.Pop;

                default: return SongStyle.None;
            }
        }
        public override string ToString()
        {
            return string.Format("{0} - {1}", this.Author, this.Title);
        }
        public void Corrupt()
        {
            this.Author += "{Corrupted}";
        }
    }
}