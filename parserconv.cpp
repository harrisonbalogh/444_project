#include <iostream>
using namespace std;

struct Node{
	char type[10];
	string data;
	Node* child;
};

/**
 * Checks whether a node has children
 */
bool has_kids(Node n) {
	bool result = (nullptr != n.child) ? true : false;
	return result;
}

/**
 * Copies data from child to parent node
 */
void copy_guts(Node mum, Node kid) {
	mum.data = kid.data;
}

/**
 * P2A rule that covers
 * PGM = KPROG VARGROUP FCNDEFS MAIN
 */
void P2A_fix1(Node n) {
	Node kid1 = n.child[1];
	for(int i = 2; i < (sizeof(n.child) / sizeof(Node)) ; i++)
		kid1.child[i - 1] = n.child[i];
	copy_guts(n, kid1);
}

/**
 * P2A rule that covers
 * BBlock = brace1 vargroup stmts brace2
 */
void P2A_fix3(Node n) {
	P2A_fix1(n);
}

/**
 * P2A rule that covers
 * STMTS = STMT STMTS
 */
void P2A_fix6(Node n) {
	Node kid1 = n.child[1];
	Node kid2 = n.child[2];
	if(has_kids(kid1)) {
		kid1.child[3] = kid2;
		copy_guts(n, kid1);
	}
}

/**
 * P2A rule that covers
 * STMT = KPRINT ID
 */
void P2A_fix9(Node n) {
	Node kid1 = n.child[1];
	Node kid2 = n.child[2];
	kid1.child[1] = kid2;
	copy_guts(n, kid1);
}

/**
 * P2A rule that covers
 * MDHEADER = KFCN MDID PPARMLIST RETKIND
 */
void P2A_fix23(Node n) {
	P2A_fix1(n);
}

void P2A_term(Node n) {

}

void P2A_fix(Node n) {
	int option;
	switch(option) {
		case 1:
			P2A_fix1(n);
			break;
		case 3:
			P2A_fix3(n);
			break;
		case 6:
			P2A_fix6(n);
			break;
		case 9:
			P2A_fix9(n);
			break;
		default:
			P2A_term(n);
			break;
	}
}

void PST2AST(Node n) {
	if(nullptr == n)
		return;
	for(int i = 1; i <= 10; ++i)
		PST2AST(n.child[i]);
	P2A_fix(n);
	return;
}

int main() {
	return 0;
}
