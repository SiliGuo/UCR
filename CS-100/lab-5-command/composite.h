#ifndef __COMPOSITE_CLASS__
#define __COMPOSITE_CLASS__

#include <iostream>
#include <sstream>
#include <math.h>
#include <string>

using namespace std;

// forward declare to avoid circular dependencies
class Iterator;

//Abstract Base Class
class Base {
    public:
        Base(){};

        //virtual
        virtual double evaluate() = 0;
};

//Leaf Class
class Op: public Base {
    private:
        double value;

    public:
        Op() : Base(), value(0){};
        Op(double val) : Base(), value(val){};
        double evaluate() { 
            return this->value; 
        };
};

//Composite Base Classes
class Operator: public Base {
    protected:
        Base* left, *right;
    public:
        Operator() : Base(){ };
        Operator(Base* l, Base* r) : left(l), right(r){  };

        Base* get_left() { return left; };
        Base* get_right() { return right; };

        virtual double evaluate() = 0;	//Note: this is implicit in the inheritance, but can also be made explicit
};

class UnaryOperator: public Base {
    protected:
        Base* child;
    public:
        UnaryOperator() : Base(){};
        UnaryOperator(Base* c) : child(c) { };
        virtual double evaluate() = 0;	//Note: this is implicit in the inheritance, but can also be made explicit
};

//Composite Classes
class Add: public Operator {
    public:
        Add() : Operator() { };
        Add(Base* left, Base* right) : Operator(left,right) { };
        double evaluate() {
            return this->left->evaluate() + this->right->evaluate(); 
        };
};

class Sub: public Operator {
    public:
        Sub() : Operator() { };
        Sub(Base* left, Base* right) : Operator(left,right) { };
        double evaluate() {
            return this->left->evaluate() - this->right->evaluate(); 
        };
};

class Mult: public Operator {
    public:
        Mult() : Operator() { };
        Mult(Base* left, Base* right) : Operator(left,right) { };
        double evaluate() {
            return this->left->evaluate() * this->right->evaluate(); 
        };
};

class Sqr: public UnaryOperator {
    public:
        Sqr() : UnaryOperator() { };
        Sqr(Base* child) : UnaryOperator(child) { };
        double evaluate() {
            return pow(this->child->evaluate(),2);
        };
};

#endif
