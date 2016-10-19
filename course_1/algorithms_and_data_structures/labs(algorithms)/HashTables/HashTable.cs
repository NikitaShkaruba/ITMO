using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

// Author: Danya
namespace Algorithms.Trees
{
      internal class LinkedDictionaryEnumerator<TKey,TValue> : IEnumerator<KeyValuePair<TKey, TValue>>
          where TKey : IEquatable<TKey>
        {
          public LinkedDictionary<TKey, TValue> linkedDictionary;
          internal LinkedDictionaryEnumerator(LinkedDictionary<TKey,TValue> linkedDictionary)
            {
                this.linkedDictionary = new LinkedDictionary<TKey,TValue>();
                this.linkedDictionary.next = linkedDictionary;
            }

            public KeyValuePair<TKey, TValue> Current
            {
                get
                {
                    return new KeyValuePair<TKey, TValue>(linkedDictionary.key, linkedDictionary.value);
                }
            }
            public bool MoveNext()
            {
                if (linkedDictionary.next == null)
                    return false;
                linkedDictionary = linkedDictionary.next;
                return true;
            }
            public void Reset(){}

            public void Dispose()
            {
                linkedDictionary = null;
            }

            object System.Collections.IEnumerator.Current
            {
                get { return new KeyValuePair<TKey, TValue>(linkedDictionary.key, linkedDictionary.value); }
            }
        }

    class LinkedDictionary<TKey, TValue>
        where TKey : IEquatable<TKey>
    {
        public TKey key;
        internal TValue value;
        internal LinkedDictionary<TKey, TValue> next;

        public LinkedDictionary()
        {
            next = null;
        }
        public LinkedDictionary(TKey key, TValue value)
        {
            this.key = key;
            this.value = value;
            next = null;
        }

        public void Add(TKey key, TValue value)
        {
            if (key.Equals(this.key))
                return;
            if (next == null)
            {
                next = new LinkedDictionary<TKey, TValue>(key, value);
                return;
            }
            next.Add(key, value);
        }
        public void Add(KeyValuePair<TKey, TValue> pair)
        {
            Add(pair.Key, pair.Value);
        }
        private bool SearchKey(TKey key)
        {
            if (this.key.Equals(key))
                return true;
            if (next == null)
                return false;
            return next.SearchKey(key);
        }
        public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator()
        {
            return new LinkedDictionaryEnumerator<TKey,TValue>(this);
        }

    }

    class HashTable<TKey, TValue> where TKey : IEquatable<TKey>
    {
        public const double defaultThreshold = 3.1415926535;
        public double threshold;
        long count;
        LinkedDictionary<TKey,TValue>[] list;

        private static long ObjectToInt64(object obj)
        {
            long result;
            BinaryFormatter bf = new BinaryFormatter();
                using (MemoryStream ms = new MemoryStream())
                {
                    bf.Serialize(ms, obj);
                    while (ms.Length < 8)
                        ms.WriteByte(0);
                    ms.Position -= 8;
                    using (BinaryReader br = new BinaryReader(ms))
                        result = br.ReadInt64();
                }
                if (result < 0)
                    result = -result;
                return result;
        }
        private static long GetHash(object obj)
        {
            return (ObjectToInt64(obj) % 2147483647);
        }
        
        public long GetIndexWithHash(object obj)
        {
            return (GetHash(obj) % list.LongLength);
        }


        private static LinkedDictionary<TKey, TValue>[] CreateLinkedDictionaryArray(long size)
        {
            var result = new LinkedDictionary<TKey, TValue>[size];
            for (long i = 0; i < size; i++)
                result[i] = new LinkedDictionary<TKey, TValue>();
            return result;
        }

        private HashTable()
        {
            threshold = defaultThreshold;
            count = 1;
            list = CreateLinkedDictionaryArray(count);
        }
        public HashTable (long size = 1, double threshold = defaultThreshold)
        {
            count = size;
            list = CreateLinkedDictionaryArray(count);
            this.threshold = threshold;
        }
        public HashTable(IDictionary<TKey, TValue> pairs)
        {
            count = pairs.Count;
            list = CreateLinkedDictionaryArray(count);
            threshold = defaultThreshold;
            foreach (var pair in pairs)
                Add(pair);
        }
        public static HashTable<TKey,long> CreateForSearch(TKey[] objects)
        {
            var searchingHashTable = new HashTable<TKey,long>(objects.LongLength);

            for (long index = 0; index < objects.LongLength; index++)
                searchingHashTable.Add(objects[index], index);

            return searchingHashTable;
        }

        public void Add(TKey key, TValue value)
        {
            list[GetIndexWithHash(key)].Add(key, value);
            ExpandIfNeeded();
        }
        public void Add(KeyValuePair<TKey,TValue> pair)
        {
            Add(pair.Key, pair.Value);
        }

        private void ExpandIfNeeded()
        {
            if (((double)++count / (double)list.LongLength) > threshold)
                Expand();
        }
        private void Expand()
        {
            LinkedDictionary<TKey, TValue>[] newLinkedDictionary = CreateLinkedDictionaryArray(list.LongLength*2);
            foreach (var linkedDictionary in list)
                foreach (var pair in linkedDictionary)
                    newLinkedDictionary[GetIndexWithHash(pair.Key)].Add(pair.Key, pair.Value);
            list = newLinkedDictionary;
        }

        public TValue Search(TKey key)
        {
            foreach (var pair in list[GetIndexWithHash(key)])
                if (key.Equals(pair.Key))
                    return pair.Value;
            return default(TValue);
        }
        

    }
}
