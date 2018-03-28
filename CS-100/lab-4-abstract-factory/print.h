#ifndef __PRINT_H__
#define __PRINT_H__

#include <iostream>
#include <bitset>

using namespace std;

class BasePrint {
    protected:
        /* Value to Print */
        double value;

    public:
        /* Constructors */
	BasePrint() {}
	BasePrint(double value) {
            this->value = value;
	}

        /* Pure Virtual Print Function */
	virtual void print() = 0;
};

class DoublePrint : public BasePrint {
    public:
        /* Constructors */
	DoublePrint() {}
	DoublePrint(double value) {
            this->value = value;
	}

	// override virtual function
	void print() {
            cout << value << endl;
	}
};

class HexPrint : public BasePrint {
    public:
        /* Constructors */
	HexPrint() {}
	HexPrint(double value) {
            this->value = value;
	}

	// override virtual function
	void print() {
            cout << hexfloat << value << endl;
	}
};

class BinaryPrint : public BasePrint {
    public:
        /* Constructors */
	BinaryPrint() {}
	BinaryPrint(double value) {
            this->value = value;
	}

	// override virtual function
	void print() {
            bitset<16> bit (value);
	    cout << bit << endl;
	}
};
#endif /* __PRINT_H__ */
