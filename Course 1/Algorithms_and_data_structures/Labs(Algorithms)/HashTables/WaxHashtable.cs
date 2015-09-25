using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

// Author: me
namespace Algorithms.Trees {
    class WaxHashtable<K, V> where K: IEquatable<K>, IConvertible {
        private class ChainPart{
            public ChainPart next { get; private set; }
            
            public K key;
            public V value;

            public ChainPart(K key, V value, ChainPart last) {
                this.key = key;
                this.value = value;
                next = last;
            }
            public override string ToString() {
                return this.key.ToString() + "-->" + this.next;
            }
        }
        
        private ChainPart[] Table = new ChainPart[2];
        public double LoadFactor{ get{ return (double)Count / (double)Height; } }
        private int Count{ get; set; }
        private int Height{ get{ return Table.Count(); } }

        public void Insert(K key, V value) {
            int HashKey = Hash(key, this.Height);
            ChainPart current = Table[HashKey];
            
            while (current != null){
                if (current.key.Equals(key)) {
                    Console.WriteLine("Already exist.");
                    return;
                }
                current = current.next;
            }
            ++Count;
            Table[HashKey] = new ChainPart(key, value, Table[HashKey]);

            if (LoadFactor >= 1.5) 
                FixHashTable();
        }
        public V this[K key] {
            get { return Table[Hash(key, this.Height)].value; }
        }
        public void Remove(int key) {
            if (LoadFactor < 0.5) {
                
            }
        }

        private int Hash(K KeyTohash, int Height) {
            Byte[] buff = GetBytes(KeyTohash);
            int ByteCapacity = 4;
            int buff2 = BitConverter.ToInt32(buff, buff.Length - ByteCapacity);
            return buff2 % Height;
        }
        private byte[] GetBytes(object obj){
            BinaryFormatter bf = new BinaryFormatter();
            using (var ms = new MemoryStream()){
                bf.Serialize(ms, obj);
                return ms.ToArray();
            }
        }

        private void FixHashTable(){
            ChainPart[] FixedTable = new ChainPart[Height * 2];
            
            for(int i = 0; i < Height; i++) {
                ChainPart Current = Table[i];
                while (Current != null) {
                    K Currentkey = Current.key;
                    FixedTable[Hash(Currentkey, Height*2)] = new ChainPart(Currentkey, Table[i].value, FixedTable[Hash(Currentkey, Height*2)]);
                    
                    Current = Current.next;
                }        
            }
            this.Table = FixedTable;
        }
    }
}
