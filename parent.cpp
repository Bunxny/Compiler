#include "AST.h"

void A_leafExp_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
	stored_parent = my_parent_or_null_if_i_am_the_root;
}

void A_root_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
	// This has been inlined into the root expression constructor,
	//   so it shouldn't actually be needed again...
	EM_warning("Strange ... called set_parent_pointers_for_me_and_my_descendants for A_root, rather than relying on constructor");
	// otherwise, we would have done this:
	// hccs_assert(my_parent_or_null_if_i_am_the_root == 0);
	// stored_parent = my_parent_or_null_if_i_am_the_root;
	// main_expr->set_parent_pointers_for_me_and_my_descendants(this);
}

void A_opExp_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
	// record my parent
	stored_parent = my_parent_or_null_if_i_am_the_root;
	// now, tell my children to record me as theirs... they'll tell the grandkids
	_right->set_parent_pointers_for_me_and_my_descendants(this);
    _left->set_parent_pointers_for_me_and_my_descendants(this);
}

void A_whileExp_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    // record my parent
    stored_parent = my_parent_or_null_if_i_am_the_root;
    // now, tell my children to record me as theirs... they'll tell the grandkids
    _body->set_parent_pointers_for_me_and_my_descendants(this);
    _test->set_parent_pointers_for_me_and_my_descendants(this);
}

void A_ifExp_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    // record my parent
    stored_parent = my_parent_or_null_if_i_am_the_root;
    // now, tell my children to record me as theirs... they'll tell the grandkids
    if(_else_or_null != nullptr) {
        _else_or_null->set_parent_pointers_for_me_and_my_descendants(this);
    }
    _then->set_parent_pointers_for_me_and_my_descendants(this);
    _test->set_parent_pointers_for_me_and_my_descendants(this);
}


void A_callExp_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    // record my parent
    stored_parent = my_parent_or_null_if_i_am_the_root;
    // now, tell my children to record me as theirs... they'll tell the grandkids
    if(_args_or_null != nullptr) {
        _args_or_null->set_parent_pointers_for_me_and_my_descendants(this);
    }
}

void A_forExp_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    // record my parent
    stored_parent = my_parent_or_null_if_i_am_the_root;
    // now, tell my children to record me as theirs... they'll tell the grandkids
    _lo->set_parent_pointers_for_me_and_my_descendants(this);
    _hi->set_parent_pointers_for_me_and_my_descendants(this);
    _body->set_parent_pointers_for_me_and_my_descendants(this);
}

void A_breakExp_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    // record my parent
    stored_parent = my_parent_or_null_if_i_am_the_root;
    // now, tell my children to record me as theirs... they'll tell the grandkids
}

void A_seqExp_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    // record my parent
    stored_parent = my_parent_or_null_if_i_am_the_root;
    // now, tell my children to record me as theirs... they'll tell the grandkids
    if (_seq != nullptr) {
        _seq->set_parent_pointers_for_me_and_my_descendants(this);
    }
}

void A_expList_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    // record my parent
    stored_parent = my_parent_or_null_if_i_am_the_root;
    // now, tell my childseqren to record me as theirs... they'll tell the grandkids
    _head->set_parent_pointers_for_me_and_my_descendants(this);
    if (_tail_or_null != nullptr) {
        _tail_or_null->set_parent_pointers_for_me_and_my_descendants(this);
    }
}

void A_var_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    stored_parent = my_parent_or_null_if_i_am_the_root;
}

void A_varExp_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    stored_parent = my_parent_or_null_if_i_am_the_root;
    _var->set_parent_pointers_for_me_and_my_descendants(this);
}

void A_letExp_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    stored_parent = my_parent_or_null_if_i_am_the_root;
    _body->set_parent_pointers_for_me_and_my_descendants(this);
    _decs->set_parent_pointers_for_me_and_my_descendants(this);
}

void A_decList_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    // record my parent
    stored_parent = my_parent_or_null_if_i_am_the_root;
    // now, tell my childseqren to record me as theirs... they'll tell the grandkids
    _head->set_parent_pointers_for_me_and_my_descendants(this);
    if (_tail != nullptr) {
        _tail->set_parent_pointers_for_me_and_my_descendants(this);
    }
}


void A_varDec_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent_or_null_if_i_am_the_root)
{
    stored_parent = my_parent_or_null_if_i_am_the_root;
    _init->set_parent_pointers_for_me_and_my_descendants(this);
}




// The following should never be called, but this "general" version
//   lets us compile and test some things without having to fill in the set_parent_pointers stuff first
// Better design would use "= 0" in the AST_node_ class, and not have this function body,
//   except that we want to leave the bulk of the work for the labs...


void AST_node_::set_parent_pointers_for_me_and_my_descendants(AST_node_ *my_parent)
{
	EM_warning("Uh-oh, need to make set_parent_pointers_for_me_and_my_descendants actually do its full job...");
	EM_warning(" rewrite or overrride it, instead of running this code the AST_node_ class.");
}

AST_node_ *AST_node_::get_parent_without_checking()  // NOT FOR GENERAL USE ... this is only for things like checking assertions
{
	return stored_parent;
}
AST_node_ *AST_node_::parent()	// get the parent node, after the 'set parent pointers' pass
{
	precondition("parent pointers have been set" && stored_parent);  // don't get the parent unless it has been set!
	return stored_parent;
}

AST_node_ *A_root_::parent()
{
	EM_error("Called parent() for root node."
		 " This typically happens when A_root has not defined a method for some inherited attribute,\n"
		 " or when you forget the word \"virtual\" for a method at the AST_node_ or A_exp_ level.", true);
	throw "Oops, shouldn't get here, if 'true' is on for 'is this error fatal";
}
