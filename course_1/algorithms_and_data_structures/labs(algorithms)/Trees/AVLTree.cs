using System;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

// Author: Danya
namespace Algorithms.Trees
{
    class AVLTree : ITree
    {
        public int key;
        public int height;
        private AVLTree left;
        private AVLTree right;

        public AVLTree(int key)
        {
            this.key = key;
            left = null;
            right = null;
            height = 1;
        }
        public static AVLTree Initialize(int[] keys)
        {
            AVLTree result = new AVLTree(keys[0]);
            for (int i = 1; i < keys.Length; i++)
                result = Grow(result, keys[i]);
            return result;
        }

        private static int GetHeight(AVLTree tree)
        {
            return (tree == null) ? 0 : tree.height; 
        }
        private int GetBalanceFactor()
        {
            return GetHeight(this.right) - GetHeight(this.left);
        }
        private void FixHeight()
        {
            int lh = GetHeight(this.left);
            int rh = GetHeight(this.right);
            this.height = (lh > rh) ? lh : rh + 1;
        }

        private AVLTree RotateRight()
        {
            AVLTree result = this.left;
            this.left = result.right;
            result.right = this;
            this.FixHeight();
            result.FixHeight();
            return result;
        }
        private AVLTree RotateLeft()
        {
            AVLTree result = this.right;
            this.right = result.left;
            result.left = this;
            this.FixHeight();
            result.FixHeight();
            return result;
        }
        private AVLTree Balance()
        {
            this.FixHeight();
            if (this.GetBalanceFactor() == 2)
            {
                if (this.right.GetBalanceFactor() < 0)
                    this.right = this.right.RotateRight();
                return this.RotateLeft();
            }
            if (this.GetBalanceFactor() == -2)
            {
                if (this.left.GetBalanceFactor() > 0)
                    this.left = this.left.RotateLeft();
                return this.RotateRight();
            }
            return this;
        }

        public static AVLTree Grow(AVLTree tree, int key)
        {
            if (tree == null)
                return new AVLTree(key);
            if (key < tree.key)
                tree.left = Grow(tree.left, key);
            else
                tree.right = Grow(tree.right, key);
            return tree.Balance();
        }
        public void Insert(int key) {
            // Nick: "wtf!11!!"
            throw new NotImplementedException();
        }
        public bool Search(AVLTree tree, int key)
        {
            if (tree == null)
                return false;
            if (tree.key > key)
                return Search(tree.left, key);
            if (tree.key < key)
                return Search(tree.right, key);
            else return true;
        }
        public bool Search(int key) {
            return Search(this, key);
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
