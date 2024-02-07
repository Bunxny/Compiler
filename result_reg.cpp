#include "AST.h"

/*
 * methods for working with "result_reg" attribute and associates
 */


int    A_exp_::result_reg() {
    if (this->stored_result_reg < 0) this->stored_result_reg = this->init_result_reg();
    return stored_result_reg;
}
string A_exp_::result_reg_s() { // return in string form, e.g. "R2"
    return "R" + std::to_string(this->result_reg());
}


// The keyword "static", used outside of a function or class,
//   means we want a global variable but it's limited-access for only in this file
// The variable next_unique_number is just something that we increment each time we use it.
static int next_unique_number = 1;
int A_exp_::init_result_reg()  // generate unique numbers, starting from 1, each time this is called
{
	// for those who've taken CS355/356, this should be an atomic transaction, in a concurrent environment
	int my_number = next_unique_number;
	next_unique_number = next_unique_number + 1;
	// end of atomic transaction
	return my_number;
}
