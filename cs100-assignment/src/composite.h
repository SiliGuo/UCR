#ifndef __COMPOSITE_H__
#define __COMPOSITE_H__

#include "component.h"

class Semicolon : public CMD {
    private:
        CMD* lhs;
		CMD* rhs;

    public:
        /* Constructor */
		Semicolon() {}
		Semicolon(CMD* lhs, CMD* rhs) {
			this->lhs = lhs;
			this->rhs = rhs;
		}

		// override virtual function
		bool execute() {
            lhs->execute();
		    bool r = rhs->execute();
			return r;
		}
};

class And : public CMD {
    private:
        CMD* lhs;
		CMD* rhs;

    public:
        /* Constructors */
		And () {}
		And(CMD* lhs, CMD* rhs) {
            this->lhs = lhs;
		    this->rhs = rhs;
		}

		// override virtual function
		bool execute() {
		    bool l = lhs->execute();
		    if (l == true) {
                bool r = rhs->execute();
				return r;
			} else return l;
		}
};

class Or : public CMD {
    private:
		CMD* lhs;
		CMD* rhs;

    public:
        /* Constructors */
		Or() {}
		Or(CMD* lhs, CMD* rhs) {
            this->lhs = lhs;
			this->rhs = rhs;
		}

		// override virtual function
		bool execute() {
            bool l = lhs->execute();
            if (l == false) {
                bool r = rhs->execute();
				return r;
		    } else return l;
		}
};
#endif /* __COMPOSITE_H__ */
