using System.Collections.ObjectModel;
using System.Collections.Generic;
using System.Windows.Threading;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Linq;
using System.Text;
using System.IO;
using System;

namespace Space {
    public class ManageCenter {
        public string[][] InterpreterGrid;
        public ObservableCollection<string> LogList = new ObservableCollection<string>();
        public List<string> States = new List<string>();
        public List<string> Tape = new List<string>();
        public List<string> Lexicon;
        public DispatcherTimer Clock = new DispatcherTimer();
        public bool IsMashineBusy = false;

        public void ReadComponents() {
            ///<.tcode format>
            ///
            ///  S0;0;0;1;1;2;2;1;1;0;S0;                   (Tape)
            ///   ,	 S0,	   0,	   1,      2;           (Program)
            ///  q1,	1_q0_L,	1_q3_R,	2_q1_R,	0_q3_R;     (Program)
            ///  q2,	2_q0_C,	2_q2_R,	0_q1_R,	1_q2_R;     (Program)
            ///  q3,	2_q0_R,	2_q2_L,	2_q3_C,	2_q1_L;     (Program)
            ///
            ///</TProgram1.tcode format>
            
            using(StreamReader reader = new StreamReader("Program1.tcode")) {
                Tape.AddRange(reader.ReadLine().Split(';').TakeWhile(p => p != ""));
                
                List<string[]> Buffer = new List<string[]>();
                while (!reader.EndOfStream)
                    Buffer.Add(reader.ReadLine().Replace("\t", "").Replace(";", "").Split(','));
                InterpreterGrid = Buffer.ToArray();
            }
            Lexicon = InterpreterGrid[0].Skip(1).ToList();

            foreach (var state in InterpreterGrid.Skip(1))
                States.Add(state[0]);
            States.Add("q0");
        }
    }

    public class TuringCommand {
        public PointerCommand PointerCommand;
        public string State;
        public string Value;

        public TuringCommand(string LaneToParse) {
            string[] ParsedLane = LaneToParse.Split('_');
            this.Value = ParsedLane[0];
            this.State = ParsedLane[1];
            this.PointerCommand = (PointerCommand)Enum.Parse(typeof(PointerCommand), ParsedLane[2]);
        }
    }

    public enum PointerCommand {C, L, R}
}
