#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "print.h"

class BaseFactory {
    public:
        /* Constructor */
	BaseFactory() {}

	/* Pure Virtual Generate Function */
       	virtual BasePrint* generatePrint(double value) = 0;
};

class DoubleFactory : public BaseFactory {
    public:
        /* Constructor */
	DoubleFactory() {}

	// override virtual function
	BasePrint* generatePrint(double value) {
           return new DoublePrint(value);  
	}
};

class HexFactory : public BaseFactory {
    public:
        /* Constructor */
	HexFactory() {}

	// override virtual function
	BasePrint* generatePrint(double value) {
            return new HexPrint(value);
	}
};

class BinaryFactory : public BaseFactory {
    public:
        /* Constructors */
	BinaryFactory() {}

	// override virtual function
	BasePrint* generatePrint(double value) {
            return new BinaryPrint(value);
	}
};

#endif /* __FACTORY_H__ */
