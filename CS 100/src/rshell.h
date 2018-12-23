#ifndef __RSHELL_H__
#define __RSHELL_H__

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "leaf.h"
#include "composite.h"

using namespace std;

class Rshell {
    private:
        // store command and connector string
	    string input;
        // store each piece of command or connector
	    vector<string> cmd;
	
	    /* In Class Functions */
	    // get the least number (except -1)
	    int least(int, int);
	    int least(int, int, int);
		int least(int, int, int, int, int);
        
	    // delete space before and after command
	    void delSpace(string&);

		// output syntax error message (return -1)
		void syntax_error(string);

		// output incomplete error message (return -2)
		void incomplete_error();

	    // parse string into pieces
        int parse();

	    // construct the tree structure
	    CMD* buildTree();

    public:
        /* Constructor */
	    Rshell() {
            input = "";
			cmd.clear();
	    }
	    Rshell(string str) {
            input = str;
			cmd.clear();
	    }

	    /* Destructor */
	    ~Rshell() {}

	    // execute the command
	    void execute();
};
#endif /* __RSHELL_H__ */
