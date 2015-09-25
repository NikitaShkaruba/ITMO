using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

// Author: Nastya
namespace Leftist
{
    public class LeftistHeap
    {
        public Node root { get; set; }

        public LeftistHeap(Node node)
        {
            root = node;
        }
        public class Node
        {
            public int key { get; set; }
            public int npl  { get; set; }
            public Node right { get; set; }
            public Node left { get; set; }
            public Node(int k)
            {
                key = k;
                npl = 1;
            }
        }
        public static Node merge(Node x, Node y)
        {
            if (x == null)
                return y;

            if (y == null)
                return x;

            if (x.key > y.key)
            {
                Node temp = x;
                x = y;
                y = temp;
            }

            x.right = merge(x.right, y);

            if (x.left == null)
            {
                x.left = x.right;
                x.right = null;
            }
            
            else
            {
                if (x.left.npl < x.right.npl)
                {
                    Node temp = x.left;
                    x.left = x.right;
                    x.right = temp;
                }
                x.npl = x.right.npl + 1;
            }

            return x;
        }
        public void insert(int value)
        {
            Node node = new Node(value);
            root = merge(root, node);
        }
        public int extract_min()
        {
            int min = root.key;
            root = merge(root.left, root.right);

            return min;
        }
        public static LeftistHeap heapify(int[] A)
        {
            Queue<Node> queue = new Queue<Node>();

            for (int i = 0; i < A.Length; i++) queue.Enqueue(new Node(A[i]));

            int size = queue.Count;

            while (queue.Count > 1)
            {
                for (int i = 0; i < size; i++)
                {
                    if (queue.Count == 1) return new LeftistHeap(queue.Dequeue());

                    Node n1 = queue.Dequeue();
                    Node n2 = queue.Dequeue();

                    queue.Enqueue(LeftistHeap.merge(n1, n2));
                }
            }

            return new LeftistHeap(queue.Dequeue());
        }
        public void merge(LeftistHeap h)
        {
            root = merge(root, h.root);
            h.root = null;
        }
        public static int[] sort(ref int[] A)
        {
            LeftistHeap heap = heapify(A);

            for (int i = 0; i < A.Length; i++)
            {
                A[i] = heap.extract_min();
            }
            return A;
        }
    }
}
