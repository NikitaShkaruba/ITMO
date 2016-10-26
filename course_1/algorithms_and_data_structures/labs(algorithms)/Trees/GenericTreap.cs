using System;
using System.Collections.Generic;
using System.Text;

// Author: Danya
namespace treap
{
    //TREAP = TREe + hEAP;
    public class Treap<T> where T : IComparable 
    {
        private T key;
        private int rank;

        private Treap<T> left;
        private Treap<T> right;


        private Treap(T key, int rank, Treap<T> left = null, Treap<T> right = null)
        {
            this.key = key;
            this.rank = rank;
            this.left = left;
            this.right = right;
        }
        public static Treap<T> Create(IEnumerable<T> keys)
        {
            IEnumerator<T> enumerator = keys.GetEnumerator();
            if (!enumerator.MoveNext())
                return null;
            Random dice = new Random();

            Treap<T> result = new Treap<T>(enumerator.Current, dice.Next());
            while (enumerator.MoveNext())
                result = result.Add(enumerator.Current, dice.Next());
            return result;
        }
        public static IEnumerable<T> SortWithTreap (IEnumerable<T> keys)
        {
            Treap<T> treap = Treap<T>.Create(keys);
            foreach (var number in treap.TraverseInOrder())
                yield return number;
        }

        private static Treap<T> Merge(Treap<T> left, Treap<T> right)
        {
            if (left == null) return right;
            if (right == null) return left;

            if (left.rank > right.rank)
            {
                Treap<T> newRight = Merge(left.right, right);
                return new Treap<T>(left.key, left.rank, left.left, newRight);
            }
            else
            {
                Treap<T> newLeft = Merge(left, right.left);
                return new Treap<T>(right.key, right.rank, newLeft, right.right);
            }
        }
        private void Split(T key, out Treap<T> left, out Treap<T> right)
        {
            Treap<T> newTree = null;

            if (key.CompareTo(this.key) > 0)
            {
                if (this.right == null)
                    right = null;
                else
                    this.right.Split(key, out newTree, out right);
                left = new Treap<T>(this.key, this.rank, this.left, newTree);
            }
            else
            {
                if (this.left == null)
                    left = null;
                else
                    this.left.Split(key, out left, out newTree);
                right = new Treap<T>(this.key, this.rank, newTree, this.right);
            }
        }

        public static Treap<T> Search(Treap<T> tree, T key)
        {
            //NE TESTIL, DOLZHNO RABOTAT'
            //If Key can't be found returns null
            //otherwise returns treap containing that key
            if (tree == null)
                return null;

            if (tree.key.CompareTo(key) == 0)
                return tree;

            if (tree.key.CompareTo(key) > 0)
                return Search(tree.left, key);
            else
                return Search(tree.right, key);

        }
        
        public Treap<T> Add(T key, int rank)
        {
            Treap<T> left;
            Treap<T> right;
            Treap<T> keyTree = new Treap<T>(key, rank);

            this.Split(key, out left, out right);
            return Merge(Merge(left, keyTree), right);
        }
        public IEnumerable<T> TraverseInOrder()
        {
            if (this.left != null)
                foreach (var key in this.left.TraverseInOrder())
                    yield return key;

            yield return this.key;

            if (this.right != null)
                foreach (var key in this.right.TraverseInOrder())
                    yield return key;
        }
    }
}
