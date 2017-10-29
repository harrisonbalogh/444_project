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

/**
* Copies data from child to parent node
*/
void copy_guts(Node mum, Node kid) {
	mum.set_id(kid.get_id());
	mum.set_data(kid.get_data());
	mum.set_symbol(kid.get_symbol());
	mum.set_child_count(kid.get_child_count() - 1);
}


/**
 * Hoists a child to a parent that has four child nodes
 * for BBlock
 */
void P2A_hoist_from_four(Node old_p) {
	Node new_p = *(old_p.get_child() + 0);
	new_p.set_children();
	Node* a = old_p.get_child() + 1;
	Node* b = old_p.get_child() + 2;
	Node* c = old_p.get_child() + 3;
	new_p.set_child(a, 0);
	new_p.set_child(b, 1);
	new_p.set_child(c, 2);
	copy_guts(old_p, new_p);
}

/**
 * Hoists a child to a parent that has four child nodes
 * for PPvarlist, Varlist, Stasgn, Stwhile, PPexprs, PPexpr1,
 * E, R and T
 */
void P2A_hoist_from_three(Node old_p) {
	Node new_p = *(old_p.get_child() + 0);
	new_p.set_children();
	Node* a = old_p.get_child() + 1;
	Node* b = old_p.get_child() + 2;
	new_p.set_child(a, 0);
	new_p.set_child(b, 1);
	copy_guts(old_p, new_p);
}

/**
 * Hoists a child to a parent that has four child nodes
 * for StmtList, MoreStmts, Pgm, Vargroup, Vardecl, Stprint, Exprlist,
 * Moreexprs, Expr, Rterm and Term
 */
void P2A_hoist_from_two(Node old_p) {
	Node new_p = *(old_p.get_child() + 0);
	new_p.set_children();
	Node* a = old_p.get_child() + 1;
	new_p.set_child(a, 0);
	copy_guts(old_p, new_p);
}

void P2A_fix(Node n) {
	int option = 0;
	if(n.get_data() == "BBlock")
		option = 1;
	else if(n.get_data() == "PPvarlist" || n.get_data() == "Varlist" || n.get_data() == "Stasgn" || n.get_data() == "Stwhile" ||
			n.get_data() == "PPexprs" || n.get_data() == "PPexpr1" || n.get_data() == "E" || n.get_data() == "R" || n.get_data() == "T")
		option = 2;
	else if(n.get_data() == "StmtList" || n.get_data() == "MoreStmts" || n.get_data() == "Pgm" || n.get_data() == "Vargroup" ||
			n.get_data() == "Stprint" || n.get_data() == "Exprlist" || n.get_data() == "Moreexprs" || n.get_data() == "Expr" ||
			n.get_data() == "Rterm" || n.get_data() == "Term")
		option = 3;

	switch(option) {
		case 1:
			P2A_hoist_from_four(n);
			break;
		case 2:
			P2A_hoist_from_three(n);
			break;
		case 3:
			P2A_hoist_from_two(n);
			break;
		default:
			//P2A_term(n);
			break;
	}
}

void PST2AST(Node n) {
	if(NULL == n)
		return;
	for(int i = 0; i < 4; ++i)
		PST2AST(n.child[i]);
	P2A_fix(n);
	return;
}

int main() {
	return 0;
}
