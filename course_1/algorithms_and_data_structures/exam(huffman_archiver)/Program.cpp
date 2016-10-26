#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <stack>
#include <regex>
#include <map>
using namespace std;

// Hello guys. I really should put one advice here before all the code. 
// My main advice: Go to gitHub documentation if you miss something and you don't understand algorithm!
// Use test() Method in main() if you don't want to bother yourself with command line
// My gitHub: https://github.com/SigmaOne/HuffmanCompress

namespace Huffman {	
	class HuffTree {
	public:
		HuffTree() : word(""), enters(0), Left(nullptr), Right(nullptr) {}
		HuffTree(char _word, int _enters) : Left(nullptr), Right(nullptr), word(1,_word), enters(_enters) {}
		HuffTree(HuffTree* l, HuffTree* r) : Left(l), Right(r) {
			word = l->word + r->word;
			enters = l->enters + r->enters;
		}
		~HuffTree() {
			if (Right != nullptr)
				delete Right;
			if (Left != nullptr)
				delete Left;
		}

		bool isLeaf() {
			return (word.size() == 1);
		}
		bool operator< (const HuffTree &right) { return enters < right.enters; }
		bool operator<= (const HuffTree &right) { return enters <= right.enters; }
		bool operator>(const HuffTree &right) { return enters > right.enters; }
		bool operator>= (const HuffTree &right) { return enters >= right.enters; }

		HuffTree *Right;
		HuffTree *Left;
		string word; // single char or word with childs to chars
		int enters;
	};
	class HuffCode {
	private:
		long rPointer = 0; // read pointer, points on next bit in raw str
		short wPointer = 8; // write pointer, points on next bit in new byte
		char byte = 0u;	// next byte to be written
		string str;

	public:
		HuffCode() : str("") { 
			// Warning! Hard Logic! These bytes is reserved for some Tree Metadata(I do need them for unpacking tree)
			str += (char)0u; // for (short) nodeCount last (8) bits 
			str += (char)0u; // for (short) nodeCount first (8) bits
			str += (char)0u; // for (char) fakeCount (8) bits
		}
		HuffCode(string code) : str(code) {}

		void PutTree(HuffTree *head) {
			short nodeCount = 0;

			// code up tree with postorder traversal
			stack<HuffTree*> stack;
			stack.push(head);
			while (!stack.empty()) {
				HuffTree* next = stack.top();
				if (next->Right == head || next->Left == head || next->isLeaf()) {
					nodeCount++;
					stack.pop();

					if (next->isLeaf()) {
						// write 1(bit) if leaf
						PutBit(1u);
						// then write symbol
						for (size_t i = 8; i > 0; i--)
							PutBit((next->word[0] >> i - 1) & 1u);
					}
					else // write 0(bit) if node
						PutBit(0u);

					head = next;
				}
				else {
					if (next->Right != NULL)
						stack.push(next->Right);
					if (next->Left != NULL)
						stack.push(next->Left);
				}
			}
			// fill reserved bytes
			str[0] = (char)(nodeCount >> 8);
			str[1] = (char)(nodeCount);
		}
		void PutBit(char bit) {
			switch (bit) {
				case 0: byte |= (0u << wPointer-- - 1); break;
				case 1: byte |= (1u << wPointer-- - 1); break;
				default: throw new exception("Bit is only 0\1 ;("); break;
			}

			// if byte completed, write it.
			if (wPointer == 0) {
				wPointer = 8;
				str += byte;
				byte = 0u;
			}
		}

		char getBit() {
			return (str[rPointer / 8] >> (7 - (rPointer++ % 8))) & 1u;
		}
		char getByte() {
			char result = 0u;
			for (size_t i = 0; i < 8; i++)
				result = (result << 1) | getBit();

			return result;
		}
		void fillLastByte() {
			// filling reserved byte which says how much fake symbols we have in the end.
			str[2] = (unsigned char)wPointer;
			// and fill last byte
			while (wPointer != 8)
				PutBit(0u);
		}

		long bitReaded() {
			return rPointer;
		}
		string asString() {
			return str;
		}
	};

	string ReadFileBytes(string path) {
		// read file
		fstream fileToEncode(path, std::ios::in | std::ios::binary | std::ios::ate);
		if (!fileToEncode.is_open()) {
			std::cout << "sht, can't open :(";
			return "";
		}

		size_t size = fileToEncode.tellg();
		char* buffer = new char[size];
		fileToEncode.seekg(0, std::ios::beg);
		fileToEncode.read(buffer, size);
		fileToEncode.close();
		
		return string(buffer, size);
	}
	map<char, vector<bool>> CodeTraversal(HuffTree *root) {
		map<char, vector<bool>> codeTable;
		vector<bool> currentCode;

		stack<pair<HuffTree*, vector<bool>>> s; // stack name is "s" coz of algorithm minimalizm
		HuffTree *current = root;
		while (!s.empty() || current != NULL) {
			if (current != NULL) {
				s.push({ current, currentCode });
				// go to left child, add '0' to code
				currentCode.insert(currentCode.end(), 0);
				current = current->Left;
			} else {
				current = s.top().first;
				currentCode = s.top().second;
				s.pop();

				if (current->isLeaf())
					codeTable.insert({ current->word[0], currentCode });

				// go to right child, add '1' to code
				currentCode.insert(currentCode.end(), 1);
				current = current->Right;
			}
		}
		return codeTable;
	}
	
	template<typename T, bool Compare(T left, T right)> 
	class Heap {
	private:
		size_t count;
		size_t memory;
	public:
		T* arr;
		Heap() : arr(NULL), count(0), memory(16) {}
		~Heap() {
			this->clear();
		}

		bool empty(void) const { return (!count); }
		size_t size(void) const { return count; }

		bool push(T value) {
			size_t current, parent; 

			if (!this->_alloc())
				return false;
			arr[count] = value;

			current = count++;
			parent = (current == 0) ? 0 : (current - 1) >> 1;

			// reverse heapify
			while ((current > 0) && Compare(arr[current], arr[parent])) {
				T buf = arr[current];
				arr[current] = arr[parent];
				arr[parent] = buf;

				current = parent--;
				if (current == 0)
					break;
				parent >>= 1;
			}
			return true;
		}
		T pop() {
			if (count > 0) {
				T buff = arr[0];
				arr[0] = arr[--count];
				this->_heapify(0);
				return buff;
			} else {
				count = 0;
				return NULL;
			}
		}
		T peek() {
			if (count > 1)
				return arr[0];
			else return NULL;
		}
		void clear() {
			if (arr != NULL)
				delete[] arr;
			arr = NULL;
			count = 0;
			memory = 16;
		}

	private:
		bool _alloc(void) {
			size_t newMemory;
			T* newArr;

			if (arr == NULL) {
				arr = new T[memory];
				if (arr == NULL)
					return false;
			}

			// If memory dried up
			if ((count + 1) >= memory) {
				newMemory = count * 2;
				newArr = new T[newMemory];
				if (newArr == NULL)
					return false;
				for (size_t i = 0u; i < count; i++)
					newArr[i] = arr[i];
				delete[] arr;
				arr = newArr;
				memory = newMemory;
			}
			return true;
		}
		void _heapify(size_t index) {
			size_t l, r, small;

			while (true) {
				l = (index << 1) + 1u;
				r = (index << 1) + 2u;

				// Who's the smallest?
				if ((l < count) && Compare(arr[l], arr[index]))
					small = l;
				else
					small = index;
				if ((r < count) && Compare(arr[r], arr[small]))
					small = r;

				if (small != index) {
					T buffer = arr[index];
					arr[index] = arr[small];
					arr[small] = buffer;
					index = small; // And go down
				}
				else
					break;
			}
		}
	};
	bool IsLeftLower(HuffTree* a, HuffTree* b) {
		// pointer content comparer
		return (a->enters) < (b->enters);
	}

	string Encode(string rawStr) {
		HuffCode result;
		
		// 1. count symbols
		std::map<char, int> charEntries;
		for (size_t i = 0; i < rawStr.size(); i++) {
			if (charEntries.count(rawStr[i]) == 0)
				charEntries.insert(pair<char,int> { rawStr[i], 1 });
			else
				charEntries[rawStr[i]]++;
		}

		// 2. create a tree
		Heap<HuffTree*, IsLeftLower> myhep;
		for each (pair<char, int> pr in charEntries) 
			myhep.push(new HuffTree(pr.first, pr.second));
		while (myhep.size() > 1)
			myhep.push(new HuffTree(myhep.pop(), myhep.pop()));

		// 3. get a code table
		HuffTree* root = myhep.pop();
		map<char, vector<bool>> CodeTable = CodeTraversal(root);
		if (CodeTable.size() == 1)
			CodeTable.begin()->second = vector<bool> {false};
		
		// 4. compress Huffman tree to a huffman string
		result.PutTree(root);
		delete root;

		// 5. code input string with new alphabet
		for (size_t i = 0; i < rawStr.size(); i++)
			for each (bool bit in CodeTable[rawStr[i]])
				result.PutBit(bit);

		// 6. fill last byte
		result.fillLastByte();

		// 7. return encoded string
		return result.asString();
	}
	string Decode(string rawStr) {
		HuffCode code(rawStr);
		string result;

		// 1. get HuffTree's child count
		short size = ((unsigned char)code.getByte() << 8) + ((unsigned char)code.getByte());

		// 2. get fake bit's count
		short fakeCount = (unsigned char)code.getByte();

		// 3. get HuffTree using Reverse Polish notation
		std::stack<HuffTree*> stacky;
		while (size-- != 0) {
			switch (code.getBit()) {
				case 1u: { // 1 means that next 8 bit's is node leaf symbol
					HuffTree *next = new HuffTree(code.getByte(), 0);
					stacky.push(next);
					break;
				}
				case 0u: { // 0 means that we're in Node, so let's create it then
					HuffTree *Right = stacky.top();
					stacky.pop();
					HuffTree *Left = stacky.top();
					stacky.pop();

					HuffTree *merged = new HuffTree(Left, Right);
					stacky.push(merged);
					break;
				}
			}
		}

		// 4.1 decode string with new alphabet!		
		HuffTree *root = stacky.top();
		HuffTree *gaze = root;
		stacky.pop(); // bye

		if (!root->isLeaf()) {
			// normal case
			do {
				switch (code.getBit()) {
					case 0u: gaze = gaze->Left; break;
					case 1u: gaze = gaze->Right; break;
				}
				if (gaze->isLeaf()) {
					result += gaze->word;
					gaze = root;
				}
			} while (code.bitReaded() != rawStr.size() * 8 - fakeCount);
		}
		else {
			// narrow case
			while (code.bitReaded() != rawStr.size() * 8 - fakeCount) {
				code.getBit();
				result += gaze->word;
			}
		}

		// 5. return result
		delete root;
		return result;
	}
}
void Test() {
	using namespace Huffman;
	std::cout.precision(1);

	// Encode
	string filepath = "One hundred years of solitude.txt";
	cout << "Encode*" << endl;
	fstream inFile(filepath, std::ios::in | std::ios::binary | std::ios::ate);
	std::cout << "Before huffing: " << inFile.tellg() << " bytes = " << (float)inFile.tellg() / 1048576.0 << " Megabytes." << endl; 
	inFile.close();
	
	string rawStr = ReadFileBytes(filepath);
	string result = Huffman::Encode(rawStr);

	string outPath = "One hundred years of solitude.huf";
	fstream outFile(outPath, std::ios::out | std::ios::binary | std::ios::ate);
	outFile << result;
	std::cout << "Compressed: " << outFile.tellg() << " bytes = " << (float)outFile.tellg() / 1048576.0 << " Megabytes." << endl; 
	outFile.close();

	// Decode
	cout << endl << "Decode*" << endl;
	fstream inFile2("One hundred years of solitude.huf", std::ios::in | std::ios::binary | std::ios::ate);
	std::cout << "After huffing: " << inFile2.tellg() << " bytes = " << (float)inFile2.tellg() / 1048576.0 << " Megabytes." << endl; 
	inFile.close();

	rawStr = Huffman::ReadFileBytes("One hundred years of solitude.huf");
	result = Huffman::Decode(rawStr);

	fstream outFile2("One hundred years of solitude(result).txt", std::ios::out | std::ios::binary | std::ios::ate);
	outFile2 << result;
	std::cout << "Before huffing: " << outFile2.tellg() << " bytes = " << (float)outFile2.tellg() / 1048576.0 << " Megabytes." << endl;
	outFile2.close();

	cout << "\npress any key to exit";
	cin >> result;
}
void main(int argc, char *argv[]) {
	using namespace Huffman;
	std::cout.precision(1);
	// Test();
	// return;

	// Command line arguments parsing
	if (argc > 3) {
		if (argv[1] == "-c") {
			if (argv[2] == "-f" || argv[2] == "--file") {
				string content = ReadFileBytes(argv[3]);
				if (content.size() == 0) {
					std::cout << "Can't compress empty file";
					return;
				}

				std::cout << "Uncompressed: " << content.size() << " bytes = " << (float)content.size() / 1048576.0 << " Megabytes." << endl; // rework!
				string result = Encode(content);
				string outPath = "";
				if ((argv[4] == "-o" || argv[4] == "--output") && argv[5])
					outPath = argv[5];
				else {
					int i = 0;
					while (argv[3][i] != '.')
						outPath += argv[3][i++];
					outPath += ".huf";
				}
				fstream outFile(outPath, std::ios::out | std::ios::binary | std::ios::ate);
				outFile << result;
				std::cout << "Compressed: " << outFile.tellg() << " bytes = " << (float)outFile.tellg() / 1048576.0 << " Megabytes." << endl; // rework!
				outFile.close();
			}
			else
				std::cout << "Wrong format. Try -h key for help";
		}
		if (argv[1] == "-u") {
			if (argv[2] == "-f" || argv[2] == "--file") {
				string content = ReadFileBytes(argv[3]);
				if (content.size() == 0) {
					std::cout << "Can't uncompress empty file";
					return;
				}

				std::cout << "Compressed: " << content.size() << " bytes = " << (float)content.size() / 1048576.0 << " Megabytes." << endl; // rework!
				string result = Decode(content);
				string outPath = "";
				if ((argv[4] == "-o" || argv[4] == "--output") && argv[5])
					outPath = argv[5];
				else
					std::cout << "Wrong format. Try -h key for help";
				fstream outFile(outPath, std::ios::out | std::ios::binary | std::ios::ate);
				outFile << result;
				std::cout << "Uncompressed: " << outFile.tellg() << " bytes = " << (float)outFile.tellg() / 1048576.0 << " Megabytes." << endl; // rework!
				outFile.close();
			}
			else
				std::cout << "Wrong format. Try -h key for help";
		}
		if (argv[1] == "-h" || argv[1] == "--help")
			std::cout << "Command format: HuffmanCompress [-c|-u] [-f|--file] filepath.txt [-o|--output] outpath.huf";
		else
			std::cout << "Wrong format. Try -h key for help";
	}
	else
		std::cout << "Wrong format. Try -h key for help";
}