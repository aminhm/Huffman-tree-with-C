#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class Node
{
	Node * Parrent, *Right_children, *Left_children;
	int content, key, bit;
public:
	Node() {
		Parrent = NULL;
		Right_children = NULL;
		Left_children = NULL;
	}
	Node(int value,int abundance):content(value),key(abundance) {
		Parrent = NULL;
		Right_children = NULL;
		Left_children = NULL;
	}
	int Bit() {
		return bit;
	}
	int Content() {
		return content;
	}
	int Key() {
		return key;
	}
	void bit_set(int bit_sign) {
		this->bit = bit_sign;
	}
	void value_set(int value) {
		this-> content = value;
	}
	void abundance_set(int abundance) {
		this->key = abundance;
	}
	void parrent_set(Node *parrent) {
		this->Parrent = parrent;
	}
	void left_children_set(Node *left_children) {
		this->Left_children = left_children;
	}
	void right_children_set(Node *right_children) {
		this->Right_children = right_children;
	}
	Node * Left_Child_value() {
		return Left_children;
	}
	Node * Right_child_value() {
		return Right_children;
	}
	Node * Parrent_value() {
		return Parrent;
	}
};
int Parrent_function(int child_pointer) {
	if (child_pointer % 2 == 0) {
		child_pointer -= 1;
	}
	return child_pointer / 2;
}
int RightChildren_function(int child_pointer) {
	return ((child_pointer) * 2) + 2;
}
int LeftChildren_function(int child_pointer) {
	return ((child_pointer) * 2) + 1;
}
void Insertion(Node **array, int i) {
	while ((i > 0) && (array[i]->Key() < array[Parrent_function(i)]->Key())) {
		Node *temp = array[i];
		array[i] = array[Parrent_function(i)];
		array[Parrent_function(i)] = temp;
		i = Parrent_function(i);
	}
}
void Min_Heapify(Node **values, int len, int i) {
	int littlechild;
	int l = LeftChildren_function(i);
	int r = RightChildren_function(i);
	if ((l < len) && (values[l]->Key() < values[i]->Key()))
		littlechild = l;
	else
		littlechild = i;
	if (r < len && values[r]->Key() < values[littlechild]->Key())
		littlechild = r;
	if (littlechild != i) {
		Node *c = values[i];
		values[i] = values[littlechild];
		values[littlechild] = c;
		Min_Heapify(values, len, littlechild);
	}
}
void Build_Heap(int input, Node **nodes) {
	for (int i = input / 2; i >= 0; i--) {
		Min_Heapify(nodes, input, i);
	}
}
void pre_order(Node *array,ofstream &file) {
	if (array->Content()>=0)
	{
		Node *temp = new Node;
		temp = array  ;
		int c[100];
		int i = 0;
		do {
			c[i] = temp->Bit();
			temp = temp->Parrent_value();
			i += 1;
		} while (temp->Parrent_value() != NULL);
		file << array->Content() << "\t";
		file << i << "\t";
		char *n = (char *)malloc(i * sizeof(char));
		for (int k  = 0; k < i; k++)
		{
			file << c[i-k-1];
		}
		file << "\n";
	}
	else {
		pre_order(array->Left_Child_value(),file);
		pre_order(array->Right_child_value(),file);
		return;
	}
}
int main() {
	char ch;
	int input = 0;
	char find;
	int length = 0;
	ifstream file("input.txt");
	int p = 0;
	char c[50];
	while (!file.eof())
	{
		file.get(ch);
		c[p] = ch;
		p += 1;
	}
	p -= 1;
	file.close();
	char values[200];
	int abundance[200];
	for (int j = 0; j < p; j++) {
		find = c[j];
		for (int k = j + 1; k < p;) {
			if (c[k] == '_')
				k++;
			else if (find == c[k]) {
				length += 1;
				c[k] = '_';
				k++;
			}
			else
				k++;
		}
		if (c[j] != '_') {
			values[input] = c[j];
			abundance[input] = length + 1;
			input += 1;
		}
		length = 0;
	}
	values[input] = 0;
	abundance[input] = 0;
	input += 1;
	Node ** nodes = (Node **)malloc(input * sizeof(Node));
	for (int i = 0; i < input; i++) {
		Node * temp = new Node;
		temp->value_set(values[i]);
		temp->abundance_set(abundance[i]);
		nodes[i] = temp;
	}
	Build_Heap(input,nodes);
	Node **huffman_nodes = (Node **)(malloc(input * sizeof(Node)));
	for (int i = 0; i < input; i++) {
		huffman_nodes[i] = nodes[i];
	}
	int inputed = input - 1;
	    for (int i=0; i<input-1;i++) {
	        Node *new_node=new Node;
			Node *temp1 = new Node;
			temp1=huffman_nodes[0];
	        huffman_nodes[0]=huffman_nodes[inputed];
	        inputed-=1;
	        Min_Heapify(huffman_nodes,inputed,0);
			Node *temp2 = new Node;
			temp2=huffman_nodes[0];
	        huffman_nodes[0]=huffman_nodes[inputed];
	        inputed-=1;
	        Min_Heapify(huffman_nodes,inputed,0);
			new_node->abundance_set(temp1->Key() + temp2->Key());
	        new_node->value_set(-1 - i);
			temp1->bit_set(0);
			temp2->bit_set(1);
			new_node->left_children_set(temp1);
			new_node->right_children_set(temp2);
			temp1->parrent_set(new_node);
			temp2->parrent_set(new_node);
	        inputed+=1;
	        huffman_nodes[inputed]=new_node;
	        Insertion(huffman_nodes,inputed);
	    }
		std::ofstream outfile;
		outfile.open("Huffman.txt", ios::out |ios::app);
		char bits[1000];
	        pre_order(huffman_nodes[0],outfile);
			outfile.close();
			ifstream out("Huffman.txt");
			char _ch;
			char _c[1000];
			int _p = 0;
			while (!out.eof())
			{
				out.get(_ch);
				_c[_p] = _ch;
				_p += 1;
			}
			_p -= 1;
			out.close();
			int index = 0;
			int y = 0;
			while (y!=_p)
			{
				int result = 0;
				if (_c[y]=='\t')
				{
					while (true)
					{
						y += 1;
						if (_c[y]=='\t')
						{
							y += 1;
							while (_c[y]!='\n')
							{
								bits[index] = _c[y];
								result = 1;
								index += 1;
								y += 1;
							}
							if (result==1)
							{
								break;
							}
						}
					}
				}
				else
				{
					y += 1;
				}
			}
			while(index%8!=0)
			{
				bits[index] = '0';
				index += 1;
			}
			int num = 0;
			std::ofstream infile;
			infile.open("Zip.txt", ios::out | ios::app);
			while (num!=index)
			{
				char result [8];
				for (int o = 0; o < 8; o++) {
					result[o] = bits[num];
					num += 1;
				}
				int character = atoi(result);
				infile << (char)character;
			}
			infile.close();
			//// Second problem
			//ifstream path;
			//path.open("Zip.txt",ios::in |ios::binary);
			//char __ch;
			//int __p = 0;
			//int elements;
			//char __c[50];
			//while (!path.eof())
			//{
			//	path.get(__ch);
			//	__c[__p] = __ch;
			//	__p += 1;
			//}
			//__p -= 1;
			//for (int n = 0; n < p; n++)
			//{
			//	int element=(int)__c[n];
			//	char bi[200];
			//	
			//	//elements = (int)__c[n];
			//	//char *bi = (char *)malloc(200 * sizeof(char));
			//	//itoa(elements, bi, 10);
			//	//printf("%s", bi);
			//}
			//path.close();
			//input.open("Zip.txt", ios::binary);
	getchar();
	printf("\n");
	return 0;
}