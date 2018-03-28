#include <iostream>
#include "leaf.h"
#include "composite.h"
#include "vector_container.h"
#include "list_container.h"
#include "strategy.h"
#include "selection_sort.h"
#include "bubble_sort.h"
#include "decorator.h"

using namespace std;

int main() {
    Op* op1 = new Op(5);
    Op* op2 = new Op(2);
    Op* op3 = new Op(4);
    Op* op4 = new Op(6);
    Op* op5 = new Op(7.5);
    Op* op6 = new Op(12.3);
    Mult* A = new Mult(op1, op2);
    //cout << "A = " << A->evaluate() << endl;
    Sub* B = new Sub(op3, op4);
    //cout << "B = " << B->evaluate() << endl;
    Add* C = new Add(A, B);
    //cout << "C = " << C->evaluate() << endl;
    Sqr* D = new Sqr(C);
    //cout << "D = " << D->evaluate() << endl;
    Ceil* E = new Ceil(op5);
    //cout << "E = " << E->evaluate() << endl;
    Floor* F = new Floor(op6);
    //cout << "F = " << F->evaluate() << endl;
    Abs* G = new Abs(B);
    //cout << "G = " << G->evaluate() << endl;

    VectorContainer* container = new VectorContainer();
    //ListContainer* container = new ListContainer();
    container->add_element(A);
    container->add_element(B);
    container->add_element(D);
    cout << "Container Before Sort: " << endl;
    container->print();
    container->set_sort_function(new SelectionSort());
    //container->set_sort_function(new BubbleSort());
    container->sort();	
    cout << "Container After Sort (Decending): " << endl;
    container->print();
};
