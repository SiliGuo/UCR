# Composite and Strategy Patterns
**You *must* work in a group of two for this lab**

## Composite Pattern
You will start this lab by creating a composite pattern for representing an expression tree. An expression tree is a tree representation of an equation, so the expression 
```
3 + 7 * 4 - 2
```
would be represented with the following tree:

![Composite Tree of equation](https://github.com/cs100/lab04_composite-strategy/blob/master/Images/CompositeTree.png)

The first expression to be executed (in this case, 7 * 4) will be at the deepest level. The result of that calculation then becomes an input to the addition (which becomes 3 + 28), and that result becomes an input to the subtraction (31 - 2). The tree is evaluated recursively from the bottom to the top, and is constructed in this particular way because of the order of operations.

You will write a composite pattern for representing these expression trees. You are required to use the following base class (found in component.h):
```c++
class Base{
  public: 
    /* Constructors */
    Base() { }
    /* Pure Virtual Functions */
    virtual double evaluate() = 0;
};
```
Note that  the main function in the base class is `evaluate()`, which will be used to return the value of the tree (subtree). 

You will have one type of leaf node which will represent a number (`class Op`), and two types of composite nodes. 
1. There will be four types of nodes that have two children, capable of expressing the operations
  a. `class Multiply` for multiply
  b. `class Divide` for divide
  c. `class Add` for addition
  d. `class Subtract` for subtraction.
2. There will also be one type of node that only has one child, which expresses squaring a value, `class Square`.

Notice that any parentheses that would be in the expression can be implemented in the tree structure rather than explicitly with a node. 

You are not required to implement functionality for parsing an expression, but can build the trees by instantiating nodes individually and adding them as children, as shown in the example main below. 

## Strategy Pattern
Now that you have created your expression tree classes, we will create a strategy pattern for sorting these trees by their `evaluate()` value. You will start this by creating the **context** for the stragety; two containers, one that uses a vector to hold your trees (`class VectorContainer`), and one that uses a list (`class ListContainer`). Both of these classes hold the top node pointers of the trees, so the list or vector would be of the type `<Base*>`. You will implement them both using the following Container base class. Each of the derived classes should have have their own .h and .cpp files. 
```c++
class Container {
  protected: 
    Sort* sort_function;
  public:
    /* Constructors */
    Container() : sort_function(NULL){ }
    Container(Sort* function) : sort_function(function){ }
    /* Non Virtual Functions */
    void set_sort_function(Sort* sort_function); // Set the type of sorting algorithm
    /* Pure Virtual Functions */
    // insert the top pointer of the tree into the container
    virtual void add_element(Base* element) = 0;
    // iterate through trees and output values
    virtual void print() = 0;
    // calls on the previously set sorting-algorithm. Checks if sort_function is not null, throw exception if otherwise
    virtual void sort() = 0;
    /* Essentially the only functions needed to sort */
    // switch tree locations
    virtual void swap(int i,int j) = 0;
    // get the top pointer of tree at index i
    virtual Base* at(int i) = 0;
    // return the container size
    virtual int size() = 0;
};
```
Notice that our container abstract base class does not have any actual STL containers because it leaves it to the derived classes to implement its own version of containers. 

You must use the homogeneous interface above for your sort functions, and you are only allowed to manipulate the containers through this interface, not directly. This will allow you to extend and change the underlying functionality without having to change anything that interfaces with it. 

You will also implement two sort functions, **Concrete Strategy**, for sorting these containers, one that uses the [selection sort algorithm](http://mathbits.com/MathBits/CompSci/Arrays/Selection.htm) and one that uses the [bubble sort algorithm](http://mathbits.com/MathBits/CompSci/Arrays/Bubble.htm) (you may directly adapt this code when writing your sort functions). They should both inherit from the base sort class, **Strategy** interface, below:
```c++
class Sort {
  public:
    /* Constructors */
    Sort();
    /* Pure Virtual Functions */
    virtual void sort(Container* container) = 0;
};
```
Notice that your container class requires a reference to your container class (and vice-versa). This will require you to use forward declarations and object file compilation. The easies way to compile with object files (without learning more specific g++ commands) is to use the makefile provided. You can get a good overview of [makefiles here](http://mrbook.org/blog/tutorials/make/) (and you may want to learn more about them on your own). You can also get a good overview of how [forward declarations work here](http://www.umich.edu/~eecs381/handouts/IncompleteDeclarations.pdf).

You should test all the combinations of containers and sorting objects together. The following code serves as a basic test you should use to extend your own test cases. 
```c++
#include <iostream>
// #include necessary classes

using namespace std;

int main() {
    Op* op7 = new Op(7);
    Op* op4 = new Op(4);
    Op* op3 = new Op(3);
    Op* op2 = new Op(2);
    Mult* A = new Mult(op7, op4);
    Add* B = new Add(op3, A);
    Sub* C = new Sub(B, op2);
    Sqr* D = new Sqr(C);

    VectorContainer* container = new VectorContainer();
    container->add_element(A);
    container->add_element(B);
    container->add_element(C);
    container->add_element(D);

    cout << "Container Before Sort: " << endl;
    container->print();

    cout << "Container After Sort: " << endl;
    container->set_sort_function(new SelectionSort());
    container->sort();
    container->print();
};
```

## Decorator Pattern 
In this lab you will be extending your Composite & Strategy Pattern lab with a decorator, which will be used to modify expressions. For example, we may want to create the following equation:
```
ceil(3 + 7 * 4 - 2)
```
would be represented with the following tree, with the top most node being a decorator

![Composite Tree of equation](https://github.com/cs100/lab04_composite-strategy/blob/master/Images/CompositeTree.png)

You can see how the ceiling function simply modifies the return of the statement, and that the return value at the top would be the ceiling of the equation below. You will be in charge of building three separate decorator classes, and testing each one at different levels of your system (including when decorators have children which are other decorators). Note that it is easiest to fully test a system when it holds double values rather than integer values. You must create the following classes as decorators:
  a. Ceiling (`Ceil`)
  b. Floor (`Floor`)
  c. Absolute Value (`Abs`)
To implement the functionality of each of these classes, you may employ the cmath library (`math.h`). This makes the implementation of the functionality trivial, so it is important that you are fully testing all variations of decorator composition (specifically, when an Absolute Value points to a Ceiling/Floor and vice-versa), since this is one of the more important concepts when discussing decorator patterns. You will be implementing each class independently and thoroughly testing it before moving on. **Each class should be it’s own commit** with a proper commit message.

## Submission
To receive credit for this lab you must show an example program to your TA that demonstrated the full functionality of these three patterns, and must explain to your TA the structure of your composite pattern, strategy pattern and decorator pattern. 

Once you have demoed to your TA, make sure you commit your changes and push them to your github repository. Submit a screenshot of this push to the lab submission on iLearn. 
