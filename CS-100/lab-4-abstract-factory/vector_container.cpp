#include "vector_container.h"

// insert the top pointer of the tree into the container
void VectorContainer::add_element(Base* element) {
    container.push_back(element);
}

// iterate through the trees and output values
void VectorContainer::print() {
    for (unsigned int i = 0; i < container.size(); i++) {
        BasePrint* base = factory->generatePrint(container[i]->evaluate());
	base->print();
	//cout << container[i]->evaluate() << endl;
    }
}

// calls on the previously set sorting-algorithm. 
// Check if sort_function is not null, throw exception if is null
void VectorContainer::sort() {
    // error message
    string Error = "\nError: sort_function is NULL.\n\n";

    // output an error message if sort_function is NULL.
    try {
        if (sort_function == NULL)
	    throw Error;
	else
            sort_function->sort(this);
    } catch (string exception) {
        cout << Error;
    }
}

// switch tree locations
void VectorContainer::swap(int i, int j) {
    Base* temp = container[i];
    container[i] = container[j];
    container[j] = temp;
}

// get top pointer of tree at index i
Base* VectorContainer::at(int i) {
    return container[i];
}

// return container size;
int VectorContainer::size() {
    return container.size();
}
