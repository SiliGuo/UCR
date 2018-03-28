#ifndef __LIST_CONTAINER_H__
#define __LIST_CONTAINER_H__

#include <iostream>
#include <list>
#include "component.h"
#include "container.h"
#include "print.h"

using namespace std;

class ListContainer : public Container {
    private:
        // linked list that stores all Base* value 
        list<Base*> container;

    public:
        /* Constructors */
        ListContainer() {}
        ListContainer(BaseFactory* factory) {
            this->factory = factory;
	}

        /* Destructor */
        ~ListContainer() {}

        /* Override virtual functions */
        // insert the top pointer of the tree into the container
        void add_element (Base*);
        // iterate through the trees and output values
        void print();
        // calls on the previously set sorting-algorithm. 
        // Check if sort_function is not null, throw exception if is null
        void sort();

        // switch tree locations
        void swap(int i, int j);
        // get top pointer of tree at index i
        Base* at(int i);
        // return container size;
        int size();
};

#endif /* __LIST_CONTAINER_H__ */
