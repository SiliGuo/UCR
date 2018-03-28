#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class CMD {
    public:
        /* Constructor */
		CMD() {}
	
		/* Pure Virtual Functions */
		// execute function, return if scuess
        virtual bool execute() = 0;
};
#endif /* __COMPONENT_H__ */
