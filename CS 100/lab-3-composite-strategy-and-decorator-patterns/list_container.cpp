#include "list_container.h"

// insert the top pointer of the tree into the container
void ListContainer::add_element(Base* element) {
    container.push_back(element);
}

// iterate through the trees and output values
void ListContainer::print(){
    // an iterator through list
    list<Base*>::iterator it;

    // output values in list
    for (it = container.begin(); it != container.end(); ++it) {
        cout << (*it)->evaluate() << endl;
    } 
}

// calls on the previously set sorting-algorithm. 
// Check if sort_function is not null, throw exception if is null
void ListContainer::sort() {
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
void ListContainer::swap(int i, int j) {
    // declare temp variables
    Base* temp1;
    Base* temp2;

    // declare 2 Base* iterators
    list<Base*>::iterator it1;
    list<Base*>::iterator it2;

    // assign swap value to temp variables
    temp1 = at(i);
    temp2 = at(j);

    // delete and insert new value in i position
    it1 = container.begin();
    for(int k = 0; k < i; k++)
        it1++;

    it2 = container.erase(it1);
    container.insert(it2, temp2);

    // delete and insert new value in j position
    it1 = container.begin();
    for (int k = 0; k < j; k++)
        it1++;

    it2 = container.erase(it1);
    container.insert(it2, temp1);
}

// get top pointer of tree at index i
Base* ListContainer::at(int i) {
    // an iterator though the list
    list<Base*>::iterator it;
    it = container.begin();

    for (int k = 0; k < i; k++)
        it++;

    return (*it);
}

// return container size;
int ListContainer::size() {
    return container.size();
}
