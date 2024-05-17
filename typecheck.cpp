#include "util.h"
#include "AST.h"
#include "errormsg.h"
#include "typecheck.h"
#include "ST.h"

//
// Change this comment to describe the attributes you'll be using
//  to check types in tiger programs.
//



var_sym_info::var_sym_info(int the_pos, Ty_ty the_type) : pos(the_pos)
{
    // The bit after the single ":" above initializes "pos" with the value "the_pos".
    // It's a lot like putting "pos = the_pos;" in the body,
    //  but the latter would first build a null "pos" and then re-define it.

    // Just to do something in the example, we'll ensure that whatever_else isn't negative:
        type = the_type;
        locationInFrame = -1;
}

var_sym_info::var_sym_info(int the_pos, Ty_ty the_type, int location_in_frame) : pos(the_pos)
{
    // The bit after the single ":" above initializes "pos" with the value "the_pos".
    // It's a lot like putting "pos = the_pos;" in the body,
    //  but the latter would first build a null "pos" and then re-define it.

    // Just to do something in the example, we'll ensure that whatever_else isn't negative:
    type = the_type;
    locationInFrame = location_in_frame;
}
//struct Ty_field_  {Symbol name; Ty_ty ty;};
//struct Ty_fieldList_ {Ty_field head; Ty_fieldList tail; string str();};
Ty_ty type_of_div =
Ty_Function(Ty_Int(), // return
Ty_FieldList(Ty_Field(to_Symbol("div1"), Ty_Int()), // b
             Ty_FieldList(Ty_Field(to_Symbol("div2"), Ty_Int()), // e
                          0))
);

//cout << "type of power is: " << to_String(type_of_power) << endl;
//cout << "is power a function? " << (type_of_power->kind == Ty_function ? "yes" : "no --- bother!") << endl;
//cout << "return type of power is: " << to_String(type_of_power->u.function.return_type) << endl;
//cout << "is type of power == Ty_Function( ... same stuff as before ...)? " <<
//((type_of_power ==
//Ty_Function(Ty_Int(), // return
//Ty_FieldList(Ty_Field(0, Ty_Int()), // b
//             Ty_FieldList(Ty_Field(0, Ty_Int()), // e
//                          0))))
//? "Yes ... Dave is surprised" : "No ... if we want to compare more interesting types, we'll need a better function") <<
//endl;

Ty_ty type_of_mod =
        Ty_Function(Ty_Int(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_Int()), // b
                                 Ty_FieldList(Ty_Field(to_Symbol("p2"), Ty_Int()), // e
                                              0))
        );
Ty_ty type_of_print =
        Ty_Function(Ty_Void(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_String()), // x ... note that parameter name is just for debugging/error messages
                                 0)
        );
Ty_ty type_of_printint =
        Ty_Function(Ty_Void(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_Int()), // x ... note that parameter name is just for debugging/error messages
                                 0)
        );
Ty_ty type_of_ord =
        Ty_Function(Ty_String(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_Int()), // b
                                 0)
        );
Ty_ty type_of_chr =
        Ty_Function(Ty_Int(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_String()), // b
                                 0)
        );
Ty_ty type_of_size =
        Ty_Function(Ty_Int(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_String()), // b
                                 0)
        );
Ty_ty type_of_substring =
        Ty_Function(Ty_String(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_String()), // b
                                 Ty_FieldList(Ty_Field(to_Symbol("p2"), Ty_Int()), // e
                                              Ty_FieldList(Ty_Field(to_Symbol("p3"), Ty_Int()), // e
                                                           0)))
        );
Ty_ty type_of_tstrcmp =
        Ty_Function(Ty_Int(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_String()), // b
                                 Ty_FieldList(Ty_Field(to_Symbol("p2"), Ty_String()), // e
                                              0))
        );
Ty_ty type_of_concat =
        Ty_Function(Ty_String(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_String()), // b
                                 Ty_FieldList(Ty_Field(to_Symbol("p2"), Ty_String()), // e
                                              0))
        );
Ty_ty type_of_not =
        Ty_Function(Ty_Int(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_Int()), // b
                                 0)
        );
Ty_ty type_of_getchar_ord =
        Ty_Function(Ty_Int(), // return
                    Ty_FieldList(Ty_Field(0, Ty_Void()), // b
                                 0)
        );
Ty_ty type_of_flush =
        Ty_Function(Ty_Void(), // return
                    Ty_FieldList(Ty_Field(0, Ty_Void()), // b
                                 0)
        );
Ty_ty type_of_getchar =
        Ty_Function(Ty_String(), // return
                    Ty_FieldList(Ty_Field(0, Ty_Void()), // b
                                 0)
        );
Ty_ty type_of_ungetchar =
        Ty_Function(Ty_String(), // return
                    Ty_FieldList(Ty_Field(0, Ty_Void()), // b
                                 0)
        );
Ty_ty type_of_getline =
        Ty_Function(Ty_String(), // return
                    Ty_FieldList(Ty_Field(0, Ty_Void()), // b
                                 0)
        );
Ty_ty type_of_getint =
        Ty_Function(Ty_Int(), // return
                    Ty_FieldList(Ty_Field(0, Ty_Void()), // b
                                 0)
        );
Ty_ty type_of_putchar_ord =
        Ty_Function(Ty_Void(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_Int()), // b
                                 0)
        );
Ty_ty type_of_printbool =
        Ty_Function(Ty_Void(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_Bool()), // b
                                 0)
        );
Ty_ty type_of_println =
        Ty_Function(Ty_Void(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_String()), // b
                                 0)
        );
Ty_ty type_of_exit =
        Ty_Function(Ty_Void(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_Int()), // b
                                 0)
        );
Ty_ty type_of_malloc =
        Ty_Function(Ty_Int(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_Int()), // b
                                 0)
        );
Ty_ty type_of_free =
        Ty_Function(Ty_Void(), // return
                    Ty_FieldList(Ty_Field(to_Symbol("p1"), Ty_Int()), // b
                                 0)
        );
ST callsDictionary =
        ST_example( { std::pair(to_Symbol("print"), var_sym_info(0, type_of_print)),
                      std::pair(to_Symbol("printint"), var_sym_info(0, type_of_printint)),
                      std::pair(to_Symbol("div"), var_sym_info(0, type_of_div)),
                      std::pair(to_Symbol("mod"), var_sym_info(0, type_of_mod)),
                      std::pair(to_Symbol("ord"), var_sym_info(0, type_of_ord)),
                      std::pair(to_Symbol("chr"), var_sym_info(0, type_of_chr)),
                      std::pair(to_Symbol("size"), var_sym_info(0, type_of_size)),
                      std::pair(to_Symbol("substring"), var_sym_info(0, type_of_substring)),
                      std::pair(to_Symbol("concat"), var_sym_info(0, type_of_concat)),
                      std::pair(to_Symbol("tstrcmp"), var_sym_info(0, type_of_tstrcmp)),
                      std::pair(to_Symbol("not"), var_sym_info(0, type_of_not)),
                      std::pair(to_Symbol("getchar_ord"), var_sym_info(0, type_of_getchar_ord)),
                      std::pair(to_Symbol("putchar_ord"), var_sym_info(0, type_of_putchar_ord)),
                      std::pair(to_Symbol("flush"), var_sym_info(0, type_of_flush)),
                      std::pair(to_Symbol("println"), var_sym_info(0, type_of_println)),
                      std::pair(to_Symbol("getchar"), var_sym_info(0, type_of_getchar)),
                      std::pair(to_Symbol("ungetchar"), var_sym_info(0, type_of_ungetchar)),
                      std::pair(to_Symbol("getline"), var_sym_info(0, type_of_getline)),
                      std::pair(to_Symbol("exit"), var_sym_info(0, type_of_exit)),
                      std::pair(to_Symbol("malloc"), var_sym_info(0, type_of_malloc)),
                      std::pair(to_Symbol("free"), var_sym_info(0, type_of_free)),
                      std::pair(to_Symbol("getint"), var_sym_info(0, type_of_getint)),
                      std::pair(to_Symbol("printbool"), var_sym_info(0, type_of_printbool))
});
//ST
ST<var_sym_info> A_forExp_::st_vars_in_me(AST_node_ *which_child) {
    if (which_child == _hi) {
        return this->parent()->st_vars_in_me(this);
    } else if (which_child == _lo) {
        return this->parent()->st_vars_in_me(this);
    } else {
        ST new_st = ST_example(std::pair(this->_var, var_sym_info(0, Ty_Int(), this->stack_size_in_me() - 2)));
        new_st = MergeAndShadow(new_st, this->parent()->st_vars_in_me(this));
        return new_st;
    }
}
//ST<var_sym_info> A_varDec_::st_vars_in_me(AST_node_ *which_child) {
//        ST new_st = ST_example(std::pair(this->_var, var_sym_info(0, Ty_Int(), this->stack_size_in_me() - 2)));
//        new_st = MergeAndShadow(new_st, this->parent()->st_vars_in_me(this));
//        return new_st;
//}

//ST<var_sym_info> A_letExp_::st_vars_in_me(AST_node_ *which_child) {
//        return this->parent()->st_vars_in_me(this);
//}


ST<var_sym_info> AST_node_::st_vars_in_me(AST_node_ *which_child) {
    return this->parent()->st_vars_in_me(this);
}

ST<var_sym_info> A_root_::st_vars_in_me(AST_node_ *which_child) {
    return callsDictionary;
}

int A_simpleVar_::getVarLocationInFrame() {
    try {
        return lookup(_sym, this->st_vars_in_me(this)).locationInFrame;
    } catch (const undefined_symbol &missing) {
        EM_error("Error:cannot find variable in symbol table", true);
        return -1;
    }
}

Ty_ty AST_node_::checkType() {
    EM_error("using type check function on something that does not have a AST_node");
    return Ty_Error();
}
Ty_ty A_exp_::checkType() {
    EM_error("using type check function on something that does not have a A_exp");
    return Ty_Error();
}
Ty_ty A_root_::checkType() {
    return this->main_expr->checkType();
}
Ty_ty A_stringExp_::checkType() {
    return Ty_String();
}
Ty_ty A_intExp_::checkType() {
    return Ty_Int();
}
Ty_ty A_boolExp_::checkType() {
    return Ty_Bool();
}
Ty_ty A_seqExp_::checkType() {
    if (_seq == nullptr) {
        return Ty_Void();
    }
    return this->_seq->checkType();
}
Ty_ty A_opExp_::checkType() {
    if (this->_left->checkType() != Ty_Int()) {
        EM_error("Error: Type check failed left of op_exp is not integer", true);
        return Ty_Error();
    } else if (this->_left->checkType() !=  this->_right->checkType()) {
        EM_error("Error: Type check failed left and right of op_exp not the same type", true);
        return Ty_Error();
    } else {
        if(this->_oper == A_ltOp || this->_oper == A_leOp || this->_oper == A_gtOp || this->_oper == A_geOp || this->_oper == A_eqOp || this->_oper == A_neqOp){
            return Ty_Bool();
        }
        return this->_left->checkType();
    }
}
Ty_ty A_expList_::checkType() {
//    if (this->_head->checkType() == Ty_Void()) {
//        // EM_error("Error: Type check failed null exp list", true);
//        //return Ty_Error();
//        return Ty_Void();
//    }
    if (this->_head == nullptr) {
        EM_error("Error: Type check failed null exp list", true);
        return Ty_Error();
    } else if(this->_tail_or_null == nullptr) {
        return this->_head->checkType();
    } else {
        A_expList hold = this->_tail_or_null;
        while(hold->_tail_or_null != nullptr) {
            hold = hold->_tail_or_null;
        }
        return hold->_head->checkType();
    }
}
Ty_ty A_callExp_::checkType() {
    int parem = 0;
    A_expList list = this->_args_or_null;
    while ( list != nullptr){
        parem++;
        list = list->_tail_or_null;
    }
    list = this->_args_or_null;
    if (parem == 3) {
        if(this->_args_or_null->_head->checkType() != lookup(_func,callsDictionary).type->u.function.parameter_types->head->ty) {
            EM_error("Error invalid parameter1 types");
        }
        else if(this->_args_or_null->_tail_or_null->_head->checkType() != lookup(_func,callsDictionary).type->u.function.parameter_types->tail->head->ty) {
            EM_error("Error invalid parameter2 types");
        } else if(this->_args_or_null->_tail_or_null->_tail_or_null->_head->checkType() != lookup(_func,callsDictionary).type->u.function.parameter_types->tail->tail->head->ty) {
            EM_error("Error invalid parameter3 types");
        }
    } else if (parem == 2) {
        if(this->_args_or_null->_head->checkType() != lookup(_func,callsDictionary).type->u.function.parameter_types->head->ty) {
            EM_error("Error invalid parameter1 types");
        }
        else if(this->_args_or_null->_tail_or_null->_head->checkType() != lookup(_func,callsDictionary).type->u.function.parameter_types->tail->head->ty) {
            EM_error("Error invalid parameter2 types");
        }
    } else if (parem == 1) {
        if(this->_args_or_null->_head->checkType() != lookup(_func,callsDictionary).type->u.function.parameter_types->head->ty) {
            EM_error("Error invalid parameter1 types");
        }
    } else if (parem == 0) {
        if(Ty_Void() != lookup(_func,callsDictionary).type->u.function.parameter_types->head->ty) {
            EM_error("Error invalid parameter0 types");
        }
}
    if (lookup(_func,callsDictionary).type->kind == Ty_function) {
        return lookup(_func,callsDictionary).type->u.function.return_type;
    } else {
        EM_error("Error:function types", true);
        return Ty_Error();
    }
//    cout << "type of power is: " << to_String(type_of_power) << endl;
//    cout << "is power a function? " << (type_of_power->kind == Ty_function ? "yes" : "no --- bother!") << endl;
//    cout << "return type of power is: " << to_String(type_of_power->u.function.return_type) << endl;
//    cout << "is type of power == Ty_Function( ... same stuff as before ...)? " <<
//    if (lookup(_func,callsDictionary).type->kind == Ty_function) {
//        return lookup(_func,callsDictionary).type->u.function.return_type;
//    } else {
//        EM_error("Error:function types", true);
//        return Ty_Error();
//    }
//    if (Symbol_to_string(_func) == "mod" || Symbol_to_string(_func) == "div") {
//        if (_args_or_null->checkType() != Ty_Int()) {
//            EM_error("Error: mod and div need int types", true);
//            return Ty_Error();
//        } else {
//            return _args_or_null->checkType();
//        }
//    } else if (Symbol_to_string(_func) == "print") {
//        if (_args_or_null->checkType() != Ty_String()) {
//            EM_error("Error:print need string types", true);
//            return Ty_Error();
//        } else {
//            return _args_or_null->checkType();
//        }
//    } else if (Symbol_to_string(_func) == "printint") {
//        if (_args_or_null->checkType() != Ty_Int()) {
//            EM_error("Error:printint need int types", true);
//            return Ty_Error();
//        } else {
//            return _args_or_null->checkType();
//        }
//    } else {
//        EM_error("Error: function not recognized for checkType", true);
//        return Ty_Error();
//    }
}
Ty_ty A_ifExp_::checkType() {
    if (_test->checkType() != Ty_Bool()) {
        EM_error("Error: if statement types not legal, needs condition bool", true);
        return Ty_Error();
    } else if (( _else_or_null != nullptr && _then->checkType()!= _else_or_null->checkType())) {
        EM_error("Error: if statement types not legal, then and else are not same type", true);
        return Ty_Error();
    } else {
        if (_else_or_null == nullptr) {
            return Ty_Void();
        }
        return _then->checkType();
    }
}

Ty_ty A_whileExp_::checkType() {
    if (_test->checkType() != Ty_Bool()) {
        EM_error("Error: while statement types not legal, needs condition bool", true);
        return Ty_Error();
    } else {
        return Ty_Void();
    }
}


Ty_ty A_forExp_::checkType() {
    if (_hi->checkType() != Ty_Int() && _lo->checkType() != Ty_Int()) {
        EM_error("Error: bounds is not type int", true);
        return Ty_Error();
    } if (_hi <= _lo) {
        EM_error("Error: lower bound is higher than upper bound", true);
        return Ty_Error();
    } else {
        return Ty_Void();
    }
}

Ty_ty A_breakExp_::checkType() {
    return Ty_Void();
}

Ty_ty A_varExp_::checkType() {
    return _var->checkType();
}

Ty_ty A_simpleVar_::checkType() {
    return Ty_Int();
}

Ty_ty A_letExp_::checkType() {
    EM_error("Error:COMPILER HAS NOT MADE IT THIS FAR :(", true);
    return _body->checkType();
}

Ty_ty A_decList_::checkType() {
    if (this->_head == nullptr) {
        EM_error("Error: Type check failed null exp list", true);
        return Ty_Error();
    } else if(this->_tail == nullptr) {
        return this->_head->checkType();
    } else {
        A_decList hold = this->_tail;
        while(hold->_tail != nullptr) {
            hold = hold->_tail;
        }
        return hold->_head->checkType();
    }
}
Ty_ty A_varDec_::checkType() {
    return _init->checkType();
}
//       so I'm putting it here.



// The bodies of type checking functions,
//  including any virtual functions you introduce into
//  the AST classes, should go here.


