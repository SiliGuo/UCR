#include "rshell.h"

int Rshell::least(int a, int b) {
    if (a == -1)
        return b;
    else if (b == -1)
        return a;
    else {
        if (a >= b)
            return b;
	else
	    return a;
    }
}

int Rshell::least(int a, int b, int c) {
    int temp = least(a, b);
    return least(temp, c);
}

int Rshell::least(int a, int b, int c, int d, int e) {
    int temp1 = least(a, b);
	int temp2 = least(c, d, e);
	return least(temp1, temp2);
}

void Rshell::delSpace(string& str) {
    int front = str.find_first_not_of(" ");
    int back = str.find_last_not_of(" ");
    str = str.substr(front, (back - front + 1));
}

void Rshell::syntax_error(string str) {
	cout << "-bash: syntax error near unexpected token " << str << endl;
}

void Rshell::incomplete_error() {
	cout << "-bash: incomplete error" << endl;
}

int Rshell::parse() {
    /* Delete space and last semicolon before and after command */
    delSpace(input);
//	if (input.front() == ';') {
//        cout << "-bash: syntax error near unexpected token \';\'" << endl;
//	}
    if (input.back() == ';') input = input.substr(0, (input.size()-1));
    delSpace(input);
    int n_pos = input.find("#");
    if (n_pos != -1) input = input.substr(0, n_pos);

	/* Seperate strings to commands and connectors */
	vector<string> strVec; // store each piece of string cut
	string temp; // temporary store cut string pieces
	string rest = input; //store rest of string
	int lp_pos, rp_pos, a_pos, o_pos, s_pos, pos; // indicate position for each connector

	while (!rest.empty()) {
	    // find each position for connectors
	    lp_pos = rest.find("(");
	    rp_pos = rest.find(")");
        a_pos = rest.find("&&");
        o_pos = rest.find("||");
        s_pos = rest.find(";");
        pos = least(lp_pos, rp_pos, a_pos, o_pos, s_pos);
//		cout << "pos = " << pos << endl;
		// if no connector found, break
		if (pos == -1) break;

        if (pos != 0) {
            temp = rest.substr(0, pos);
			delSpace(temp);
			strVec.push_back(temp);
		}

		if (rest.at(pos) == '&' || rest.at(pos) == '|') {
		    temp = rest.substr(pos, 2);
            strVec.push_back(temp);
			rest = rest.substr(pos + 2);
			if (!rest.empty()) delSpace(rest);
//			cout << "rest: " << rest << endl;
		} else {
            temp = rest.substr(pos, 1);
			strVec.push_back(temp);
			rest = rest.substr(pos + 1);
			if (!rest.empty()) delSpace(rest);
		}
	}
	// push last element in vector (if exist)
	if (!rest.empty()) {
        delSpace(rest);
		strVec.push_back(rest);
	}

//	/* Test strVec */
//	cout << "strVec = " << endl;
//	for (unsigned int i = 0; i < strVec.size(); i++) {
//		cout << "[" << strVec[i] << "]" << endl;
//	}
	
	/* Check validation of command */
	int strSize = strVec.size(); // store the size of strVec
	// check if connectors are at front
	if (strVec[0] == ";" || strVec[0] == "&&" || strVec[0] == "||") {
		syntax_error(strVec[0]);
		return -1;
	}
	// check if connectors are at back
	if (strVec[strSize-1] == "&&" || strVec[strSize-1] == "||" || strVec[strSize-1] == "(") {
		incomplete_error();
		return -2;
	}

	// declare a vector that store the position for each parentheses and intialize
	vector<int> position;
	position.push_back(0);
	
	// check validation for each command/connector, and store in a new vector in preorder
	for (int i = 0; i < strSize; i++) {
//		cout << "start for loop" << endl;
		/* Front Parentheses */
		if (strVec[i] == "(") {
//			cout << "check (" << endl;
			// After "(" cannot be connectors or ")"
			if (strVec[i+1] == "&&" || strVec[i+1] == "||" || strVec[i+1] == ";" || strVec[i+1] == ")")	{
				syntax_error(strVec[i+1]);
				return -1;
			}
			// store parentheses position in vector
			position.push_back(cmd.size());
		/* Back Parentheses */
		} else if (strVec[i] == ")") {
//			cout << "check )" << endl;
			// no "(" before ")"
			if (position.size() <= 1) {
				syntax_error(strVec[i]);
				return -1;
			} else {
				// if not the last element in vector
				if (i != strSize-1) {
					// After ")" can only be connectors or ")"
					if (strVec[i+1] != "&&" && strVec[i+1] != "||" && strVec[i+1] != ";" && strVec[i+1] != ")") {
						// "(" directly after ")"
						if (strVec[i+1] == "(") {
							syntax_error(strVec[i+1]);
							return -1;
						// command directly after ")"
						} else {
							// cut the first word of string
							string t = strVec[i+1];
							int p = t.find(" ");
							if (p != -1) t = t.substr(0, p);
							syntax_error(t);
							return -1;
						}
					}
				}
				// remove the latest position in vector
				position.pop_back();
			}
		/* Connectors */
		} else if (strVec[i] == "&&" || strVec[i] == "||" || strVec[i] == ";") {
//			cout << "check connectors" << strVec[i] << endl;
			if (i != strSize -1) {
				// After connectors cannot be connectors or ")"
				if (strVec[i+1] == "&&" || strVec[i+1] == "||" || strVec[i+1] == ";" || strVec[i+1] == ")")	{
					syntax_error(strVec[i+1]);
					return -1;
				}
			}
			// insert connectors into cmd vector
			cmd.insert((cmd.begin()+position[position.size()-1]), strVec[i]);
		/* Commands */
		} else {
//			cout << "check command [" << strVec[i] << "]" <<  endl;
			if (i != strSize -1) {
				// After commands cannot be "("
				if (strVec[i+1] == "(") {
					syntax_error(strVec[i+1]);
					return -1;
				}
			}
			// store commands in vector
			cmd.push_back(strVec[i]);
		}

//	  	/* Test Case */
//		cout << "cmd = " << endl;
//	    for (unsigned int i = 0; i < cmd.size(); i++) {
//	        cout << "[" << cmd[i] << "]" << endl;
//	    }
	}
	// check if every parentheses is completed
	if (position.size() != 1) {
		incomplete_error();
		return -2;
	}
	
//	/* Test Case */
//	cout << "cmd = " << endl;
//	for (unsigned int i = 0; i < cmd.size(); i++) {
//		cout << "[" << cmd[i] << "]" << endl;
//	}
	return 0;
}

CMD* Rshell::buildTree() {
    string temp = cmd[0];
    cmd.erase(cmd.begin());
    if (temp == ";") {
        CMD* lhs = buildTree();
	CMD* rhs = buildTree();
	return new Semicolon(lhs, rhs);
    } else if (temp == "&&") {
        CMD* lhs = buildTree();
	CMD* rhs = buildTree();
	return new And(lhs, rhs);
    } else if (temp == "||") {
        CMD* lhs = buildTree();
	CMD* rhs = buildTree();
	return new Or(lhs, rhs);
    } else {
        return new Executable(temp);
    }
}

void Rshell::execute() {
    if (parse() >= 0) {
        CMD* run = buildTree();
        run->execute();
	}
}
