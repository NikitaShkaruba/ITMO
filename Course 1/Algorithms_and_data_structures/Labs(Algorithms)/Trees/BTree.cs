using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// Author: Danya
namespace Algorithms.Trees
{
    public static class consts {
        // Count of the keys in one node
        public const int t = 50;
    }
    static class Disk
    {
        const int size = 4 * (2 + 4 * consts.t - 1);
        static FileStream file = new FileStream("B-tree.txt", FileMode.OpenOrCreate);

        public static void Write(BNode x)
        {
            file.Position = x.offset * size;
            byte[] bytes = NodeToBytes(x);
            foreach (byte b in bytes)
                file.WriteByte(b);
        }
        public static BNode Read(BNode x, int offset)
        {
            if (x == null)
                x = new BNode();
            if (x.isLoaded)
                return x;
            x.offset = offset;
            file.Position = size * offset;
            byte[] bytes = new byte[size];
            for (int i = 0; i < size; i++)
                bytes[i] = (byte)file.ReadByte();
            return BytesToNode(bytes);
        }

        private static byte[] NodeToBytes(BNode x)
        {

            int[] array;
            if (!x.isALeaf)
                array = new int[2 + 2 * x.length + 1];
            else
                array = new int[2 + x.length];
            array[0] = x.length;
            array[1] = x.isALeaf? 1:0;
            for (int i = 0; i < x.length; i++)
                array[i + 2] = x.keys[i];
            if (!x.isALeaf)
                for (int i = 0; i < x.length + 1; i++)
                    array[i + 2 + (x.length)] = x.childOffsets[i];
            byte[] bytes = new byte[(2 + 2 * x.length + 1) * 4];
            List<byte[]> byt = new List<byte[]>();
            foreach (int a in array)
                byt.Add(BitConverter.GetBytes(a));
            for (int j = 0; j < byt.Count; j++)
                for (int i = 0; i < 4; i++)
                    bytes[i + j * 4] = byt[j][i];
            return bytes;
        }
        private static BNode BytesToNode(byte[] bytes)
        {
            BNode result = new BNode();
            result.length = BitConverter.ToInt32(bytes, 0);
            result.isALeaf = BitConverter.ToInt32(bytes, 4) == 1;
            for (int i = 0; i < result.length; i++)
                result.keys[i] = BitConverter.ToInt32(bytes, 4 * (i + 2));
            if (!result.isALeaf)
                for (int i = 0; i < result.length + 1; i++)
                    result.childOffsets[i] = BitConverter.ToInt32(bytes, 4 * (i + 2 + result.length));
            result.isLoaded = true;
            return result;
        }
    }

    [Serializable]
    public class BNode
    {
        internal static int generalOffset = 0;
        internal const int t = consts.t;

        internal bool isLoaded = false;
        internal bool isALeaf;

        internal int length = 0;
        internal int offset;
        public int[] keys = new int[2*t-1];
        internal int[] childOffsets = new int[2*t];
        internal BNode[] children = new BNode[2*t];

        public BNode(bool leaf)
        {
            isALeaf = leaf;
        }
        public BNode(){}
        internal void InsertNonFull(int key)
        {
            int i = length - 1;
            if (isALeaf)
            {
                while (i >= 0 && keys[i] > key)
                {
                    keys[i + 1] = keys[i];
                    i--;
                }

                keys[i + 1] = key;
                length++;

                Disk.Write(this);
            }
            else
            {
                while (i >= 0 && keys[i] > key)
                    i--;
                i++;
                children[i] = Disk.Read(children[i], childOffsets[i]);
                if (children[i].length == 2 * t - 1)
                {
                    SplitChild(i, children[i]);

                    if (keys[i] < key)
                        i++;
                }
                children[i].InsertNonFull(key);
            }
        }
        internal void SplitChild(int i, BNode y)
        {
            BNode z = new BNode(y.isALeaf);
            z.length = t - 1;
            z.offset = generalOffset++;
            z.isLoaded = true;

            for (int j = 0; j < t - 1; j++)
                z.keys[j] = y.keys[j + t];

            if (!y.isALeaf)
            {
                for (int j = 0; j < t; j++)
                    z.childOffsets[j] = y.childOffsets[j + t];
            }

            y.length = t - 1;

            for (int j = length; j >= i + 1; j--)
            {
                childOffsets[j + 1] = childOffsets[j];
                children[j + 1] = children[j];
            }
            childOffsets[i + 1] = z.offset;
            children[i + 1] = z;

            for (int j = length - 1; j >= i; j--)
                keys[j + 1] = keys[j];

            keys[i] = y.keys[t-1];
            length++;
            Disk.Write(y);
            Disk.Write(z);
            Disk.Write(this);
        }
        public bool Search(int key)
        {
            int i=0;
            while (i < this.length && key > this.keys[i])
                i++;
            if (i < this.length && key == keys[i])
                return true;
            if (this.isALeaf)
                return false;
            else
            {
                children[i] = Disk.Read(children[i], childOffsets[i]);
                return  children[i].Search(key);
            }
        }


    }

    internal class BTree : ITree
    {
        internal BNode root;
        internal const int t = consts.t;

        public BTree()
        {
            root = new BNode(true);
            root.offset = BNode.generalOffset;
            BNode.generalOffset++;
            Disk.Write(root);
            root.isLoaded = true;
        }
        public static BTree Initialize(int[] keys)
        {
            BTree result = new BTree();
            foreach (int key in keys)
                result.Insert(key);
            return result;
        }

        public void Insert(int key)
        {
            if (root.length == 2 * t - 1)
            {
                BNode r = root;
                BNode s = new BNode(false);
                root = s;
                s.length = 0;
                s.childOffsets[0] = r.offset;
                s.children[0] = r;
                s.offset = BNode.generalOffset;
                BNode.generalOffset += 1;
                s.isLoaded = true;
                s.SplitChild(0, r);
                int i = 0;
                if (s.keys[0] < key)
                    i++;
                s.children[i].InsertNonFull(key);
                root = s;
            }
            else
                root.InsertNonFull(key);
        }
        public bool Search(int key)
        {
            return root.Search(key);
        }


        public void Remove(int key) {
            throw new NotImplementedException();
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
