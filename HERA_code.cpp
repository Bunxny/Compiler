#include "AST.h"

/*
 * HERA_code methods
 */
/*/*hi*/

const string indent_math = "    ";  // might want to use something different for, e.g., branches


string AST_node_::HERA_code()  // Default used during development; could be removed in final version
{
	string message = "HERA_code() requested for AST node type not yet having a HERA_code() method";
	EM_error(message);
	return "#error " + message;  //if somehow we try to HERA-C-Run this, it will fail
}


string A_root_::HERA_code()
{
	return "CBON()\n\n" + main_expr->HERA_code();  // was SETCB for HERA 2.3
}



string A_intExp_::HERA_code()
{
	return indent_math + "SET(" + result_reg_s() + ", " + str(value) + ")\n";
}


string A_opExp_::HERA_code()
{
    string leftCode  = _left->HERA_code();
    string rightCode = _right->HERA_code();

    string HERA_op;
    if (this->_oper == A_plusOp) {
        HERA_op = "ADD";
    } else if (this->_oper == A_timesOp) {
        HERA_op = "MUL";
    } else if (this->_oper == A_minusOp) {
        HERA_op = "SUB";
    } else {
        EM_error("Unhandled case in HERA_math_op");
        return "Oops_unhandled_hera_math_op";
    }

	string myCode = indent_math +
	        (HERA_op + "(" +
			    		this->result_reg_s() + ", " +
				    	_left->result_reg_s() + ", " +
					    _right->result_reg_s() + ")\n");

    return leftCode + rightCode + myCode;
	// Or, equivalently,
	// return _left->HERA_code() + _right->HERA_code() + my_code;
}

string A_callExp_::HERA_code() {
        string returnString = this->_args->_head->HERA_code() + "\n";
        returnString += indent_math + "MOVE(R1, " + this->_args->_head->result_reg_s() + ")\n";
        returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")";
        return returnString;
}
string A_stringExp_::HERA_code()
{
    string returnString = indent_math + "DLABEL(the_string)\n";
    returnString += indent_math + "LP_STRING(" +this->value+ ")\n";
    returnString += indent_math + "SET( R1, the_string);";
    return returnString;
}

string A_expList_::HERA_code()
{
    string returnString = _head->HERA_code();
    if(_tail != nullptr){
        returnString += indent_math + _tail->HERA_code();
    }
    return returnString;
}

string A_seqExp_::HERA_code()
{
    string returnString = _seq->HERA_code();
    returnString += "MOVE(" + this->result_reg_s() + "," + this->_seq->last_elist_exp()->result_reg_s() +")\n";
    return returnString;
}

