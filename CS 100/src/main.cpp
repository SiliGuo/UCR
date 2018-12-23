#include <iostream>
#include "leaf.h"
#include "composite.h"
#include "rshell.h"

using namespace std;

void delSpace(string&);
int main() {
    /* Declare Variables*/
    string input;

    while(1) {
        /* Prompt input from user */
        cout << "$ ";
        getline(cin, input);
		cout << input << endl;
        delSpace(input);
		// loop until user input exit
		if (input == "exit") break;
	
		// execute command
        Rshell* rshell = new Rshell(input);
		rshell->execute();
	
		// clean memory
		delete rshell;
    }
   
    return 0;
}

// delete space at front and back of string
void delSpace(string& str) {
    int front = str.find_first_not_of(" ");
    int back = str.find_last_not_of(" ");
    str = str.substr(front, (back - front + 1));
}
