#ifndef __STRATEGY_H__
#define __STRATEGY_H__

//#include "container.h"
class Container;

class Sort {
    public: 
        /* Constructors */
        Sort() {}

        /* Pure Virtual Functions */
        virtual void sort(Container* container) = 0;
};
#endif // __STRATEGY_H__
