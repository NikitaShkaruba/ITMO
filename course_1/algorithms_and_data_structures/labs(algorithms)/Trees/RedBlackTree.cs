using System;
using System.IO;

// Author: me
namespace Algorithms.Trees { 

    // *************************************** Mighty Red-Black tree Rules ******************************************* //
    // * 1. A node is either red or black.                                                                           * //
    // * 2. The root is black.                                                                                       * //
    // * 3. All leaves (NIL) are black.                                                                              * //
    // * 4. Every red node must have two black child nodes.                                                          * //
    // * 5. Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes. * //
    // *************************************************************************************************************** //
    
    class RedBlackTree : ITree {
        class Node {
		public int key { get; set; }
		public Color color { get; set; } 
		public Node Grandpa { 
            get { 
                if (Parent == null)
                    return null;
                else return Parent.Parent; 
            } 
        }
		public Node Uncle { 
            get{
                if (this.Grandpa == null) 
                    return null;
                else return (Grandpa.Left == this.Parent) ? Grandpa.Right : Grandpa.Left;
            } 
        }
		public Node Parent { get; set; }
		public Node Left { 
			get{ return _left; }
			set{                 
                if (_left != null)
                    _left.Parent = null;
                
                _left = value;
                if (value != null)
                    value.Parent = this;
			}
		}
        public Node Right { 
			get { return _right; } 
			set { 
                if (_right != null)
                    _right.Parent = null;
                
                _right = value;
                if (value != null)
                    value.Parent = this;
			}
		}

        public Node(int key) {
            this.key = key;
            this.color = Color.Red;
        }
        public Node(int key, Color color) {
			this.key = key;
			this.color = color;
        }
    
		public override string ToString() {
            return this.key + "(" + this.color.ToString() + ")";
        }
        
        private Node _left = null;
		private Node _right = null;
    }
        
        private Node Root = null;
        public RedBlackTree(string filePath) {
			using (StreamReader reader = File.OpenText(filePath))
                while (!reader.EndOfStream)
                    Grow(Int32.Parse( reader.ReadLine()), Root);
        }
        public RedBlackTree(int[] keys) {
			for (int i = 0; i < keys.Length; i++) 
				Grow(keys[i], Root);
        }
		
        private void Grow(int key, Node Gazed) {
			if (Gazed == null)
				Root = new Node(key, Color.Black);
			else {
				if (key >= Gazed.key) {
					if (Gazed.Right == null) {
						Gazed.Right = new Node(key);
						FixRedBlackProperties(Gazed.Right);
					}
                    else Grow(key, Gazed.Right);
				} else {
					if (Gazed.Left == null) {
						Gazed.Left = new Node(key);
						FixRedBlackProperties(Gazed.Left);
					}
                    else Grow(key, Gazed.Left);
				}
			}
        }
        public void Insert(int key) {
            this.Grow(key, Root);
        }
        public void Remove(int key) {
            throw new NotImplementedException();
        }
        public bool Search(int value) {
            return Search(value, Root);
        }
        private bool Search(int key, Node gazing){
            if (gazing == null) return false;
            if (key < gazing.key)
                return Search(key, gazing.Left);
            if (key > gazing.key)
                return Search(key, gazing.Right);
            if (gazing.key == key)
                return true;
            return true;
        }

        private void FixRedBlackProperties(Node Current) {
			
            // ******************************************************************** Mighty Fix Cases ********************************************************* //
            // ** case1: N is the root node, i.e., first node of red–black tree                                                                             ** //
            // ** case2: N's parent (P) is black                                                                                                            ** //
            // ** case3: N's parent (P) and uncle (U) are red                                                                                               ** //
            // ** case4: N is added to right of left child of grandparent, or N is added to left of right child of grandparent (P is red and U is black)    ** //
            // ** case5: N is added to left of left child of grandparent, or N is added to right of right child of grandparent (P is red and U is black)    ** //
            // *********************************************************************************************************************************************** //

            if (Current.Parent == null) {
				//Insert case1
                Current.color = Color.Black;
                return;
            } else { 
				//Insert case 2
				if (Current.Parent.color == Color.Black)
					return;
				else {
					//Insert case 3
					if (Current.Uncle != null && Current.Uncle.color == Color.Red) {
						Current.Parent.color = Color.Black;
						Current.Uncle.color = Color.Black;
						Current.Grandpa.color = Color.Red;
						FixRedBlackProperties (Current.Grandpa);
					} else {
						//Insert case 4
						if (Current == Current.Parent.Right && Current.Parent == Current.Grandpa.Left) {
							RotateLeft(Current);
							Current = Current.Left;
						} else if (Current == Current.Parent.Left && Current.Parent == Current.Grandpa.Right) {
							RotateRight(Current);
							Current = Current.Right;
						}
						//Insert case 5 {}{}{}{ Corrupted }{}{}{}
						Current.Parent.color = Color.Black;
						Current.Grandpa.color = Color.Red;

						if (Current == Current.Parent.Left) // Current.Dad == current.Grandddad.left
							RotateRight (Current.Parent);
						else
							RotateLeft (Current.Parent);
					}
				}
            }
        }
        private void RotateLeft(Node Center) {
			Node SavedParent = Center.Parent;
            Node UnforgotenChild = Center.Left;
            Node Grandpa = Center.Grandpa;

            if (Center.Grandpa == null) Root = Center;
            else {
                if (SavedParent == Center.Grandpa.Left)
                    Center.Grandpa.Left = Center;
                else    
                    Center.Grandpa.Right = Center;
            }

            Center.Left = SavedParent;
            SavedParent.Right = UnforgotenChild; 
            if (Center != Root && Center.Parent == null)
                Center.Parent = Grandpa;
        }
		private void RotateRight(Node Center) { 
		    Node SavedParent = Center.Parent;	
            Node UnforgottenChild = Center.Right;
            Node Grandpa = Center.Grandpa;

            if (Center.Grandpa == null) Root = Center;
            else { 
                if (SavedParent == Center.Grandpa.Left)
                    Center.Grandpa.Left = Center;
                else 
                    Center.Grandpa.Right = Center;
            }

            Center.Right = SavedParent;
            SavedParent.Left = UnforgottenChild;
            if (Center != Root && Center.Parent == null)
                Center.Parent = Grandpa;
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

    public enum Color : byte { Black = 0, Red = 1 }
}