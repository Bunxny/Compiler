#include "AST.h"

/*
 * methods for working with "result_reg" attribute and associates
 */


int    A_exp_::result_reg() {
    if (this->stored_result_reg < 0) this->stored_result_reg = this->init_result_reg();
    if (this->stored_result_reg > 11) {
        EM_error("Uses over 12 registers cannot compute", true);
    }
    return stored_result_reg;
}
string A_exp_::result_reg_s() { // return in string form, e.g. "R2"
    return "R" + std::to_string(this->result_reg());
}

A_exp A_expList_::last_elist_exp() {
    A_exp front = this->_head;
    A_expList body = this->_tail_or_null;
    while(body != nullptr) {
        front = body->_head;
        body = body->_tail_or_null;
    }
    return front;
}


// The keyword "static", used outside of a function or class,
//   means we want a global variable but it's limited-access for only in this file
// The variable next_unique_number is just something that we increment each time we use it.
static int next_unique_number = 1;
int A_exp_::init_result_reg()  // generate unique numbers, starting from 1, each time this is called
{
    EM_error("Oops, something still needs to provide an init_result_reg() but isn't.");
	// for those who've taken CS355/356, this should be an atomic transaction, in a concurrent environment
	int my_number = next_unique_number;
	next_unique_number = next_unique_number + 1;
	// end of atomic transaction
	return my_number;
}
int A_var_::init_result_reg()  // generate unique numbers, starting from 1, each time this is called
{
    EM_error("Oops, something still needs to provide an init_result_reg() but isn't.");
    return -1;
}

string A_var_::result_reg_s() { // return in string form, e.g. "R2"
    return "R" + std::to_string(this->init_result_reg());
}


static int next_unique_String_num = 1;
string A_exp_::next_string()  // generate unique numbers, starting from 1, each time this is called
{
    String my_string = "string" + std::to_string(next_unique_String_num);
    next_unique_String_num = next_unique_String_num + 1;
    // end of atomic transaction
    return my_string;
}

//static int next_unique_branch_num = 1;
//string A_exp_::next_branch_string()  // generate unique numbers, starting from 1, each time this is called
//{
//    String my_string = "branch" + std::to_string(next_unique_String_num);
//    next_unique_String_num = next_unique_branch_num + 1;
//    // end of atomic transaction
//    return my_string;
//}

int A_intExp_::init_result_reg()
{
    return 1;  // This saves 1-3 for parameters
}
int A_stringExp_::init_result_reg()
{
    return 1;  // This saves 1-3 for parameters
}
int A_boolExp_::init_result_reg()
{
    return 1;
}
int A_opExp_::init_result_reg()
{
    int ret = _left->result_reg();
    if(_left->result_reg() == _right->result_reg() ) {
        ret++;
    } else {
        ret = std::max(_left->result_reg(), _right->result_reg());
    }
    return ret; // for now ... ToDo: needs to depend on: the register numbers of the children (operands)
    // ToDo: Also, need to add those "MOVE" instructions, this goes in the A_opExp::HERA_code
}

int A_expList_::init_result_reg(){
    if(this->_tail_or_null != nullptr){
        return std::max(this->_head->result_reg(), this->_tail_or_null->init_result_reg());
    } else {
        return this->_head->result_reg();
    }
}

int A_seqExp_::init_result_reg(){
    if (_seq == nullptr) {
        return 0;
    }
    return this->_seq->init_result_reg();
}

int A_callExp_::init_result_reg(){
    if (_args_or_null == nullptr) {
        return 1;
    }
    return this->_args_or_null->init_result_reg();
}


int A_ifExp_::init_result_reg(){
    if (_else_or_null == nullptr) {
        return std::max(_then->result_reg(), _test->result_reg());
    }
    int max = std::max(_then->result_reg(), _else_or_null->result_reg());
    return std::max(max, _test->result_reg());
}

int A_whileExp_::init_result_reg(){
    return std::max(_body->result_reg(), _test->result_reg());
}

int A_forExp_::init_result_reg(){
    int max = std::max(_lo->result_reg(), _hi->result_reg());
    return std::max(max, _body->result_reg()) + 1; //adding one to make sure lo and this not the same
}

int A_breakExp_::init_result_reg(){
    return 0;
}

int A_varExp_::init_result_reg(){
    return _var->init_result_reg();
}

int A_simpleVar_::init_result_reg(){
    return 1;
}

//int A_fieldVar_::init_result_reg(){
//    return this->init_result_reg();
//}

//int A_subscriptVar_::init_result_reg(){
//    return this->init_result_reg();
//}