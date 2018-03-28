#ifndef __COMMAND_CLASS__
#define __COMMAND_CLASS__

#include "composite.h"

class Command {
    protected:
        Base* root;
	
    public:
	Command() { };
	double execute() {
	    return root->evaluate();
	};
	Base* get_root() {
	    return root;
	};
};

class OpCommand : public Command {
    //OpCommand Code Here
    public:
        /* Constructors */
        OpCommand() {}
        OpCommand(double value) {
            Op* op = new Op(value);
	    root = op;
        }
};

class AddCommand : public Command {
    //AddCommand Code Here
    public:
        /* Constructors */
	AddCommand() {}
	AddCommand(Command* cmd, double value) {
            Add* add = new Add(cmd->get_root(), new Op(value));
	    root = add;
	}
};

class SubCommand : public Command {
    //SubCommand Code Here
    public:
        SubCommand() {}
	SubCommand(Command* cmd, double value) {
            Sub* sub = new Sub(cmd->get_root(), new Op(value));
	    root = sub;
	}
};

class MultCommand : public Command {
    //MultCommand Code Here
    public:
        MultCommand() {}
	MultCommand(Command* cmd, double value) {
	    Mult* mult = new Mult(cmd->get_root(), new Op(value));
	    root = mult;
	}
};

class SqrCommand : public Command {
    //SqrCommand Code Here
    public:
        SqrCommand() {}
	SqrCommand(Command* cmd) {
            Sqr* sqr = new Sqr(cmd->get_root());
	    root = sqr;
	}
};

#endif //__COMMAND_CLASS__
