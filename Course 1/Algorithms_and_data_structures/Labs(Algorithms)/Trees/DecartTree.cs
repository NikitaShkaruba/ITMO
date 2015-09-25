using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.Generic;

// Author: me
namespace Algorithms.Trees {
    class Treap : ITree {
        public int x { get; private set; } // Key
        public int y { get; private set; } // Priority
        public static int Count = 0;
        public Treap Left{ get; set; }
        
        public Treap Right{ get; set; }
        public Treap(){}
        public Treap(Treap copy){
            x = copy.x;
            y = copy.y;
            Left = copy.Left;
            Right = copy.Right;
            Count++;
        }
        public Treap(int key){
            Random rnd = new Random();
            this.x = key;
            this.y = rnd.Next();
            Count++;
        }
        public Treap(int key, int priority, Treap left = null, Treap right = null) {
            this.x = key;
            this.y = priority;
            this.Left = left;
            this.Right = right;
            Count++;
        }
        public static Treap Treapify(int[] numbers) {
            Random dice = new Random();
            Treap Root = new Treap();

            foreach (int number in numbers)
                Root = Root.Grow(number, dice.Next());
            return Root; 
        }
        public static Treap Treapify(int[] x, int[] y) {
            Treap Root = new Treap();
            for (int i = 0; i < 11; i++) {
                Root = Root.Grow(x[i], y[i]);
            }
            return Root;
        }
        public bool Search(int key) {
            return Search(key, this);
        }
        private bool Search(int key, Treap gazing){
            if (gazing == null) return false;
            if (key < gazing.x)
                return Search(key, gazing.Left);
            if (key > gazing.x)
                return Search(key, gazing.Right);
            if (gazing.x == key)
                return true;
            return true;
        }
        public Treap Grow(int x, int y) {
            Treap left, right;
            this.Split(x, out left, out right);
            Treap buf = Merge(left, new Treap(x, y));
            Treap result = Merge(buf, right);
                
            return result;
        }
        public void Remove(int value) {
            throw new NotImplementedException();
            // Treap firebox, left, right;
            // Split(value, out left, out right);
            // right.Split(value, out firebox, out right);
            // return Merge(left, right);
        }
        public override string ToString() {
            return "X:" + this.x + "; Y:" + this.y;
        }

        private static Treap Merge(Treap left, Treap right){
            if (left == null) return right;
            if (right == null) return left;

            if (left.y > right.y) 
                return new Treap(left.x, left.y, left.Left, Merge(left.Right, right));
            else
                return new Treap(right.x, right.y, Merge(left, right.Left), right.Right);
        }
        private void Split(int key, out Treap left, out Treap right){
            Treap NewTree = null;
            
            if (this.x <= key) {
                if (this.Right == null) 
                    right = null; 
                 else 
                    this.Right.Split(key, out NewTree, out right);
                left = new Treap(this.x, this.y, this.Left, NewTree);
            } else {
                if (this.Left == null) 
                    left = null; 
                 else 
                    this.Left.Split(key, out left, out NewTree);
                right = new Treap(this.x, this.y, NewTree, this.Right);
            }
        }

        public void Insert(int key) {
            Random dice = new Random();
            this.Grow(key, dice.Next(0, Int32.MaxValue));
        }




        public int[] InfixTraverse() {
            throw new NotImplementedException();
        }

        public int[] PrefixTraverse() {
            throw new NotImplementedException();
        }

        public int[] PostfixTraverse() {
            throw new NotImplementedException();
        }
    }
}
