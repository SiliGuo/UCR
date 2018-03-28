#include "visitor.h"

void PrintVisitor::rootNode() {
	output.append("ROOT\n");
}

void PrintVisitor::sqrNode() {
	output.append("^2\n");
}

void PrintVisitor::multNode() {
	output.append("*\n");
}

void PrintVisitor::subNode() {
	output.append("-\n");
}

void PrintVisitor::addNode() {
	output.append("+\n");
}

void PrintVisitor::opNode(Op* op) {
	string op_str = to_string((int)op->evaluate());
	output.append(op_str);
	output.append("\n");
}

void PrintVisitor::execute() {
	cout << output;
}
