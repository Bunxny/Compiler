#include <stdio.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "errormsg.h"
#include "AST.h"
#include "ST.h"  /* to run ST_test */
#include "tigerParseDriver.h"

#include "lazy.h"   // allow self-test of lazy-evaluation system

/* Turned this off while having trouble switching to C++ approach; this used to work in C version */
#if defined COMPILE_LEX_TEST
// array of token number / token name pairs
static struct {
	int number;
	const char *name;
} toknames[] = {
	{ID, "ID"},
	{STRING, "STRING"},
	{INT, "INT"},
	{COMMA, "COMMA"},
	{COLON, "COLON"},
	{SEMICOLON, "SEMICOLON"},
	{LPAREN, "LPAREN"},
	{RPAREN, "RPAREN"},
	{L_SQUARE_BRACKET, "L_SQUARE_BRACKET"},
	{R_SQUARE_BRACKET, "R_SQUARE_BRACKET"},
	{L_CURLY_BRACE, "L_CURLY_BRACE"},
	{R_CURLY_BRACE, "R_CURLY_BRACE"},
	{DOT, "DOT"},
	{PLUS, "PLUS"},
	{MINUS, "MINUS"},
	{TIMES, "TIMES"},
	{DIVIDE, "DIVIDE"},
	{EQ, "EQ"},
	{NEQ, "NEQ"},
	{LT, "LT"},
	{LE, "LE"},
	{GT, "GT"},
	{GE, "GE"},
	{AND, "AND"},
	{OR, "OR"},
	{ASSIGN, "ASSIGN"},
	{ARRAY, "ARRAY"},
	{IF, "IF"},
	{THEN, "THEN"},
	{ELSE, "ELSE"},
	{WHILE, "WHILE"},
	{FOR, "FOR"},
	{TO, "TO"},
	{DO, "DO"},
	{LET, "LET"},
	{IN, "IN"},
	{END, "END"},
	{OF, "OF"},
	{BREAK, "BREAK"},
	{NIL, "NIL"},
	{FUNCTION, "FUNCTION"},
	{VAR, "VAR"},
	{TYPE, "TYPE"}
};

// function to convert token numbers to printable names
String tokname(int tok) {
	for (unsigned int i = 0; i < sizeof(toknames)/sizeof(*toknames); i++)
	{
		if (toknames[i].number == tok)
			return toknames[i].name;
	}
	return "BAD_TOKEN";
}


extern YYSTYPE yylval;  // global variable set by lexical analyzer

void lex_test()
{
	extern int yylex(void); /* prototype for the lexing function, C style with no parameters */

	int tok;	// token number

	while( (tok=yylex()) != 0)
	{
		cout << tokname(tok) << " (token # " << tok << ")";
		switch(tok)
		{
		case ID:
			cout << " \tvalue is: " << *(yylval.str_attrs.sval) << endl;
			break;
		case STRING:
			cout << " \tvalue in printable form is: " << repr(*(yylval.str_attrs.sval)) <<
				" and in raw form is: " << *(yylval.str_attrs.sval) << endl;
			break;
		case INT:
			cout << " \tvalue is: " << yylval.int_attrs.ival << endl;
			break;
		default:
			cout << endl;
		}
	}
}
#endif

int main(int argc, char **argv)
{
    try {
        bool debug = false, show_ast = false, crash_on_fatal;
#if defined COMPILE_LEX_TEST
        bool just_do_lex_and_then_stop = false;
#endif
        String filename;
        int arg_consumed = 0;

        if (argc>arg_consumed+1 && string(argv[1]).length()>= 2 && (argv[1][0] == '-' && argv[1][1] == 'd')) { // Debug option
            arg_consumed++;
            debug = true;
            if (string(argv[1]).length()>= 3 && argv[1][2] == 'a')
                show_ast = true;
            else if (string(argv[1]).length()>= 3 && argv[1][2] == 'A')
                print_ASTs_with_attributes = show_ast = true;
            else if (string(argv[1]).length()>= 3 && argv[1][2] == 'c')
                crash_on_fatal = true;
#if defined COMPILE_LEX_TEST
            else if (string(argv[1]).length()>= 3 && argv[1][2] == 'l')
                just_do_lex_and_then_stop = true;
#endif
        }

        if (argc>arg_consumed+1)
        {
            arg_consumed++;
            filename = argv[arg_consumed];
        } else {
            cout << "Enter name of file to be compiled (or - for standard input) ";
            // read from stdin to avoid confusing stdin/cin
            char buf[1024];
            scanf("%s", buf);
            filename = buf;
        }

        // open "filename" for reading by lexical scanner,
        // give up after 8 errors,
        // with compiler debugging ON if the "-d" flag was used when we started
        EM_reset(filename, 8, debug, crash_on_fatal);

        EM_debug("Beginning self-test of modules, feel free to comment out these steps if confident.");
        ST_examples(); // confirm examples work
        ST_test();     // internal consistency check
        lazy_test();   // internal consistency check of lazy-evaluation system
        EM_debug("Completed self-test of modules; if no errors/warnings, yay.");

#if defined COMPILE_LEX_TEST
        if (just_do_lex_and_then_stop) {
            lex_test();
            return 0;
        } else
#endif

        // This is kind of a strange use of "while",
        //  but I want a structure in which I run a bunch of lines in order,
        //  once each, but can "break" the sequence at any point.
        // In C++, I have to use "goto", or make a one-trip loop and use "break".

        while (true) {  // always "break" or return, to get out of this one-trip loop
            tigerParseDriver driver;
            int result = driver.parse(filename);
            if (EM_recorded_any_errors()) break;
            if (result != 0) {
                EM_error("Strange result in tiger.cc: parser failed but EM module reported no errors");
                break;
            }
            EM_debug("Parsing Successful", driver.AST->pos());

            driver.AST->set_parent_pointers_for_me_and_my_descendants(0);  // now we can traverse up or down

            // Can do static checks, e.g. type checking, here if we want to do them all before any code generation
            if (show_ast)
                EM_debug("Printing AST due to -da or -dA flag:\n" + repr(driver.AST) + "\n");
            if (EM_recorded_any_errors()) break; // could detect errors while computing attributes to print them

            String code = driver.AST->HERA_code();
            if (EM_recorded_any_errors()) break;

            cout << code;
            return 0; // no errors
        }
        EM_warning("Not generating HERA code due to above errors.");
        return EM_recorded_any_errors(); // got errors somewhere, or would have returned 0 above

    } catch (const char *message) {
        cerr << "Compiler exception (this should not happen): " << message << endl;
        return 4;
    } catch (const std::string message) {
        cerr << "Compiler exception (this should not happen): " << message << endl;
        return 4;
    }  catch (const duplicate_symbol &d) {
        cerr << "Compiler exception due to duplicate symbol error not caught elsewhere." << endl;
        return 5;
    }  catch (const undefined_symbol &u) {
        cerr << "Compiler exception due to undefined symbol error not caught elsewhere." << endl;
        return 6;
    } catch (...) {
        cerr << "Yikes! Uncaught compiler exception (this should not happen if dave listed all exceptions in tiger.cpp)" << endl;
        return 66;
    }
}
