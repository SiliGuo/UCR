#ifndef __DECORATOR_H__
#define __DECORATOR_H__

#include <math.h>
#include "component.h"

class Decorator : public Base {
    protected:
        Base* decorated;

    public:
        /* Constructor */
	Decorator() {}

	/* Destructor */
	~Decorator() {}

	/* Pure virtual function */
        virtual double evaluate() = 0;
};

class Ceil : public Decorator {
    public:
        /* Constructors */
	Ceil() {}
        Ceil(Base* child) {
            decorated = child;
	}

	/* Destructor */
	~Ceil() {}

	// override virtual function
	double evaluate() {
            return ceil(decorated->evaluate());
	}
};

class Floor : public Decorator {
    public:
        /* Constructors */
	Floor();
        Floor(Base* child) {
	    decorated = child;
	}

	/* Destructor */
	~Floor();

        // override virtual function
	double evaluate() {
            return floor(decorated->evaluate());
	}
};

class Abs : public Decorator {
    public:
        /* Constructors */
	Abs();
	Abs(Base* child) {
            decorated = child;
	}

	/* Destructor */
	~Abs();

	// override virtual function
	double evaluate() {
            return abs(decorated->evaluate());
	}
};
#endif /* __DECORATOR_H__ */

