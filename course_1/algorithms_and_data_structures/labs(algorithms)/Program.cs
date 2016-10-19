using System.Collections.Generic;
using Algorithms.Trees;
using System.Linq;
using System.IO;
using System;

namespace Algorithms {
    enum States { MainMenu, TreeTestMenu, HashTableTest, ShuttingDown }

    static class Program {
        static States State;

        static private string[] ProgramFiles{
            get{ return Directory.GetFiles("Data"); }}
        static private void GenerateRandomFiles() {
            int ValuesAmount = 64;

            for (int i = 0; i < 15; i++, ValuesAmount*= 2)
                using (var writer = new StreamWriter(@"Data\Values(2^" + (int)Math.Log(ValuesAmount, 2) + ").txt")) {
                    Random dice = new Random();
                    int nextValue = dice.Next(0, Int32.MaxValue);
                    for (int j = 0; j < ValuesAmount; j++) {
                        // Engeneer solution, all existing values are even values. Why? For existing and unexisting values search.
                        writer.WriteLine(nextValue % 2 == 0? nextValue : ++nextValue); 
                    }
                }
            Console.WriteLine("Files were generated.");
        }
        static private void ColorWrite(string input, ConsoleColor color){
            Console.ForegroundColor = color;
            Console.Write(input);
            Console.ForegroundColor = ConsoleColor.Gray;
        }
        static private void ColorWriteLine(string input, ConsoleColor color){
            Console.ForegroundColor = color;
            Console.WriteLine(input);
            Console.ForegroundColor = ConsoleColor.Gray;
        }
        static private int[] GetNumbers(string path) {
            List<int> ListResult = new List<int>();
            using (var reader = new StreamReader(path))
                while(!reader.EndOfStream)
                    ListResult.Add(Int32.Parse(reader.ReadLine()));
            return ListResult.ToArray();
        }

        private static void Main(){
            State = States.MainMenu;

            while (true) {
                Console.Clear();
                switch(State) {
                    case States.MainMenu: ShowMainMenu(); break;
                    case States.TreeTestMenu: ShowGreenery(); break;
                    case States.HashTableTest: break;
                    case States.ShuttingDown: return;
                }
                
            }
        }
        private static void ShowMainMenu() {
            Console.WriteLine("Was made by Shkaruba Nickita, IFMO university, IPM 1121 group");
            Console.Write("Commands:\n\t1) Generate files\n\t2) To the Greenery - Tree tests\n\t" +
            "3) Hash Table tests\n\t0) Quit");
            
            ColorWrite(("\n\nInput your command: "), ConsoleColor.DarkMagenta);
            switch (Console.ReadLine().ToLower()) {
                case "1":  GenerateRandomFiles(); break; 
                case "2":  State = States.TreeTestMenu; break; 
                case "3":  State = States.HashTableTest; break;
                case "0":  State = States.ShuttingDown; break;
            }
        }
        private static void ShowGreenery() {
            string Place = "";
            int[] Input = null;
            ITree Tree = null;
            
                Console.Clear();
                Console.WriteLine("Places to grow avaiable: ");
                
                int FileNumber = 1;
                Dictionary<int, string> filenames = new Dictionary<int,string>();
                foreach (var filename in Directory.GetFiles(@"Data\", "*.txt").OrderBy( p => p.Length)) {
                    Console.WriteLine("\t{0}) {1}", FileNumber, filename);
                    filenames.Add(FileNumber++, filename);
                }
                Console.WriteLine("\n\t0) Back\n");

            // *Choosing filePath
            while (Input == null) {
                ColorWrite(("* Choose a place to grow: "), ConsoleColor.DarkMagenta);
                Place = Console.ReadLine();
                if (Place == "0") {
                    State = States.MainMenu; 
                    return;
                }
                else // There's might be an exception, i'll fix it latelly
                    Input = GetNumbers(filenames[Int32.Parse(Place)]); break;
            }

            // **Choosing Tree sort
            while (Tree == null) {
                Console.Clear();
                Console.WriteLine("Tree seeds avaiable:\n\t1) RedBlack Tree\n\t2) Cartesian Tree\n\t3) BTree\n\t4) AVL Tree\n\t5) Splay Tree\n\t0) Back");
            
                ColorWrite(("Choose a seed: "), ConsoleColor.DarkMagenta);
                string Seed = Console.ReadLine();
                ColorWrite("\nGrowing up tree. Please wait...", ConsoleColor.DarkRed);
                int PlaneSeconds = Environment.TickCount;
                switch(Seed.ToLower()) {
                    case "1": Tree = new RedBlackTree(Input); break;
                    case "2": Tree = Treap.Treapify(Input); break;
                    case "3": Tree = BTree.Initialize(Input); break;
                    case "4": Tree = AVLTree.Initialize(Input); break;
                    case "5": Tree = new SplayTree(Input); break;
                    case "0": State = States.MainMenu; return;
                }
                Console.WriteLine("\n** Grown for {0} miliseconds.\n", Environment.TickCount - PlaneSeconds);
            }
            
            // ***Calculating Existing and Unexisting values
            while (State != States.MainMenu) {
                // All existing is even
                int Existing_dt = Environment.TickCount; 
                for (int i = 0; i < Input.Count(); i++)
                    if (Tree.Search(Input[i]) == false) 
                        throw new Exception("BUG. Tree Couldn't find existing value. Cut it down."); 
                Existing_dt = Environment.TickCount - Existing_dt;
                
                // All Unexisting is odd
                int Unexisting_dt = Environment.TickCount; 
                for (int i = 0; i < Input.Count(); i++)
                    if (Tree.Search(Input[i]-1) == true) 
                        throw new Exception("BUG. Tree Found Unexisting value. Cut it down."); 
                Unexisting_dt = Environment.TickCount - Unexisting_dt;
                
                Console.Clear();
                Console.WriteLine("*** The whole search took {0} miliseconds", Existing_dt + Unexisting_dt);
                ColorWriteLine("ExistingValues: " + Existing_dt + " ms",ConsoleColor.Green);
                ColorWriteLine("UnexistingValues: " + Unexisting_dt + " ms",ConsoleColor.Red);

                Console.WriteLine("Press 0 to exit or any other key to continue the tests...");
                if (Console.ReadLine() == "0")
                    State = States.MainMenu;
            }
        }
    }
}