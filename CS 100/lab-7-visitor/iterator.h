#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <iostream>
#include <stack>
#include "composite.h"

using namespace std;


class Base;

class Iterator {
    protected:
        Base* self_ptr;
        Base* current_ptr;
    public:
        Iterator(Base* ptr) { this->self_ptr = ptr; current_ptr = NULL; }

        /* Sets up the iterator to start at the beginning of traversal */
        virtual void first() = 0;
        
        /* Move onto the next element */
        virtual void next() = 0;

        /* Returns if you have finished iterating through all elements */
        virtual bool is_done() = 0;

        /* Return the element the iterator is currently at */
        virtual Base* current() = 0;
};

class OperatorIterator : public Iterator {
    public:
        OperatorIterator(Base* ptr) : Iterator(ptr) {}

        void first();
        void next();
        bool is_done();
        Base* current();
};

class UnaryIterator : public Iterator {
    public:
        UnaryIterator(Base* ptr) : Iterator(ptr) {}

        void first();
        void next();
        bool is_done();
        Base* current();
};

class NullIterator : public Iterator {
    public:
        NullIterator(Base* ptr) : Iterator(ptr) {}

        void first();
        void next();
        bool is_done();
        Base* current();
};

class PreorderIterator : public Iterator {
    protected:
	    stack<Iterator*> iterators;
    public:
        PreorderIterator(Base* ptr) : Iterator(ptr) {}

        void first();
        void next();
        bool is_done();
        Base* current();
};

#endif //__ITERATOR_H__
