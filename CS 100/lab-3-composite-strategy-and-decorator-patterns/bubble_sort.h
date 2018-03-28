#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__

#include "strategy.h"

class BubbleSort : public Sort {
    public:
        /* Constructor */
	BubbleSort() {}

	/* Destructor */
	~BubbleSort() {}

	// override sort function
        void sort(Container* container) {
            int i, j, flag = 1;    // set flag to 1 to start first pass
            int numLength = container->size( ); 
            for(i = 1; (i <= numLength) && flag; i++)
            {
                flag = 0;
                for (j = 0; j < (numLength - 1); j++)
                {
                    if (container->at(j+1)->evaluate() > container->at(j)->evaluate())      // ascending order simply changes to <
                    { 
                        container->swap(j, (j+1));             // swap elements
                        flag = 1;               // indicates that a swap occurred.
                    }
                }
            }
        }
};
#endif /* __BUBBLE_SORT_H__ */
