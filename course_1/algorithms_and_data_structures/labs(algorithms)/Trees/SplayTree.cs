using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// Author: Alex
namespace Algorithms.Trees 
{
    class SplayTree : ITree {
        class Node
        {
            public int value;
            public Node left;
            public Node right;
            public Node() {}
            public Node(int value): this(value, null, null)
            {
             

            }
            public Node(int value, Node left, Node right)
            { this.value = value; this.left = left; this.right = right; }
        }
        Node root;
        
        public SplayTree(int[] values) 
        {
            for (int i = 0; i < values.Length; i++) 
            {
                this.Insert(values[i]);
            }
        }
        public void Insert(int value)
        {
            // splay key to root
            if (root == null)
            {
                root = new Node(value);
                return; 
            }

            root = splay(root, value);

            int cmp = value.CompareTo(root.value);

            // Insert new node at root
            if (cmp < 0)
            {
                Node n = new Node(value);
                n.left = root.left;
                n.right = root;
                root.left = null;
                root = n;
            }

            // Insert new node at root
            else if (cmp > 0)
            {
                Node n = new Node(value);
                n.right = root.right;
                n.left = root;
                root.right = null;
                root = n;
            }

            // It was a duplicate key. Simply replace the value
            else if (cmp == 0)
            {
                root.value = value;
            }

        }
        public void Remove(int value)
        {
            if (root == null) return; // empty tree

            root = splay(root, value);

            int cmp = value.CompareTo(root.value);

            if (cmp == 0)
            {
                if (root.left == null)
                {
                    root = root.right;
                }
                else
                {
                    Node x = root.right;
                    root = root.left;
                    splay(root, value);
                    root.right = x;
                }
            }

        }
        
        
        //Splay функция
        private Node splay(Node h, int value)
        {
            if (h == null) return null;

            int cmp1 = value.CompareTo(h.value);

            if (cmp1 < 0)
            {
                // key not in tree, so we're done
                if (h.left == null)
                {
                    return h;
                }
                int cmp2 = value.CompareTo(h.left.value);
                if (cmp2 < 0)
                {
                    h.left.left = splay(h.left.left, value);
                    h = rotateRight(h);
                }
                else if (cmp2 > 0)
                {
                    h.left.right = splay(h.left.right, value);
                    if (h.left.right != null)
                        h.left = rotateLeft(h.left);
                }

                if (h.left == null) return h;
                else return rotateRight(h);
            }

            else if (cmp1 > 0)
            {
                // key not in tree, so we're done
                if (h.right == null)
                {
                    return h;
                }

                int cmp2 = value.CompareTo(h.right.value);
                if (cmp2 < 0)
                {
                    h.right.left = splay(h.right.left, value);
                    if (h.right.left != null)
                        h.right = rotateRight(h.right);
                }
                else if (cmp2 > 0)
                {
                    h.right.right = splay(h.right.right, value);
                    h = rotateLeft(h);
                }

                if (h.right == null) return h;
                else return rotateLeft(h);
            }

            else return h;
        }
        
        
        //Вспомагательные функции
        //Функции поворотов и др.
        public int height() { return height(root); }
        private int height(Node x)
        {
            if (x == null) return -1;
            return 1 + Math.Max(height(x.left), height(x.right));
        }
        public int size()
        {
            return size(root);
        }
        private int size(Node x)
        {
            if (x == null) return 0;
            else return (1 + size(x.left) + size(x.right));
        }
        // right rotate
        private Node rotateRight(Node h)
        {
            Node x = h.left;
            h.left = x.right;
            x.right = h;
            return x;
        }
        // left rotate
        private Node rotateLeft(Node h)
        {
            Node x = h.right;
            h.right = x.left;
            x.left = h;
            return x;
        }

        public bool Search(int value) 
        {
            return Search(value, root);
        }
        private bool Search(int key, Node gazing)
        {
            if (gazing == null) return false;
            if (key < gazing.value)
                return Search(key, gazing.left);
            if (key > gazing.value)
                return Search(key, gazing.right);
            if (gazing.value == key)
                return true;
            return true;
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
