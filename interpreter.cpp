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
	return true;
}

bool is_block(Node arn) {
	return true;
}

bool is_use(Node arn) {
	return true;
}

bool is_op(Node arn) {
	return true;
}

void do_op(Node arn) {
	//add
	//sub
	//mult
	//divide
	//compare
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

	//example: prog main { int E = 12 ; int F = 0 ; F = E + E * E ; print ( E ) ; }
	//obtain AST from parser
	//build SCT (using node that opens scope, decl, var)
	//root will hold global identifiers
	//SET UP ROOT BEFORE WALKING AST
	//scope contains symbol table
	//treewalk AST to run executable
	
	//decl should create new symtab in current scope node
	//entry links back to AST decl
}