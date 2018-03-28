#ifndef __VECTOR_CONTAINER_H__
#define __VECTOR_CONTAINER_H__

#include <iostream>
#include <vector>
#include "component.h"
#include "container.h"

using namespace std;

class VectorContainer : public Container {
    private:
        // vector that stores all Base* value
        vector <Base*> container;

    public:
        /* Constructor */
        VectorContainer() {}

        /* Destructor */
        ~VectorContainer() {}

        /* Override virtual functions */
        // insert the top pointer of the tree into the container
        void add_element(Base*);
        // iterate through the trees and output values
        void print();
        // calls on the previously set sorting-algorithm. 
        // Check if sort_function is not null, throw exception if is null
        void sort();

        // switch tree locations
        void swap(int i, int j);
        // get top pointer of tree at index i
        Base* at(int i) ;
        // return container size;
        int size();
};
#endif /* __VECTOR_CONTAINER_H__ */
