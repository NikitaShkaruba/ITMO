using System;

// Author: Nikitos
namespace Sorts
{
	public class BNode
	{
		int key;
		public int content;
		BNode bro, child, parent;
		int degree;
		public BNode(int k)
		{
			key = k;
			bro = child = parent = null;
			degree = 0;
		}
		public BNode(int k, int c){
			key = k;
			bro = child = parent = null;
			degree = 0;
			this.content = c;
		}
		void decreaseKey(BNode node, int newKey)
		{
			if (newKey < node.key) {
				node.key = newKey;
				node.emersion ();
			}
		}
		void emersion()
		{
			var node = this;
			if ((node.parent != null) && (node.key < node.parent.key)) {
				var t = node.key;
				node.key = node.parent.key;
				node.parent.key = t; // обмен ключами
				node.parent.emersion();
			}
		}
		BNode mergeTrees(BNode head)
		{
			BNode prev = null;
			BNode curr = head;
			BNode next = head.bro;
			while (next != null) {
				if (next.degree != curr.degree ||
					(next.bro != null &&
						curr.degree == next.bro.degree)) {
					prev = curr; curr = next;
				} else if (curr.key < next.key) {
					curr.bro = next.bro;
					next.bro = curr.child;
					curr.child = next;
					next.parent = curr;
					curr.degree++;
				} else {
					if (prev == null) 
						head = next;
					else
						prev.bro = next;
					curr.bro = next.child;
					next.child = curr;
					curr.parent = next;
					next.degree++;
					curr = next;
				}
				next = curr.bro;
			}
			return head;
		}
		BNode mergeHeaps(BNode h1, BNode h2)
		{
			if (h1 == null)
				return h2;
			if (h2 == null)
				return h1;

			BNode head, h;
			if (h1.degree < h2.degree) {
				h = h1;
				h1 = h1.bro;
			} else {
				h = h2;
				h2 = h2.bro;
			}
			head = h;
			while (h1 != null && h2 != null) {
				if (h1.degree < h2.degree) {
					h.bro = h1;
					h = h.bro;
					h1 = h1.bro;
				} else {
					h.bro = h2;
					h = h.bro;
					h2 = h2.bro;
				}
			}
			if (h1 == null)
				while (h2 != null) {
					h.bro = h2;
					h = h.bro;
					h2 = h2.bro;
				}
			if (h2 == null)
				while (h1 != null) {
					h.bro = h1;
					h = h.bro;
					h1 = h1.bro;
				}
			h.bro = null;
			return mergeTrees (head);
		}
		public BNode insert(int key)
		{
			BNode node = new BNode (key);
			return mergeHeaps (this, node);
		}
		public BNode insert(BNode node)
		{
			return mergeHeaps (this, node);
		}
		BNode getMinimum(BNode heap)
		{
			BNode min = heap;
			while (heap.bro != null)
				if (heap.bro.key < min.key) {
					min = heap.bro;
					heap = heap.bro;
				}
			return min;
		}
		public BNode extractMin(out BNode min){
			BNode head = this;
			min = this;
			BNode cur = this;
			BNode prev = null;
			while (cur.bro != null) {
				if (cur.bro.key < min.key) {
					min = cur.bro;
					prev = cur;
				}
				cur = cur.bro;
			}
			if (prev == null)
				head = head.bro;
			else
				prev.bro = min.bro;
			min.bro = null;
			cur = min.child;
			if (cur != null) {
				cur.parent = null;
				cur = inverse (cur, null);
			}
			head = mergeHeaps (head, cur);
			return head;
		}
		BNode rightBefore(BNode heap, BNode before)
		{
			if (heap.bro != before)
				return rightBefore (heap.bro, before);
			else
				return heap;
		}
		BNode inverse(BNode node, BNode before){
			BNode h = rightBefore (node, before);
			if (node == h) {
				h.bro = null;
				return h;
			}
			BNode brother = inverse (node, h);
			h.bro = brother;
			return h;
		}
		public int Key(){
			return this.key;
		}
	}
}
