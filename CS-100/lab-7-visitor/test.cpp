#include <iostream>
#include <vector>
#include "composite.h"
#include "iterator.h"

using namespace std;

int main() {

	Op* op3 = new Op(3);
	Op* op4 = new Op(4);
	Op* op2 = new Op(2);
	Add* add = new Add(op3, op4);
	Sqr* sqr = new Sqr(op2);
	Sub* sub = new Sub(add, sqr);
	Root* root = new Root(sub);

	cout << "--- Preorder Iteration ---" << endl;
	PreorderIterator* pre_itr = new PreorderIterator(root);
	Visitor* vis = new PrintVisitor();
	for(pre_itr->first(); !pre_itr->is_done(); pre_itr->next()) {
		pre_itr->current()->print();
		pre_itr->current()->accept(vis);
		cout << endl;
	}
	cout << "--- Visitor Test ---" << endl;
	vis->execute();
	return 0;
}
