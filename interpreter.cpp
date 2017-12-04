#include <iostream>
#include <sstream>
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

	void set_children() {
		child = new Node[4];
	}

	void set_child(Node* c, int i) {
		if(child == NULL)
			child = c;
		else
			child[i] = *c;
		child_count++;
	}

	void set_symbol(char s) { symbol = s; }

	void set_data(string d) { data = d; }

	void set_child_count(int cc) { child_count = cc; }

	void deallocate_ptr() {
		delete [] child;
	}

	int get_id() { return id; }

	Node* get_child() { return child; }

	Node get_one_child(int i) { return child[i]; }

	char get_symbol() { return symbol; }

	string get_data() { return data; }

	int get_child_count() { return child_count; }
};

class SCTnode{
	char symtab[10];
public:
	SCTnode(Node n) {
		for(int i = 0; i < 10; ++i) {
			if(symtab[i] == 0) {
				add(n.get_symbol(), i);
				break;
			}
		}
	}

	SCTnode(char c) {
		for(int i = 0; i < 10; ++i) {
			if(symtab[i] == 0) {
				add(c, i);
				break;
			}
		}
	}
	void add(char c, int i) {
		symtab[i] = c;
	}

	char get_table_cell(int i) {
		return symtab[i];
	}
};

//Not done
class Snode {
 
private: 
		map<string, Node> sctMap;
		Snode *kid;
		Snode *parent;
public: 
	Snode() {
		sctMap = NEW hashmap<string, Node>();
	}
	 Snode(Snode parent) {
		sctMap = new hashmap<string, Node>();
		this->parent = parent;
	}

	 map<string, Node> getSCTMap() {
		return sctMap;
	}
	void linkParentToChild(Snode child) {
		this->kid = child;
	}
	 Snode getKid() {
		return kid;
	}
	 Snode getParent() {
		return parent;
	}
};

/**
 * Returns a SCTnode with a symbol from a given node
 */
void find_sym(Node ra) {
	SCTnode s = new SCTnode(ra);
	return s;
}

/**
 * Adds an entry into a symbol table
 */
void add_entry(Node arn, Snode rsn) {
	for(int i = 0; i < 10; ++i) {
		if(rsn[i] == 0) {
			rsn.add(arn.get_symbol(), i);
			break;
		}
	}
}

/**
 * Determines if a node represents a DECL
 */
bool is_decl(Node arn) {
	if(arn.get_data() == 'int' || arn.get_data() == 'float'
	   || arn.get_data() == 'string')
		return true;
	else
		return false;

}

/**
 * Determines if a node represents a block
 */
bool is_block(Node arn) {
	if(arn.get_symbol() == '{')
		return true;
	else
		return false;
}

/**
 * Determines if a node represents a use
 */
bool is_use(Node arn) {
	if(arn.get_symbol() == 'i')
		return true;
	else
		return false;
}

/**
 * Determines if a node represents an operation
 */
bool is_op(Node arn) {
	if(arn.get_symbol() == '+' || arn.get_symbol() == '-'
	|| arn.get_symbol() == '*' || arn.get_symbol() == '/')
		return true;
	else
		return false;
}

/**
 * Performs the operation specified by the node
 */
void do_op(Node arn) {
	int newSym = 0;
	Node n1 = arn.get_one_child(0);
	Node n2 = arn.get_one_child(1);
	stringstream s(n1.get_data());
	stringstream t(n1.get_data());
	int x,y;
	s >> x;
	t >> y;
	char tester = arn.get_symbol();
	switch(tester) {
		case '+':
			newSym = x + y;
			break;
		case '-':
			newSym = x - y;
			break;
		case '*':
			newSym = x * y;
			break;
		case '/':
			newSym = x / y;
			break;
		default:
			newSym = 0;
}

/**
 * Converts a use AST node to a SCT node
 */
void A2S_use(Node ra, Snode rs) {
	SCTnode my_scope = find_sym(ra);
}

/**
 * Converts a block AST node to a SCT node
 */
void A2S_block(Node arn, SCTnode rsn) {
	for(int i = 0; i < 4; ++i)
		AST2SCT(arn.get_one_child(i), rsn);
}

/**
 * Converts a decl AST node to a SCT node
 */	
void A2S_decl(Node arn, SCTnode rsn) {
	add_entry(arn.get_one_child(0), rsn);
	if(is_decl(arn.get_one_child(1)))
		A2S_decl(arn.get_one_child(1), rsn);
}

/**
 * Runs the AST starting with the given root node
 */
void run_AST(Node arn) {
	if(is_decl(arn)) return;
	else if (is_block(arn)) {
		for(int i = 0; i < 4; i++)
			run_AST(arn.get_one_child(i));
	}
	else if (is_use(arn)) {
		char c = arn.get_symbol();
		stringstream c2s;	string s;
		c2s << c;	c2s >> s;
		arn.set_data(s);
	}
	else if (is_op(arn))
		do_op(arn);
}

/**
 * Converts AST to a SCT
 */
void AST2SCT(Node arn, SCTnode rsn) {
	if(arn.get_symbol() == ' ')
		return;
	if(is_block(arn))
		A2S_block(arn, rsn);
	else if(is_decl(arn))
		A2S_decl(arn, rsn);
	else if (is_use(arn))
		A2S_use(arn);
	else {
		for(int i = 0; i < 4; i++)
			AST2SCT(arn.get_one_child(i), rsn);
	}
	return;
}

int main() {
	//example: int B = ( 2 * 7 ) + 3 ;
	Node a,b,c,d,e,intB,q;
	intB.set_id(8);	intB.set_symbol('i');	intB.set_data("B");
	q.set_id(9);	q.set_symbol('=');	a.set_data("equals");
	a.set_id(1);	a.set_symbol('+');	a.set_data("plus");
	b.set_id(2);	a.set_symbol('*');	a.set_data("times");
	c.set_id(3);	a.set_symbol('K');	a.set_data("3");
	d.set_id(4);	a.set_symbol('K');	a.set_data("2");
	e.set_id(5);	a.set_symbol('K');	a.set_data("7");
	Node *f = &b;
	Node *g = &c;
	Node *h = &d;
	Node *j = &e;
	a.set_children();
	a.set_child(f, 0);
	a.set_child(g, 1);
	b.set_children();
	b.set_child(h, 0);
	b.set_child(j, 1);
	print_tree(n);

	//NEED HELP WITH TRAVERSING AST AFTER BUILDING SCT
	//ALSO FIX ANY ISSUES YOU SEE
}
