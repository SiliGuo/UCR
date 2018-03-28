#ifndef __LEAF_H__
#define __LEAF_H__

#include "component.h"

class Op : public Base {
    private:
        // store calculating value
        double value;
    public:
        /* Constructors */
        Op() {}
        Op(double n) {
            value = n;
        }

        /* Destructor */
        ~Op() {}

        // override virtual function
        double evaluate() {
            return value;
        }
};
#endif /* __LEAF_H__ */
