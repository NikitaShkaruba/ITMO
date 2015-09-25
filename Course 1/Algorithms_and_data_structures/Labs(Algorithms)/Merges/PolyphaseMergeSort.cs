using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

// Author: me
namespace Algorithms.Trees {
    class Tape
    {
        private StreamWriter writer;
        private StreamReader reader;
        public string Path{ get; private set; }
        public int Count{ 
            get;
            set;
        }
 
        public Tape(string Path){
            this.Path = Path;
            using(reader = new StreamReader(Path)){
                while(!reader.EndOfStream)
                    Count++;
            }
         
        }
     
        public int Pop(){
            int result;
 
            using(reader = new StreamReader(Path)) 
                result = Int32.Parse(reader.ReadLine());
            //using(writer = new StreamWriter(Path))
            //    reader.read
                    Count--;
            return result;
        }    
        public Run PopRun(){
            Run result = new Run();
 
            using(reader = new StreamReader(Path)) 
                result.Enqueue(Int32.Parse(reader.ReadLine()));
            //using(writer = new StreamWriter(Path))
            //    reader.read
            Count--;
            
            return result;
        }
        public void Push(int input){
            using (writer = new StreamWriter(Path, true))
                writer.WriteLine(input.ToString(), true);
            Count++;
        }
        public void Push(string input){
            using (writer = new StreamWriter(Path, true))
                writer.WriteLine(input, true);
            Count++;
        }
        public void Push(Run input){
            while (!input.IsEmpty) {
                using(writer = new StreamWriter(Path, true)){
                    writer.WriteLine(input.Dequeue().ToString(), true);
                    Count++;
                }
            }
        }
    }
    public class Run
    {
        protected Queue<int> Values = new Queue<int>();
        
        public Run(Run[] runs)
        {
            //This constructor takes array of runs and merges it into one output run
            List<int> cream = new List<int>(runs.Count());
            int empty_runs = 0;

            for (int i = 0; i < runs.Count(); i++){
                if ((object)runs[i] is Fake_Run || runs[i] == null)
                    empty_runs++;
                cream.Add(runs[i].Dequeue());
            }
            while (empty_runs != runs.Count()){
                int Imin = cream.IndexOf(cream.Min());

                Values.Enqueue(cream[Imin]);

                if (!runs[Imin].IsEmpty)
                    cream[Imin] = runs[Imin].Dequeue();
                else{
                    cream[Imin] = 999999999;
                    empty_runs++;
                }
            }
        }
        public Run(int number)
        {
            Values.Enqueue(number);
        }
        public Run(){}

        public void Enqueue(int number)
        {
            Values.Enqueue(number);
        }
        public int Dequeue(){
            return Values.Dequeue();
        }
        public bool IsEmpty{
            get{ return (Values.Count == 0)? true : false; }
        }
        public int[] ToArray() {
            int[] array = new int[Values.Count];
            for (int i = 0; i < Values.Count; i++) {
			    array[i] = Values.Dequeue();
			}
            return array;
        }
    }
    public class Fake_Run : Run
    {
        public Fake_Run(){
            Values = new Queue<int>();
            Values.Enqueue(999999999);
        }
    }

    class PolyphaseMergeSort {
          private static List<Queue<Run>> MakeTapes()
            {
                List<Queue<Run>> result = new List<Queue<Run>>();

                for (int i = 0; i < 6; i++)
                    result.Add(new Queue<Run>());

                return result;
            }

        public static int[] StartPolyphaseMerge(string filename) {
            List<Queue<Run>> Tapes = MakeTapes(); 

            int output = 5;
            // 1.
            Queue<Run> Runs = GetRuns(filename);
            // 2.
            int level, Absolute_fibbonacci_number = GetAbsoluteFibbonacciSum(Runs.Count, out level);
            while (Runs.Count != Absolute_fibbonacci_number)
                Runs.Enqueue(new Fake_Run());
            // 3.
            Run LastRun=null;
            if (level > 0)
            {
                int dam = GetFibonacci(level);
                for (int j = 0; j < 5; j++)
                {
                    for (int i = 0; i < dam; i++)
                        Tapes[j].Enqueue(Runs.Dequeue());
                    int s = GetFibonacci(level - 5 + j);
                    dam -= s;
                }
                // 4.
                while (Tapes.Count(querry => querry.Count == 1) != 1 || Tapes.Count(querry => querry.Count == 0) != 5)
                {
                    do
                    {
                        Run[] Cream = new Run[5];
                        int InputCount = 0;
                        for (int i = 0; InputCount != 5; i++)
                        {
                            if (i != output)
                                Cream[InputCount++] = Tapes[i].Dequeue();
                        }
                        Tapes[output].Enqueue(new Run(Cream));
                    } while (Tapes.Count(p => p.Count() == 0) != 1 && Tapes.Count(p => p.Count() == 0) != 5);
                    output = Tapes.FindIndex(p => p.Count() == 0);
                }

            // 5.
            output = Tapes.FindIndex(p => p.Count == 1);
            LastRun = Tapes[output].Dequeue();
            }
                
            return Runs.Dequeue().ToArray();
                
            // 1. Распарстить файл, собирая run'ы                                                       |+|
            // 2. Посчитать Фибоначивую сумму нашего порядка и добить до неё количество наших run'ов    |+|
            // 3. Распределить начальную партию на все 5 лент                                           |+|
            // 4. Собственно, сливать партии со всех input лент на output                               |+|
            // 4~. Когда закончится один input, то поменять output местами с empty input                |+|
            // 4~~. Повторять Пункт(3), пока не образуется одна единственная партия                     |+|
            // 5. Записать единственный run в output file и вспомнить, что жизнь прекрасна              |+|

            Console.WriteLine("Done.");
        }
        public static int GetFibonacci(int n)
        {
            if (n < 0) return 0;
            if (n == 0 || n == 1)
                return 1;

            return GetFibonacci(n - 1) + GetFibonacci(n - 2) + GetFibonacci(n - 3) + GetFibonacci(n - 4) + GetFibonacci(n - 5);
        }
        private static Queue<Run> GetRuns(string Path_To_File)
        {
            Queue<Run> ResultedRuns = new Queue<Run>();
            Run CurrentRun = new Run();

            using (StreamReader rdr = new StreamReader(@"Unsorted files\" + Path_To_File)){
                SortedSet<int> SortedHeap = new SortedSet<int>();
                SortedHeap.Reverse();
                List<int> ReserveList = new List<int>();

                for (int i = 0; i < 4; i++)
                    SortedHeap.Add(Int32.Parse(rdr.ReadLine()));

                do{  
                    while (SortedHeap.Count != 0){
                        int pretendent = SortedHeap.First();
                        SortedHeap.Remove(SortedHeap.First());

                        CurrentRun.Enqueue(pretendent);
                        if (!rdr.EndOfStream){
                            int Next = Int32.Parse(rdr.ReadLine());

                            if (Next >= pretendent)
                                SortedHeap.Add(Next);
                            else
                                ReserveList.Add(Next);
                        }
                    }
                    SortedHeap = new SortedSet<int>(ReserveList);
                    ReserveList = new List<int>();
                    ResultedRuns.Enqueue(CurrentRun);
                    CurrentRun = new Run();
                } while (SortedHeap.Count != 0);
            }
            return ResultedRuns;
        }
        public static int GetAbsoluteFibbonacciSum(int Count, out int level)
        {
            // Level is the most high Fibonacci number
            int i, Final_distribution = 1;

            for (i = 0; Final_distribution < Count; i++)
                Final_distribution += 4 * GetFibonacci(i);
            level = i;

            return Final_distribution;
        }
    }
}
