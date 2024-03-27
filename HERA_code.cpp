#include "AST.h"

/*
 * HERA_code methods
 */
/*/*hi*/

const string indent_math = "    ";  // might want to use something different for, e.g., branches


string AST_node_::HERA_code()  // Default used during development; could be removed in final version
{
    Ty_ty typeCheck = this->checkType();
	string message = "HERA_code() requested for AST node type not yet having a HERA_code() method";
	EM_error(message);
	return "#error " + message;  //if somehow we try to HERA-C-Run this, it will fail
}
string AST_node_::string_data()  // Default used during development; could be removed in final version
{
    string message = "string_data() requested for AST node type not yet having a string_data() method";
    EM_error(message);
    return "#error " + message;  //if somehow we try to HERA-C-Run this, it will fail
}

string A_stringExp_::HERA_code()
{
    Ty_ty typeCheck = this->checkType();
    if( uniqueLabel == ""){
        this->uniqueLabel = next_string();
    }
    string returnString = indent_math + "SET(" + this->result_reg_s() + "," + uniqueLabel +")\n";
    return returnString;
}
string A_stringExp_::string_data()
{
    if( uniqueLabel == ""){
        this->uniqueLabel = next_string();
    }
    string returnString = indent_math + "DLABEL(" + uniqueLabel +")\n";
    returnString += indent_math + "TIGER_STRING(" +this->value+ ")";
    return returnString;
}



string A_root_::HERA_code()
{
    Ty_ty typeCheck = this->checkType();
	return "#include <Tiger-stdlib-stack-data.hera>\n" +
    main_expr->string_data()+ "CBON()\n\n" + main_expr->HERA_code() + "\nHALT()\n" + "#include <Tiger-stdlib-stack.hera>\n";  // was SETCB for HERA 2.3
}



string A_intExp_::HERA_code()
{
    Ty_ty typeCheck = this->checkType();
    return  indent_math + "SET(" + result_reg_s() + ", " + str(value) + ")\n";
}

string A_intExp_::string_data()
{
    string returnString = "";
    return returnString;
}

string A_boolExp_::HERA_code()
{
    Ty_ty typeCheck = this->checkType();
    if (this->value) {
        return indent_math + "SET(" + result_reg_s() + ", " + str(1) + ")\n";
    } else {
        return indent_math + "SET(" + result_reg_s() + ", " + str(0) + ")\n";
    }
}
string A_boolExp_::string_data()
{
    string returnString = "";
    return returnString;
}

string A_ifExp_::elseLabel() {
    if (this->else_Label == "") {
        else_Label = next_string();}
    return else_Label;
}
string A_ifExp_::HERA_code() {

    if(endLabel == "") {
        endLabel = next_string();
    }
    string returnString = _test->HERA_code();
    returnString +=  indent_math + "CMP(" + this->_test->result_reg_s() + ", R0 )\n";
    returnString +=  indent_math + "BZ(" + this->elseLabel() + ")\n";
    returnString += _then->HERA_code();
    returnString +=  indent_math + "BR(" + endLabel + ")\n";
    returnString +=  indent_math + "LABEL("+ elseLabel() +")\n";
    if(_else_or_null != nullptr) {
        returnString += _else_or_null->HERA_code();
    }
    returnString +=  indent_math + "LABEL(" + endLabel + ")\n";
    return returnString;
    //dividecode += indent_math + "SET(R2," + this->_right->result_reg_s() + ")\n";
    //dividecode += indent_math + "CALL(FP_alt ," + "div" + ")\n";
}
string A_ifExp_::string_data()
{
    string returnString = this->_test->string_data();
    returnString += this->_then->string_data();
    if(_else_or_null != nullptr) {
        returnString += this->_else_or_null->string_data();
    }
    return returnString;
}


string A_opExp_::HERA_code() {
    Ty_ty typeCheck = this->checkType();
    string leftCode = _left->HERA_code();
    string move = indent_math + "MOVE(" + this->result_reg_s() + "," + _left->result_reg_s() + ")\n";
    string rightCode = _right->HERA_code();

    string HERA_op;
    if (this->_oper == A_plusOp) {
        HERA_op = "ADD";
    } else if (this->_oper == A_timesOp) {
        HERA_op = "MUL";
    } else if (this->_oper == A_minusOp) {
        HERA_op = "SUB";
    } else if (this->_oper == A_divideOp) {
//        HERA_op = "";
//        string dividecode = indent_math + "MOVE(R1," + this->result_reg_s() + ")\n";
//        dividecode += indent_math + "MOVE(R2," + this->_right->result_reg_s() + ")\n";
//        dividecode += indent_math + "CALL(FP_alt ," + "div" + ")\n";
//        dividecode += indent_math + "MOVE(" + this->result_reg_s() + "," + "R1" + ")\n";
//        if (_right->result_reg() > _left->result_reg()) {
//            return rightCode + move + leftCode + dividecode; //div doesnt have heraop
//        } else {
//            return leftCode + move + rightCode + dividecode;
//        }
    } else {
        EM_error("Unhandled case in HERA_math_op");
        return "Oops_unhandled_hera_math_op";
    }
    string myCode;
    if (_right->result_reg() > _left->result_reg()) {
        //BASically heraop(R,R)
        myCode = indent_math +
                 (HERA_op + "(" +
                  this->result_reg_s() + ", " +
                  _left->result_reg_s() + ", " +
                  _right->result_reg_s() + ")\n");
        return rightCode + leftCode + myCode;
    } else {
        myCode = indent_math +
                 (HERA_op + "(" +
                  this->result_reg_s() + ", " +
                  this->result_reg_s() + ", " +
                  _right->result_reg_s() + ")\n");
        return leftCode + move + rightCode + myCode;
    }
	// Or, equivalently,
	// return _left->HERA_code() + _right->HERA_code() + my_code;
}
string A_opExp_::string_data()
{
    string returnString = this->_left->string_data();
    returnString += this->_right->string_data();
    return returnString;
}

string A_callExp_::HERA_code() {
    Ty_ty typeCheck = this->checkType();
    int pNum = 0;
    A_expList argList = _args;
    while (argList != nullptr) {
        pNum++;
        argList = argList->_tail;
    }
    string dec = str(pNum + 3);
    string returnString; //= this->_args->HERA_code() + "\n";//
    if (pNum == 3) {
        returnString += indent_math + "MOVE(FP_alt, SP)\n"
                + indent_math + "INC(SP," + dec + ")\n";
        returnString += this->_args->_head->HERA_code() //first parem
                       +  indent_math + "STORE(R1, 3, FP_alt)\n"
                       +this->_args->_tail->HERA_code() //second parem
                       +  indent_math + "MOVE( R2, " + this->_args->_tail->_head->result_reg_s() + ")\n"
                       +  indent_math + "STORE( R2 , 4, FP_alt)\n"
                       +  indent_math + "MOVE(R3, " + this->_args->_tail->_tail->_head->result_reg_s() + ")\n"
                       +  indent_math + "STORE( R3, 5, FP_alt)\n";
        returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")\n";
        returnString += indent_math + "LOAD(" + this->result_reg_s() + ", 3, FP_alt )\n";
        returnString += indent_math + "DEC(SP," + dec + ")\n";
        return returnString;
    } else if (pNum == 2) {
            returnString +=  indent_math + "MOVE(FP_alt, SP)\n"
                    + indent_math + "INC(SP," + dec + ")\n";
            returnString += this->_args->_head->HERA_code() //first parem
                           +  indent_math + "STORE(" + this->_args->_head->result_reg_s() + ", 3, FP_alt)\n"
                           +this->_args->_tail->HERA_code() //second parem
                           +  indent_math + "STORE("+ this->_args->_tail->_head->result_reg_s() + ", 4, FP_alt)\n"; //rtnstr was here
            returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")\n";
            returnString += indent_math + "LOAD(" + this->result_reg_s() + ", 3, FP_alt )\n";
            returnString += indent_math + "DEC(SP, " + dec + ")\n";
            return returnString;
        } else if (pNum == 1) {
            returnString +=  indent_math + "MOVE(FP_alt, SP)\n"
                    + indent_math + "INC(SP," + dec + ")\n";
            returnString += this->_args->_head->HERA_code() //first parem
                           +  indent_math + "STORE(" + this->_args->_head->result_reg_s() + ", 3, FP_alt)\n";
            returnString +=  indent_math + "MOVE(R1, " + this->result_reg_s() + ")\n";
            returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")\n";
            returnString += indent_math + "LOAD(" + this->result_reg_s() + ", 3, FP_alt )\n";
            returnString += indent_math + "DEC(SP, " + dec + ")\n";
            return returnString;
//            if (this->_args == nullptr) {
//                returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")\n";
//            } else {
//                string returnString = this->_args->HERA_code() + "\n";
//                returnString += indent_math + "MOVE(R1, " + this->_args->_head->result_reg_s() + ")\n";
//                returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")\n";
//            }
//            return returnString;
        } else if (pNum == 0) {
            returnString +=  indent_math + "MOVE(FP_alt, SP)\n"
                    + indent_math + "INC(SP," + dec + ")\n";
            returnString +=  indent_math + "MOVE(R1," + this->result_reg_s() + ")\n";
            returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")\n";
            returnString += indent_math + "LOAD(" + this->result_reg_s() + ", 3, FP_alt )\n";
            returnString += indent_math + "DEC(SP," + dec + ")\n";
            return returnString;
        } else {
        EM_error("\n too many parameters in call" + Symbol_to_string(_func) + " number of paremeters " + str(pNum));
        return "";
    }
}
string A_callExp_::string_data()
{
    if (_args == nullptr) {
        return "";
    }
    string returnString = this->_args->string_data() + "\n";
    return returnString;
}
/*
string A_stringExp_::HERA_code()
{
    string unique_label = next_string();
    string returnString = indent_math + "DLABEL(" + unique_label +")\n";
    returnString += indent_math + "LP_STRING(" +this->value+ ")\n";
    returnString += indent_math + "SET( R1," + unique_label +");";
    return returnString;
}
*/
string A_expList_::HERA_code()
{
    Ty_ty typeCheck = this->checkType();
    string returnString = _head->HERA_code();
//    if(_head == nullptr){
//        return "";
//    }
    if(_head == nullptr){
        return "";
    }
    if(_tail != nullptr){
        returnString += indent_math + _tail->HERA_code();
    }
    return returnString;
}
string A_expList_::string_data()
{
    if(_head == nullptr){
        return "";
    }
    string returnString = this->_head->string_data();
    if(_tail != nullptr){
        returnString += this->_tail->string_data();
    }
    return returnString;
}

string A_seqExp_::HERA_code()
{
    if (_seq == nullptr) {
        return "";
    }
    Ty_ty typeCheck = this->checkType();
    string returnString = _seq->HERA_code();
    returnString += "MOVE(" + this->result_reg_s() + "," + this->_seq->last_elist_exp()->result_reg_s() +")\n";
    return returnString;
}
string A_seqExp_::string_data()
{
    if (_seq == nullptr) {
        return "";
    }
    string returnString = this->_seq->string_data() + "\n";
    return returnString;
}

