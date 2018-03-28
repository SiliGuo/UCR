#include "iterator.h"
//--------------------------------------------------------------------------
// OperatorIterator Class
//--------------------------------------------------------------------------
void OperatorIterator::first() {
    current_ptr = self_ptr->get_left();
}
void OperatorIterator::next() {
    if (!is_done()) {
        if (current_ptr == self_ptr->get_left())
		    current_ptr = self_ptr->get_right();
		else current_ptr = NULL;
	}
}
bool OperatorIterator::is_done() {
    if (current_ptr == NULL) return true;
	else return false;
}
Base* OperatorIterator::current() {
    return current_ptr;
}

//--------------------------------------------------------------------------
// UnaryIterator Class
//--------------------------------------------------------------------------
void UnaryIterator::first() {
    current_ptr = self_ptr->get_left();
}
void UnaryIterator::next() {
	if (!is_done()) current_ptr = NULL;
}
bool UnaryIterator::is_done() {
    if (current_ptr == NULL) return true;
	else return false;
}
Base* UnaryIterator::current() {
    return current_ptr;
}

//--------------------------------------------------------------------------
// NullIterator Class
//--------------------------------------------------------------------------
void NullIterator::first() {
	if (!is_done()) cout << "Error: is_done Flag Error (N)!" << endl;
}
void NullIterator::next() {
	if (!is_done()) cout << "Error: is_done Flag Error (N)!" << endl;
}
bool NullIterator::is_done() {
	return true;
}
Base* NullIterator::current() {
    return current_ptr;
}

//--------------------------------------------------------------------------
// PreorderIterator Class
//--------------------------------------------------------------------------
void PreorderIterator::first() {
    // Empty the stack (just in case we had something leftover from another run)
	while (!iterators.empty()) {
	    iterators.pop();
	}
    // Create an iterator for the Base* that we built the iterator for
	Iterator* it = self_ptr->create_iterator();
    // Initialize that iterator and push it onto the stack
	current_ptr = self_ptr;
	it->first();
	iterators.push(it);
}

void PreorderIterator::next() {
	if (is_done()) return;
    // Create an iterator for the item on the top of the stack
	Iterator* it = iterators.top();
    // As long as the top iterator on the stack is_done(), pop it off the stack and then advance whatever iterator is now on top of the stack
	while (1) {
		it = iterators.top();
		if (!it->is_done()) break;
		iterators.pop();
		if (is_done()) break;
	}
    // Initialize the iterator and push it onto the stack
	if (!it->is_done()) {
		current_ptr = it->current();
		Iterator* temp = current_ptr->create_iterator();
		temp->first();
		iterators.push(temp);
		it->next();
	}

//	/* Test current_ptr */
//	cout << "\ncp = ";
//	current_ptr->print();

}

bool PreorderIterator::is_done() {
    // Return true if there are no more elements on the stack to iterate
	if (iterators.empty()) return true;
	else return false;
}

Base* PreorderIterator::current() {
    // Return the current for the top iterator in the stack
	return current_ptr;
}
