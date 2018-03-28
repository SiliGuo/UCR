#ifndef __LEAF_H__
#define __LEAF_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "component.h"

using namespace std;

class Executable : public CMD {
    private:
        // store command string
        string str;
		// delete space at front and at back
		void delSpace(string& str) {
		    int front = str.find_first_not_of(" ");
		    int back = str.find_last_not_of(" ");
		    if (str != "") str = str.substr(front, (back - front + 1));
		}
		bool is_p_or_f(string str) {
			int pos1 = str.find('|');
			int pos2 = str.find('<');
			int pos3 = str.find('>');
			if (pos1 == -1 && pos2 == -1 && pos3 == -1) return false;
			else return true;
		}

    public:
        /* Constructors */
        Executable() {}
		Executable(string str) {
		    this->str = str;
		}

		// override virtual function
		bool execute() {
			/* Declare variables */
			pid_t child;
		    int status; // exit status of pid
            char* argv[100]; // list of arguments for the child process
			vector<string> vec; // vector to store all arguments
			int pos = str.find(" "); // find each positon with whitespace
			string sub1; // the cut piece of arguments
			string rest = str; // rest of the arguments
			struct stat sb;

			/* Execute filestream and pipe */
			if (is_p_or_f(str)) {
				if (exe_pipe(str) == true) return true;
				else return false;
			}

			/* Cut String into Pieces */
			while(pos != -1) {
				sub1 = rest.substr(0, pos);
				delSpace(sub1);
				vec.push_back(sub1);
				rest = rest.substr(pos + 1);
				delSpace(rest);
				pos = rest.find(" ");
		    }
		    if (!rest.empty()) {
				vec.push_back(rest);
		    }

		    /* Test and execute test command*/
		    int vec_l = vec.size()-1; // index of last member in vector
		    string path; // path of the file for test 
		    if (vec[0] == "test" || (vec[0] == "[" && vec[vec_l] == "]")) {
		        // get path string
				if (vec[0] == "test") {
				    path = str.substr(5);
			    	delSpace(path);
				} else {
			    	path = str.substr(2, (str.size() - 4));
			    	delSpace(path);
//			    	cout << path << endl;
				}

		    	if (vec[1].at(0) != '-') {
					if (stat((char*)path.c_str(), &sb) == -1) {
						perror("stat");
						cout << "(false)" << endl;
						return false;
					} else {
						cout << "(true)" << endl;
						return true;
			    	}
				} else {
			    	// remove flag piece from path string
			    	path = path.substr(3);
			    	delSpace(path);
			    	if (stat((char*)path.c_str(), &sb) == -1) {
						perror("stat");
						cout << "(false)" << endl;
						return false;
			    	} else {
						if (vec[1] == "-f") {
							if (sb.st_mode & S_IFREG) {
				        		cout << "(true)" << endl;
								return true;
				    		} else {
								cout << "(false)" << endl;
								return false;
				    		}
						} else if (vec[1] == "-d") {
							if (sb.st_mode & S_IFDIR) {
			        			cout << "(true)" << endl;
								return true;
							} else {
				       			cout << "(false)" << endl;
								return false;
				  			}
						} else {
				    		cout << "(true)" << endl;
				    		return true;
						}
			    	}
				}
		    }

			// assign each piece of command to argument vector
			for (unsigned int i=0; i<vec.size(); i++) {
				argv[i] = (char*)vec[i].c_str();
			}
		    argv[vec.size()] = NULL;

	        /* Child process*/
		    if ((child = fork()) == 0) {
		        if((execvp(argv[0], argv)) == -1) { // argv[0] has the command name
					perror("-bash");
		    	    /* If the child process reaches this point, then */
		    	    /* execvp must have failed.                      */
					exit(1);
				}

	        /* Parent process*/
		    } else {
		        if (child == (pid_t)(-1)) {
				    cout << "Error: Fork failed" << endl;
				    exit(0);
				} else
	         	   wait(&status);
		    }
	    
		    /* Return Value */
		    if (status == 0) return true;
		    else return false;
		}

	/* Execution of pipe function */
	bool exe_pipe(string userInput) {
//		string userInput = "cat < 1.txt | tr A-Z a-z | tee 2.txt | tr a-z A-Z > 3.txt";
		vector<string> pcmd; // vector stored parse cmds
		char* argv[100]; // cmds for executions
		pid_t child;
		int status;
		int mypipe1[2]; // 1st pipe
		int mypipe2[2]; // 2nd pipe
		int ret; // return value for pipe
		int p_stat = 0;	// status for using which pipe (0-no pipe; 1-mypipe1; 2-mypipe2)

		// parse cmds based on '|'
		pipe_parse(userInput, pcmd);
		for(unsigned int i = 0; i < pcmd.size(); i++) {
			if (i + 1 == pcmd.size()) break;
			if (pcmd[i] == "|") {
				if (i - 1 == 0) {
					ret = pipe(mypipe1);
					p_stat = 2;
					if (ret == -1) {
						perror("pipe:");
						exit(EXIT_FAILURE);
					}
	
					/* Child Process */
					if ((child = fork()) == 0) {
					//	close(1);
						dup2(mypipe1[1], 1);
		
						if (is_file(pcmd[0])) {
							if (exe_file(pcmd[0]) == false) return false;
						} else {
							exe_parse(argv, pcmd[0]);
							if ((execvp(argv[0], argv)) == -1) {
								perror("execvp:");
								exit(EXIT_FAILURE);
							}
						}
					} else { 
						if (child == (pid_t)(-1)) {
							cout << "Error: Frok failed" << endl;
							exit(0);
						} else {
							wait(&status);
							close(mypipe1[1]);
						}
					}
				} else {
					if (p_stat == 1) {
						ret = pipe(mypipe1);
						p_stat = 2;
					} else if (p_stat == 2) {
						ret = pipe(mypipe2);
						p_stat = 1;
					}
					if (ret == -1) {
						perror("pipe:");
						exit(EXIT_FAILURE);
					}

					/* Child Process */
					if ((child = fork()) == 0) {
						if (p_stat == 1){
							dup2(mypipe1[0], 0);
							dup2(mypipe2[1], 1);
						} else if (p_stat == 2) {
							dup2(mypipe2[0], 0);
							dup2(mypipe1[1], 1);
						}

						if (is_file(pcmd[i-1])) {
							if (exe_file(pcmd[i-1]) == false) return false;
						} else {
						exe_parse(argv, pcmd[i-1]);
							if ((execvp(argv[0], argv)) == -1) {
								perror("execvp:");
								exit(EXIT_FAILURE);
							}
						}
					} else {
						if (child == (pid_t)(-1)) {
							cout << "Error: Fork failed" << endl;
							exit(0);
						} else {
							wait(&status);
							if (p_stat == 1) {
								close(mypipe1[0]);
								close(mypipe2[1]);
							} else if (p_stat == 2) {
								close(mypipe2[0]);
								close(mypipe1[1]);
							}
						}
					}
				}
			}
		}
	
		if (p_stat == 1) ret = pipe(mypipe1);
		else if (p_stat == 2) ret = pipe(mypipe2);
		if (ret == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		/* Child Process */
		if ((child = fork()) == 0) {
//			close(0);
			if (p_stat == 1) dup2(mypipe2[0], 0);
			else if (p_stat == 2) dup2(mypipe1[0], 0);
	
			if (is_file(pcmd[pcmd.size()-1])) {
				if (exe_file(pcmd[pcmd.size()-1]) == false) return false;
			} else {
				exe_parse(argv, pcmd[pcmd.size()-1]);
				if ((execvp(argv[0], argv)) == -1) {
					perror("execvp:");
					exit(EXIT_FAILURE);
				}
			}
		} else { 
			if (child == (pid_t)(-1)) {
				cout << "Error: Frok failed" << endl;
				exit(0);
			} else {
				wait(&status);
				if (p_stat == 1) close(mypipe2[0]);
				else if (p_stat == 2) close(mypipe1[0]);
			}
		}

		/* Return Value */
		if (status == 0) return true;
		else return false;
	}

	/* Test if required file i/o */
	bool is_file(string str) {
		int pos1 = str.find('<');
		int pos2 = str.find('>');
		if (pos1 == -1 && pos2 == -1) return false;
		else return true;
	}

	/* Find least number*/
	int least(int a, int b) {
		if (a == -1) return b;
		if (b == -1) return a;
		if (a < b) return a;
		else return b;
	}
	
	// parse cmds based on '|'
	void pipe_parse(string str, vector<string>& pcmd) {
		string temp;
		string rest = str;
		int pos;

		while (!rest.empty()) {
			pos = rest.find('|'); 
			if (pos == -1) break;

			if (pos != 0) {
				temp = rest.substr(0, pos);
				delSpace(temp);
				pcmd.push_back(temp);
			} else cout << "Error" << endl;
			if (rest.at(pos) == '|') {
				temp = rest.substr(pos, 1);
				rest = rest.substr(pos + 1);
			}
			pcmd.push_back(temp);
			if (!rest.empty()) delSpace(rest);
		}
		if (!rest.empty()) {
			delSpace(rest);
			pcmd.push_back(rest);
		}

//		/* Test Case */
//		for (int i = 0; i < pcmd.size(); i++) {
//			cout << "[" << pcmd[i] << "]" << endl;
//		}
	}
	
	/* Parse for executing cmds*/
	void exe_parse(char* argv[], string str) {
		string sub1;
		string rest = str;
		int pos = rest.find(' ');
		vector<string> vec;
		/* Cut String into Pieces */
		while(pos != -1) {
			sub1 = rest.substr(0, pos);
			delSpace(sub1);
			vec.push_back(sub1);
			rest = rest.substr(pos + 1);
			delSpace(rest);
			pos = rest.find(' ');
	    }
	    if (!rest.empty()) {
			vec.push_back(rest);
		}

		for (unsigned int i = 0; i < vec.size(); i++) {
			argv[i] = (char*)vec[i].c_str();
		}
		argv[vec.size()] = NULL;

	}

	/* Parse for file i/o */
	void file_parse(string str, vector<string>& fcmd) {
		string temp;
		string rest = str;
		int in_pos, out_pos, pos;

		while (!rest.empty()) {
			in_pos = rest.find('<');
			out_pos = rest.find('>');
			pos = least(in_pos, out_pos);
			if (pos == -1) break;

			if (pos != 0) {
				temp = rest.substr(0, pos);
				delSpace(temp);
				fcmd.push_back(temp);
			} else cout << "Error" << endl;
			
			if (rest.at(pos) == '>' && rest.at(pos+1) == '>') {
				temp = rest.substr(pos, 2);
				rest = rest.substr(pos + 2);
			} else {
				temp = rest.substr(pos, 1);
				rest = rest.substr(pos + 1);
			}
			fcmd.push_back(temp);
			if (!rest.empty()) delSpace(rest);
		}
		if (!rest.empty()) {
			delSpace(rest);
			fcmd.push_back(rest);
		}

//		/* Test Case */
//		for (unsigned int i = 0; i < fcmd.size(); i++) {
//			cout << "[" << fcmd[i] << "]" << endl;
//		}
	}

	/* file i/o execution */
	bool exe_file(string userInput) {
		vector<string> fcmd;
		char* argv[100];
		int input, output;

		file_parse(userInput, fcmd);
		exe_parse(argv, fcmd[0]);
		for (unsigned int i = 0; i < fcmd.size(); i++) {
			if (fcmd[i] == "<") {
				i++;
				input = open(fcmd[i].c_str(), O_RDONLY);
				if (input == -1) {
					perror("input:");
					exit(EXIT_FAILURE);
				}
				dup2(input, 0);
				close(input);
			} else if (fcmd[i] == ">") {
				i++;
				output = open(fcmd[i].c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666/*S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH*/);
				if (output == -1) {
					perror("output:");
					exit(EXIT_FAILURE);
				}
				dup2(output, 1);
				close(output);
			} else if (fcmd[i] == ">>") {
				i++;
				output = open(fcmd[i].c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666/*S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH*/);
				if (output == -1) {
					perror("output:");
					exit(EXIT_FAILURE);
				}
				dup2(output, 1);
				close(output);
			}
		}
		if ((execvp(argv[0], argv)) == -1) {
			perror("execvp:");
			exit(2);
		}
		return true;
	}
};
#endif /* __LEAF_H__ */
