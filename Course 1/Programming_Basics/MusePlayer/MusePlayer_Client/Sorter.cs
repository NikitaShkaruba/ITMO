using System;
using System.Collections.Generic;
using System.Linq;

namespace MusicPlayer_ClientSide {
    class Sorter {
        private List<Song> QuickSort(List<Song> collection) {
            if (collection.Count == 1) {
                return collection;
            }    
            if (collection.Count != 1) {
                int key = collection.Count/2;
                List<Song> result = new List<Song>();
                result.Add(collection[key]);

                for (int i = 0; i < collection.Count(); i++) {
                    if (collection[i].CompareTo(collection[key]) == -1) {
                        result.Insert(0, collection[i]);
                    }
                    if (collection[i].CompareTo(collection[key]) == 1) {
                        result.Add(collection[i]);        
                    }
                    if (key == i)
                        continue;
                }
                List<Song> Left = QuickSort(result.Take(key).ToList());
                List<Song> Right = QuickSort(result.Skip(key).ToList());
                result = Left.Union(Right).ToList();
                
                return result;
            }
            
            return collection;
        }
        private void Compare() {
            throw new NotImplementedException();
        }
    }
}
