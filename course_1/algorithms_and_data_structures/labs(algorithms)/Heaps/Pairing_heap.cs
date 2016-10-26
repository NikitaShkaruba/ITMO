using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// Author: Dima
class Pairing_heap
{
    class Node
    {
        public int key;
        // Левый сын
        public Node child;
        // Правый брат
        public Node nextSibling;

        public Node(int key)
        {
            this.key = key;
            child = null;
            nextSibling = null;
        }

        // Добавить потомка
        public void AddChild(Node a)
        {
            a.nextSibling = this.child;
            this.child = a;
        }
    }

    Node root = null;

    // Слить две кучи
    private static Node Merge(Node a, Node b)
    {
        if (a == null)
            return b;
        if (b == null)
            return a;
        if (a.key < b.key)
        {
            a.AddChild(b);
            return a;
        }
        else
        {
            b.AddChild(a);
            return b;
        }
    }

    // Добавить элемент в кучу
    public void Add(int key)
    {
        if (this.root == null)
            this.root = new Node(key);
        else
            this.root = Merge(this.root, new Node(key));
    }

    public bool Empty()
    {
        return root == null;
    }

    // Получить и удалить минимальный элемент
    public int GetMin()
    {
        int t = root.key;

        if (root.child == null)
        {
            root = null;
            return t;
        }

        Queue<Node> pairs = new Queue<Node>();

        Node cur = root.child;
        while (cur != null && cur.nextSibling != null)
        {
            Node first = cur;
            cur = cur.nextSibling;
            first.nextSibling = null;
            Node second = cur;
            cur = cur.nextSibling;
            second.nextSibling = null;
            pairs.Enqueue(Merge(first, second));
        }
        if (cur != null)
            pairs.Enqueue(cur);
        root = pairs.Dequeue();
        while (pairs.Count != 0)
        {
            root = Merge(root, pairs.Dequeue());
        }
        return t;
    }
}
