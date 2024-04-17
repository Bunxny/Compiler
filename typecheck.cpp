#include "util.h"
#include "AST.h"
#include "errormsg.h"
#include "typecheck.h"
#include "ST.h"

//
// Change this comment to describe the attributes you'll be using
//  to check types in tiger programs.
//


struct call_sym_info { // what do we know about a symbol?
public:
    call_sym_info(int the_pos,  // record the place it was declared, for error messages
            // other attributes could go here, e.g.
                     Ty_ty type

    );
    // leave data public, which is the default for 'struct'
    int pos;
    //int whatever_else;
    Ty_ty type;

    string repr_method();
    string str_method();

};
call_sym_info::call_sym_info(int the_pos, Ty_ty the_type) : pos(the_pos)
{
    // The bit after the single ":" above initializes "pos" with the value "the_pos".
    // It's a lot like putting "pos = the_pos;" in the body,
    //  but the latter would first build a null "pos" and then re-define it.

    // Just to do something in the example, we'll ensure that whatever_else isn't negative:
        type = the_type;
}

typedef ST<call_sym_info> ST_example;
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
        ST_example( { std::pair(to_Symbol("print"),    call_sym_info(0,  type_of_print)),
                      std::pair(to_Symbol("printint"), call_sym_info(0, type_of_printint)),
                      std::pair(to_Symbol("div"),      call_sym_info(0, type_of_div)),
                      std::pair(to_Symbol("mod"),      call_sym_info(0, type_of_mod)),
                      std::pair(to_Symbol("ord"),      call_sym_info(0, type_of_ord)),
                      std::pair(to_Symbol("chr"),      call_sym_info(0, type_of_chr)),
                      std::pair(to_Symbol("size"),      call_sym_info(0, type_of_size)),
                      std::pair(to_Symbol("substring"),      call_sym_info(0, type_of_substring)),
                      std::pair(to_Symbol("concat"),      call_sym_info(0, type_of_concat)),
                      std::pair(to_Symbol("tstrcmp"),      call_sym_info(0, type_of_tstrcmp)),
                      std::pair(to_Symbol("not"),      call_sym_info(0, type_of_not)),
                      std::pair(to_Symbol("getchar_ord"),      call_sym_info(0, type_of_getchar_ord)),
                      std::pair(to_Symbol("putchar_ord"),      call_sym_info(0, type_of_putchar_ord)),
                      std::pair(to_Symbol("flush"),      call_sym_info(0, type_of_flush)),
                      std::pair(to_Symbol("println"),      call_sym_info(0, type_of_println)),
                      std::pair(to_Symbol("getchar"),      call_sym_info(0, type_of_getchar)),
                      std::pair(to_Symbol("ungetchar"),      call_sym_info(0, type_of_ungetchar)),
                      std::pair(to_Symbol("getline"),      call_sym_info(0, type_of_getline)),
                      std::pair(to_Symbol("exit"),      call_sym_info(0, type_of_exit)),
                      std::pair(to_Symbol("malloc"),      call_sym_info(0, type_of_malloc)),
                      std::pair(to_Symbol("free"),      call_sym_info(0, type_of_free)),
                      std::pair(to_Symbol("getint"),      call_sym_info(0, type_of_getint)),
                      std::pair(to_Symbol("printbool"),      call_sym_info(0, type_of_printbool))
} );

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
//    cout << "type of power is: " << to_String(type_of_power) << endl;
//    cout << "is power a function? " << (type_of_power->kind == Ty_function ? "yes" : "no --- bother!") << endl;
//    cout << "return type of power is: " << to_String(type_of_power->u.function.return_type) << endl;
//    cout << "is type of power == Ty_Function( ... same stuff as before ...)? " <<
    if (lookup(_func,callsDictionary).type->kind == Ty_function) {
        return lookup(_func,callsDictionary).type->u.function.return_type;
    } else {
        EM_error("Error:function types", true);
        return Ty_Error();
    }
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

Ty_ty A_breakExp_::checkType() {
    return Ty_Void();
}
//       so I'm putting it here.



// The bodies of type checking functions,
//  including any virtual functions you introduce into
//  the AST classes, should go here.


