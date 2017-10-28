#include <iostream>
#include <stack>
using namespace std;

class Node {
	int id; // unique value
	char symbol;
	string data;
	Node *child;
	int child_count;
public:
	Node() { id = 0; symbol = ' '; data = ""; child = NULL; child_count = 0; }

	void set_id(int i) { id = i; }

	void set_children() { child = new Node[4]; }

	void set_child(Node* c, int i) {
		if(child == NULL)
			child = c;
		else
			child[i] = *c;
		child_count++;
	}

	void set_symbol(char s) { symbol = s; }

	void set_data(string d) { data = d; }

	void deallocate_ptr() { delete [] child; }

	int get_id() { return id; }

	Node* get_child() { return child; }

	Node get_one_child(int i) { return child[i]; }

	char get_symbol() { return symbol; }

	string get_data() { return data; }

	int get_child_count() { return child_count; }
};

bool has_kids(Node n) {
	return (n.get_child() != nullptr) ? true: false;
}

void local_info(Node n) {
	cout << "\n(Node: " << n.get_id() << " Symbol: '" << n.get_symbol() << "' Data: " << n.get_data() << ")";
}

void print_tree(Node n) {
	//for internal node
	if(has_kids(n)) {
		cout << "(";
		local_info(n);
		for(int i = 0; i < n.get_child_count(); i++)
			print_tree(*(n.get_child() + i));
		cout << "\n)";
	}
	//for leaf nodes
	else {
		local_info(n);
	}
}


////////////////////////////////////////////////////////////////////
// BELOW 3 FUNCTIONS IS FOR BUILDING THE PST, NEED HELP WITH THAT //
////////////////////////////////////////////////////////////////////


//int ROWS, COLS;
//bool parser_table[ROWS][COLS];

//bool top_is_term() {
//	bool result = 0;
//	return result;
//}

//Node reverse(Node rn) {
//	Node r;
//	return r;
//}

///*
// * Builds and outputs a PST of Node objects
// */
//void parse_machine(Node root) {
//	int top, front;
//	stack<Node> pst;
//	pst.push(root);
//	while(!pst.empty()) {
//		if(top == front)
//			pst.pop();
//		else {
//			if(top_is_term())
//				cerr << "Error";
//			else {
//				bool cell = 0;//parser_table[ROWS][COLS];
//				if(!cell)
//					cerr << "Error";
//				else {
//					pst.pop();
//					//pst.push(reverse(cell.RHS));
//				}
//			}
//		}
//	}
//	print_tree(root);
//}

int main() {
	Node n, a, x;
	n.set_id(1);	n.set_symbol(';');	n.set_data("semi");
	a.set_id(5);	a.set_symbol('i');	a.set_data("Ax");
	x.set_id(2);	x.set_symbol(':');	x.set_data("colon");
	Node* d = &a;
	Node* t = &x;
	n.set_children();
	n.set_child(d, 0);
	n.set_child(t, 1);
	print_tree(n);
	n.deallocate_ptr();
}
