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

bool AST_node_::amIInLoop()  // Default used during development; could be removed in final version
{
    return this->parent()->amIInLoop();
}

bool A_whileExp_::amIInLoop()  // Default used during development; could be removed in final version
{
    return true;
}
bool A_forExp_::amIInLoop()  // Default used during development; could be removed in final version
{
    return true;
}
bool A_root_::amIInLoop()  // Default used during development; could be removed in final version
{
    return false;
}

string AST_node_::getEndLabel()  // Default used during development; could be removed in final version
{
    return this->parent()->getEndLabel();
}

string A_whileExp_::getEndLabel()  // Default used during development; could be removed in final version
{
    return this->endLabel();
}
string A_forExp_::getEndLabel()  // Default used during development; could be removed in final version
{
    return this->endLabel();
}
string A_root_::getEndLabel()  // Default used during development; could be removed in final version
{
    string message = "No loops to go through to get end label";
    EM_error(message);
    return "#error " + message;  //if somehow we try to HERA-C-Run this, it will fail
}

string A_stringExp_::HERA_code()
{
    Ty_ty typeCheck = this->checkType();
    if( uniqueLabel == "") {
        this->uniqueLabel = next_string();
    }
    string returnString = indent_math + "SET(" + this->result_reg_s() + "," + uniqueLabel +")\n";
    return returnString;
}
string A_stringExp_::string_data()
{
    if( uniqueLabel == "") {
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
string A_ifExp_::elseLabel() { //ex
    if (this->else_Label == "") {
        else_Label = next_string();
    }
    return else_Label;
}
string A_ifExp_::HERA_code() {

    if(endLabel == "") {
        endLabel = next_string();
    }
    string returnString = _test->HERA_code();
    returnString +=  indent_math + "CMP(" + this->_test->result_reg_s() + ", R0 )\n";
    returnString +=  indent_math + "BZ(ELSE" + this->elseLabel() + ")\n";
    returnString += _then->HERA_code();
    returnString += indent_math + "MOVE(" + this->result_reg_s() + "," + _then->result_reg_s() + ")\n";
    returnString +=  indent_math + "BR(END"+ endLabel + ")\n";
    returnString +=  indent_math + "LABEL(ELSE" + elseLabel() +")\n";
    if(_else_or_null != nullptr) {
        returnString += _else_or_null->HERA_code();
        returnString += indent_math + "MOVE(" + this->result_reg_s() + "," + _else_or_null->result_reg_s() + ")\n";
    }
    returnString +=  indent_math + "LABEL(END" + endLabel + ")\n";
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

string A_forExp_::endLabel() { //ex
    if (this->end_Label == "") {
        end_Label = "forEndLabel" + next_string();
    }
    return end_Label;
}

string A_whileExp_::endLabel() {
    if (this->end_Label == "") {
        end_Label = "whileEndLabel" + next_string();}
    return end_Label;
}

string A_whileExp_::startLabel() {
    if (this->start_Label == "") {
        start_Label = "whileStartLabel" + next_string();}
    return start_Label;
}

string A_whileExp_::HERA_code() {
    string returnString =  indent_math + "LABEL("+ this->startLabel() +")\n";
    returnString += _test->HERA_code();
    returnString +=  indent_math + "CMP(" + this->_test->result_reg_s() + ", R0 )\n";
    //if zero/false end
    returnString +=  indent_math + "BZ(" + this->endLabel() + ")\n";
    //body
    returnString += _body->HERA_code();
    //go back to start
    returnString +=  indent_math + "BR(" + this->startLabel() + ")\n";
    returnString +=  indent_math + "LABEL("+ this->endLabel() +")\n";
    return returnString;
}
string A_whileExp_::string_data()
{
    string returnString = this->_test->string_data();
    returnString += this->_body->string_data();
    return returnString;
}

string A_breakExp_::HERA_code()
{
    string returnString = "";
    if(this->amIInLoop() == false){
        EM_error("Not in loop", true);
    } else {
        returnString ="BR(" + this->getEndLabel() + ")";
    }
    return returnString;
}
string A_breakExp_::string_data()
{
    string returnString = "";
    return returnString;
}

string A_opExp_::HERA_code() {
    Ty_ty typeCheck = this->checkType();
    string leftCode = _left->HERA_code();
    string move = indent_math + "MOVE(" + this->result_reg_s() + "," + _left->result_reg_s() + ")\n";
    string rightCode = _right->HERA_code();
    if(brTrue == "") {
        brTrue = "thenLabel" + next_string();
    }
    if(brFalse== "") {
        brFalse = "elseLabel" + next_string();
    }
    if(brEnd == "") {
        brEnd = "ifEndLabel"+ next_string();
    }
    string HERA_op;
    if (this->_oper == A_plusOp) {
        HERA_op = "ADD";
    } else if (this->_oper == A_timesOp) {
        HERA_op = "MUL";
    } else if (this->_oper == A_minusOp) {
        HERA_op = "SUB";
    } else if (this->_oper == A_ltOp | this->_oper == A_leOp | this->_oper == A_gtOp | this->_oper == A_geOp|
                this->_oper == A_eqOp| this->_oper == A_neqOp) {
        String opCode = "";
        if (_right->result_reg() > _left->result_reg()) {
             opCode += rightCode + move + leftCode;
        } else {
             opCode += leftCode + move + rightCode;
        }
        if (this->_left->result_reg_s() == this->_right->result_reg_s()) { //check
            opCode += indent_math + "CMP(" + this->result_reg_s() + "," + this->_right->result_reg_s() + ")\n";
        } else {
            opCode += indent_math + "CMP(" + this->_left->result_reg_s() + "," + this->_right->result_reg_s() + ")\n";
        }
        if (this->_oper == A_ltOp) {
            opCode += indent_math + "BL(" + brTrue + ")\n";
        } else if (this->_oper == A_leOp) {
            opCode += indent_math + "BLE(" + brTrue + ")\n";
        } else if (this->_oper == A_gtOp ) {
            opCode += indent_math + "BG(" + brTrue + ")\n";
        } else if (this->_oper == A_geOp) {
            opCode += indent_math + "BGE(" + brTrue + ")\n";
        } else if (this->_oper == A_eqOp) {
            opCode += indent_math + "BZ(" + brTrue + ")\n";
        } else if (this->_oper == A_neqOp) {
            opCode += indent_math + "BNZ(" + brTrue + ")\n";
        }
        opCode += indent_math + "SET(" + this->result_reg_s() + "," + "0" + ")\n";
        opCode += indent_math + "BR(" + brEnd+ ")\n";
        opCode += indent_math + "LABEL("+ brTrue +")\n";
        opCode += indent_math + "SET(" + this->result_reg_s() + "," + "1" + ")\n";
        opCode += indent_math + "LABEL("+ brEnd +")\n";
        return  opCode;
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
    A_expList argList = _args_or_null;
    while (argList != nullptr) {
        pNum++;
        argList = argList->_tail_or_null;
    }
    string dec;
    if (pNum == 0) {
        dec = str(pNum + 4);
    } else {
        dec = str(pNum + 3);
    }
    string returnString; //= this->_args_or_null->HERA_code() + "\n";//
    if (pNum == 3) {
        returnString += indent_math + "MOVE(FP_alt, SP)\n"
                + indent_math + "INC(SP," + dec + ")\n";
        returnString += this->_args_or_null->_head->HERA_code() //first parem
                       + indent_math + "STORE(R1, 3, FP_alt)\n"
                        + this->_args_or_null->_tail_or_null->HERA_code() //second parem
                       + indent_math + "MOVE( R2, " + this->_args_or_null->_tail_or_null->_head->result_reg_s() + ")\n"
                        + indent_math + "STORE( R2 , 4, FP_alt)\n"
                        + indent_math + "MOVE(R3, " + this->_args_or_null->_tail_or_null->_tail_or_null->_head->result_reg_s() + ")\n"
                        + indent_math + "STORE( R3, 5, FP_alt)\n";
        returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")\n";
        returnString += indent_math + "LOAD(" + this->result_reg_s() + ", 3, FP_alt )\n";
        returnString += indent_math + "DEC(SP," + dec + ")\n";
        return returnString;
    } else if (pNum == 2) {
            returnString +=  indent_math + "MOVE(FP_alt, SP)\n"
                    + indent_math + "INC(SP," + dec + ")\n";
            returnString += this->_args_or_null->_head->HERA_code() //first parem
                           + indent_math + "STORE(" + this->_args_or_null->_head->result_reg_s() + ", 3, FP_alt)\n"
                            + this->_args_or_null->_tail_or_null->HERA_code() //second parem
                           + indent_math + "STORE(" + this->_args_or_null->_tail_or_null->_head->result_reg_s() + ", 4, FP_alt)\n"; //rtnstr was here
            returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")\n";
            returnString += indent_math + "LOAD(" + this->result_reg_s() + ", 3, FP_alt )\n";
            returnString += indent_math + "DEC(SP, " + dec + ")\n";
            return returnString;
        } else if (pNum == 1) {
            returnString +=  indent_math + "MOVE(FP_alt, SP)\n"
                    + indent_math + "INC(SP," + dec + ")\n";
            returnString += this->_args_or_null->_head->HERA_code() //first parem
                           + indent_math + "STORE(" + this->_args_or_null->_head->result_reg_s() + ", 3, FP_alt)\n";
            returnString +=  indent_math + "MOVE(R1, " + this->result_reg_s() + ")\n";
            returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")\n";
            returnString += indent_math + "LOAD(" + this->result_reg_s() + ", 3, FP_alt )\n";
            returnString += indent_math + "DEC(SP, " + dec + ")\n";
            return returnString;
//            if (this->_args_or_null == nullptr) {
//                returnString += indent_math + "CALL(FP_alt ," + Symbol_to_string(_func) + ")\n";
//            } else {
//                string returnString = this->_args_or_null->HERA_code() + "\n";
//                returnString += indent_math + "MOVE(R1, " + this->_args_or_null->_head->result_reg_s() + ")\n";
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
    if (_args_or_null == nullptr) {
        return "";
    }
    string returnString = this->_args_or_null->string_data() + "\n";
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
    if(_tail_or_null != nullptr){
        returnString += indent_math + _tail_or_null->HERA_code();
    }
    return returnString;
}
string A_expList_::string_data()
{
    if(_head == nullptr){
        return "";
    }
    string returnString = this->_head->string_data();
    if(_tail_or_null != nullptr){
        returnString += this->_tail_or_null->string_data();
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

