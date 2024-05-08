#ifndef TYPECHECK_H_
#define TYPECHECK_H_
#include "ST.h"
struct var_sym_info { // what do we know about a symbol?
public:
    var_sym_info(int the_pos,  // record the place it was declared, for error messages
            // other attributes could go here, e.g.
                 Ty_ty type

    );
    var_sym_info(int the_pos,  // record the place it was declared, for error messages
            // other attributes could go here, e.g.
                 Ty_ty type,
                 int location_in_frame

    );
    // leave data public, which is the default for 'struct'
    int pos;
    //int whatever_else;
    Ty_ty type;
    int locationInFrame;
    string repr_method();
    string str_method();

};

typedef ST<var_sym_info> ST_example;
#endif /*TYPECHECK_H_*/

