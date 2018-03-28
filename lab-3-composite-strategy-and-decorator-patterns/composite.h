#ifndef __COMPOSITE_H__
#define __COMPOSITE_H__

#include "component.h"

class Add : public Base {
    private:
        // 2 Base pointers point to left and right child of tree
        Base* lhs;
        Base* rhs;

    public:
        /* Constructors */
        Add() {}
        Add(Base* left, Base* right) {
            lhs = left;
            rhs = right;
        }

        /* Destructor */
        ~Add() {}

        // override virtural function
        double evaluate() {
            return lhs->evaluate() + rhs->evaluate();
        }
};

class Sub : public Base {
    private:
        // 2 Base pointers point to left and right child of tree
        Base* lhs;
        Base* rhs;

    public:
        /* Constructors */
        Sub() {}
        Sub(Base* left, Base* right) {
            lhs = left;
            rhs = right;
        }

        /* Destructor */
        ~Sub() {}

        // override virtual function
        double evaluate() {
            return lhs->evaluate() - rhs->evaluate();
        }
};

class Mult : public Base {
    private:
        // 2 Base pointers point to left and right child of tree
        Base* lhs;
        Base* rhs;

    public:
        /* Constructors */
        Mult() {}
        Mult(Base* left, Base* right) {
            lhs = left;
            rhs = right;
        }

        /* Destructor */
        ~Mult() {}

        // override virtual function
        double evaluate() {
            return lhs->evaluate() * rhs->evaluate();
        }
};

class Div : public Base {
    private:
        // 2 pointers point to left and right child of tree
        Base* lhs;
        Base* rhs;

    public:
        /* Constructors */
        Div() {}
        Div(Base* left, Base* right) {
            lhs = left;
            rhs = right;
        }

        /* Destructor */
        ~Div() {}

        //override virtual function
        double evaluate() {
            return lhs->evaluate() / rhs->evaluate();
        }
};

class Sqr : public Base {
    private:
        // only conatins 1 pointer point to the only child of tree
        Base* expression;

    public:
        /* Constructors */
        Sqr() {}
        Sqr(Base* child) {
            expression = child;
        }

        /* Destructor */
        ~Sqr() {}

        // override virtual function
        double evaluate() {
            return expression->evaluate() * expression-> evaluate();
        }
};
#endif /* __COMPOSITE_H */
