#include <iostream>
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

void find_sym(Node ra) {

}

void add_use_link(Node rn, Snode rs) {

}

void add_entry(Node arn, Snode rsn) {

}

bool is_decl(Node arn) {
	if(arn.get_data() == 'int' ||
	   arn.get_data() == 'float' || arn.get_data() == 'string')
		return true;
	else
		return false;

}

bool is_block(Node arn) {
	if(arn.get_symbol() == '{')
		return true;
	else
		return false;
}

bool is_use(Node arn) {
	if(arn.get_symbol() == 'i')
		return true;
	else
		return false;
}

bool is_op(Node arn) {
	if(arn.get_symbol() == '+' || arn.get_symbol() == '-' ||
	   arn.get_symbol() == "*" || arn.get_symbol() == '/')
		return true;
	else
		return false;
}

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

void A2S_use(Node ra, Snode rs) {
	Snode my_scope = find_sym(ra);
	add_use_link(ra, my_scope);
}

void A2S_block(Node arn, SCTnode rsn) {
	SCTnode skid = new SCTnode(rsn); //bilink
	foreach kid
		AST2SCT(kid, skid);
}

void A2S_decl(Node arn, SCTnode rsn) {
	Entry ex = add_entry(arn.lkid, rsn);
	ex.decl = arn;
	if(is_decl(arn.rkid))
		A2S_decl(arn.rkid, rsn);
}

void run_AST(Node arn) {
	if(is_decl(arn)) return;
	else if (is_block(arn))
		foreach kid
			run_AST(kid);
	else if (is_use(arn))
		arn,val = arn.sym.box;
	else if (is_op(arn))
		do_op(arn);	//perform operation (add values of arn kids)
}

void AST2SCT(Node arn, SCTnode rsn) {
	if(NULL == arn) return;
	if(is_block(arn))
		A2S_block(arn, rsn);
	else if(is_decl(arn))
		A2S_decl(arn, rsn);	//add_decl
	else if (is_use(arn))
		A2S_use(arn);	//add_use
	else
		foreach kid
			AST2SCT(kid, rsn);
	return;
}

int main() {
	//example: prog main { int B = ( 2 * 7 ) + 3 ; print ( B ) ; }
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

	//look for brace, var decl (int, float, string), ID
	//linkk i and K nodes to its scope node
	//put ID into symbol table
	//each scope node has a symbol table

	//build SCT (using node that opens scope, decl, var)
	//root will hold global identifiers
	//SET UP ROOT BEFORE WALKING AST
	
	//decl should create new symtab in current scope node
	//entry links back to AST decl
}
