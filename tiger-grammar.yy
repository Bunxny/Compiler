// Note: to learn how to invoke bison/flex in Eclipse, see https://www.eclipse.org/forums/index.php/t/1075215/
// And refer to the example at https://www.gnu.org/software/bison/manual/html_node/A-Complete-C_002b_002b-Example.html#A-Complete-C_002b_002b-Example

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.2"
%defines
%define api.parser.class {tigerParser}

/* next two from https://www.gnu.org/software/bison/manual/html_node/Complete-Symbols.html#Complete-Symbols */
%define api.value.type variant
%define api.token.constructor

%code requires
{
class tigerParseDriver;
}
%param { tigerParseDriver& driver }

// According to the Example, this turns on "location tracking"
%locations
// Thanks to Ian Fisher HC '19 for explaining the details of the parts I'd failed to get working


%{
#include "tigerParseDriver.h"
%}

// The line below means our grammar must not have conflicts
//  (no conflicts means it is "an LALR(1) grammar",
//   meaning it must be unambiguous and have some other properties).
%expect 0


/******************************************************************/
/***                                                            ***/
/***                 TOKENS and NON-TERMINALS                   ***/
/***                                                            ***/
/******************************************************************/

// We need to list TOKENS and NONTERMINALS, possibly giving TYPES for either one, and possibly giving PRECEDENCE
// NOTE that bison complains if you have the same symbol listed as %token and %type, since the latter is used only for nonterminals.

// In this file, I'll list the non-termials first, then their precedence relations, and then give the types of terminals

/*****************************    TOKENS     **********************/

// For my list of tokens, I'll give
//    first, a specal case for END,
//     then, all the un-attributed tokens like PLUS, LPAREN
//   finaly, the tokens with attributes, such as INT and STRING

%token END  0  /* this one is special, due to pre-defined interaction with flex */

%token
  COMMA COLON SEMICOLON LPAREN RPAREN L_SQUARE_BRACKET R_SQUARE_BRACKET 
  L_CURLY_BRACE R_CURLY_BRACE
  ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END_LET OF
  BREAK NIL
  FUNCTION VAR TYPE DOT
  PLUS MINUS UMINUS TIMES DIVIDE ASSIGN EQ NEQ LT LE GT GE OR AND NOT
;

%token <bool> BOOL
%token <int>  INT
%token <std::string> ID
%token <std::string> STRING

// Next, the precedence rules; these can be from the list of tokens above,
//  but with _ordered_sequence_ of %left/%right/%nonassoc steps,
//  we define precedence (stickiness), with the "stickiest" (highest precedence) at the bottom of the list
%left IF THEN WHILE DO
%left ELSE
%left OR
%left AND
%left NOT
%left GT GE LT LE EQ NEQ
%left MINUS PLUS
%left TIMES DIVIDE
%left UMINUS
%left LPAREN RPAREN
%left SEMICOLON



/***************************** NON-TERMINALS **********************/

/* Attributes types for nonterminals are next, e.g. struct's from tigerParseDriver.h */
%type <expAttrs>  exp
%type <elistAttrs>  elist




/******************************************************************/
/***                                                            ***/
/***    THE SECTION BELOW, AFTER %%, GIVES PRODUCTION RULES     ***/
/***                                                            ***/
/******************************************************************/


%%

%start program;
program: exp[main]	{ EM_debug("Got the main expression of our tiger program.", $main.AST->pos());
		 			  //if ($main.type != Ty_Int() && $main.type != Ty_String() && $main.type != Ty_Void() && $main.type != Ty_Bool() && $main.type != Ty_Void())
		 			   //EM_error("Sorry, at this time, main expression must be an integer");
		 			  driver.AST = new A_root_($main.AST);
		 			}
	;

exp:  INT[i]					{ $$.AST = A_IntExp(Position::fromLex(@i), $i);
								  //$$.type = Ty_Int();
								  EM_debug("Got int " + str($i), $$.AST->pos());
								}
	| exp[exp1] PLUS exp[exp2]	{
	                              $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
												   A_plusOp,  $exp1.AST,$exp2.AST);
								  //$$.type = Ty_Int();
								  EM_debug("Got plus expression.", $$.AST->pos());
								}
	| exp[exp1] TIMES exp[exp2]	{
	                              $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
												   A_timesOp, $exp1.AST,$exp2.AST);
								  //$$.type = Ty_Int();
								  EM_debug("Got times expression.", $$.AST->pos());
			  					}
    | exp[exp1] DIVIDE exp[exp2]	{
    	                              $$.AST = A_CallExp(Position::undefined(),to_Symbol("div"),A_ExpList($exp1.AST, A_ExpList($exp2.AST,0)));
    								  //$$.type = Ty_Int();
    								  EM_debug("Got divide expression.", $$.AST->pos());
    			  					}
    | exp[exp1] GT exp[exp2]	{
    	                             $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
    												   A_gtOp,  $exp1.AST,$exp2.AST);
    								 //$$.type = Ty_Bool();
    								 EM_debug("Got greater than expression.", $$.AST->pos());
    							    }
    | exp[exp1] GE exp[exp2]	{
        	                         $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
        											    A_geOp,  $exp1.AST,$exp2.AST);
        							 //$$.type = Ty_Bool();
        							 EM_debug("Got greater than equal to expression.", $$.AST->pos());
        							}
    | exp[exp1] LT exp[exp2]	{
            	                    $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
            						                    A_ltOp,  $exp1.AST,$exp2.AST);
            					    //$$.type = Ty_Bool();
            					    EM_debug("Got less than to expression.", $$.AST->pos());
            						}
    | exp[exp1] LE exp[exp2]	{
            	                    $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
            								            A_leOp,  $exp1.AST,$exp2.AST);
            					    //$$.type = Ty_Bool();
            					    EM_debug("Got less than equal to expression.", $$.AST->pos());
            						}
    | exp[exp1] EQ exp[exp2]	{
                	                 $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
                								         A_eqOp,  $exp1.AST,$exp2.AST);
                					 //$$.type = Ty_Bool();
                					 EM_debug("Got equal equal to expression.", $$.AST->pos());
                				     }
    | exp[exp1] NEQ exp[exp2]	{
                	                 $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
                								         A_neqOp,  $exp1.AST,$exp2.AST);
                					 //$$.type = Ty_Bool();
                					 EM_debug("Got not equal to expression.", $$.AST->pos());
                					}

    |exp[exp0] AND exp[exp1] {
                                          $$.AST = A_IfExp(Position::undefined(), $exp0.AST,
                                                            $exp1.AST, A_BoolExp(Position::undefined(), 0));
                                          EM_debug("Got and expression", $$.AST->pos());
                                }
    |exp[exp0] OR exp[exp1] {
                                          $$.AST = A_IfExp(Position::undefined(), $exp0.AST,
                                                            A_BoolExp(Position::undefined(), 1), $exp1.AST);
                                          EM_debug("Got or expression", $$.AST->pos());
                                }
    |NOT exp[exp0] {
                                          $$.AST = A_IfExp(Position::undefined(), $exp0.AST,
                                                           A_BoolExp(Position::undefined(), 0), A_BoolExp(Position::undefined(), 1));
                                          EM_debug("Got not expression", $$.AST->pos());
                                    }

    | exp[exp1] MINUS exp[exp2]	{
                                  $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
												   A_minusOp,  $exp1.AST,$exp2.AST);
								  //$$.type = Ty_Int();
								  EM_debug("Got minus expression.", $$.AST->pos());
								}

	| MINUS exp[exp1]	%prec UMINUS{
                                      $$.AST = A_OpExp(Position::undefined(),
    												   A_minusOp,  A_IntExp(Position::undefined(), 0),$exp1.AST);
    								  //$$.type = Ty_Int();
    								  EM_debug("Got minus expression.", $$.AST->pos());
    								}

    | LPAREN exp[exp1] RPAREN   { $$.AST = $exp1.AST;
								  //$$.type = $exp1.type;
								  EM_debug("Got parenthesis expression.", $$.AST->pos());
								}
    | STRING[i]					{ $$.AST = A_StringExp(Position::fromLex(@i), $i);
   								  //$$.type = Ty_String();
      							  EM_debug("Got string ", $$.AST->pos());
        					    }
    | ID[i] {
                     $$.AST = A_VarExp(Position::fromLex(@i),A_SimpleVar(Position::fromLex(@i), to_Symbol($i)));
            		 EM_debug("Got var expression.", $$.AST->pos());
            		}
    | ID[i] LPAREN exp[exp1] RPAREN {
                                      $$.AST = A_CallExp(Position::undefined(),to_Symbol($i),A_ExpList($exp1.AST, 0));
                                      //$$.type = Ty_Void();
								      EM_debug("Got call expression.", $$.AST->pos());
								    }
	| ID[i] LPAREN exp[exp1] COMMA exp[exp2] RPAREN {
                                          $$.AST = A_CallExp(Position::undefined(),to_Symbol($i),A_ExpList($exp1.AST, A_ExpList($exp2.AST,0)));
                                          //$$.type = Ty_Int();
    								      EM_debug("Got call expression.", $$.AST->pos());
    								    }
    | ID[i] LPAREN exp[exp1] COMMA exp[exp2] COMMA exp[exp3] RPAREN {
                                              $$.AST = A_CallExp(Position::undefined(),to_Symbol($i),A_ExpList($exp1.AST, A_ExpList($exp2.AST,A_ExpList($exp3.AST,0))));
                                              //$$.type = Ty_Int();
        								      EM_debug("Got call expression.", $$.AST->pos());
        								    }
    | ID[i] LPAREN RPAREN {
                                              $$.AST = A_CallExp(Position::undefined(),to_Symbol($i),nullptr);
                                              //$$.type = Ty_Void();
        								      EM_debug("Got void call expression.", $$.AST->pos());
        								    }
	//| LPAREN elist[elist1] RPAREN {
                                      //$$.AST = A_SeqExp(Position::undefined(), $elist1.AST);
                                      //$$.type = $elist1.type;
                                     // EM_debug("got expression sequence.");
                                   // }
    | LPAREN exp[exp1] SEMICOLON elist[elist1] RPAREN   {
                                      $$.AST = A_SeqExp(Position::undefined(), A_ExpList($exp1.AST, $elist1.AST));
    								  //$$.type =  $elist1.type;
    								  EM_debug("Got expression sequence.", $$.AST->pos());
    								}
    | BOOL[i]					{
                                      $$.AST = A_BoolExp(Position::fromLex(@i), $i);
       								  //$$.type = Ty_Bool();
          							  EM_debug("Got Bool ", $$.AST->pos());
            					}
    | IF exp[exp0] THEN exp[exp1] ELSE exp[exp2] {
                                          $$.AST = A_IfExp(Position::undefined(), $exp0.AST,
                                                            $exp1.AST, $exp2.AST);
                                          //$$.type = $exp2.type;
                                          EM_debug("Got if expression ", $$.AST->pos());
                                    }
    | IF exp[exp0] THEN exp[exp1] {
                                          $$.AST = A_IfExp(Position::undefined(), $exp0.AST,
                                                            $exp1.AST, nullptr);
                                          //$$.type = $exp1.type;
                                          EM_debug("Got if expression without else", $$.AST->pos());
                                    }
    | WHILE exp[exp0] DO exp[exp1] {
                                              $$.AST = A_WhileExp(Position::undefined(), $exp0.AST,
                                                                $exp1.AST);
                                              //$$.type = $exp1.type;
                                              EM_debug("Got if expression without else", $$.AST->pos());
                                    }
    | FOR ID[i] ASSIGN exp[exp0] TO exp[exp1] DO exp[exp2] {
                                              $$.AST = A_ForExp(Position::undefined(), to_Symbol($i), $exp0.AST,
                                                                $exp1.AST, $exp2.AST);
                                              //$$.type = Ty_Void();
                                              EM_debug("Got for expression", $$.AST->pos());
                                    }
    | BREAK {
                                          $$.AST = A_BreakExp(Position::undefined());
                                          EM_debug("Got break expression", $$.AST->pos());
                                    }
    | LPAREN RPAREN {
                                              $$.AST =  A_SeqExp(Position::undefined(), nullptr);
                                              //$$.type = Ty_Void();
        								      EM_debug("Got void expression.");
        								    }
elist:
        exp[exp1] SEMICOLON elist[elist1] {
                                $$.AST = A_ExpList($exp1.AST, $elist1.AST);
                                //$$.type = $elist1.type;
        					    EM_debug("Got expression list.", $$.AST->pos());
        						}
        |exp[exp1] {            $$.AST = A_ExpList($exp1.AST, 0);
                                //$$.type = $exp1.type;
                                EM_debug("Got parenthesis expression.", $$.AST->pos());
                                }
//
// Note: In older compiler tools, instead of writing $exp1 and $exp2, we'd write $1 and $3,
//        to refer to the first and third elements on the right-hand-side of the production.
//        We can still use this notation (and note that Appel uses it in his book), e.g. the above is like
//					$$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
//									 A_timesOp, $1.AST,$3.AST);
// Also: Bison's location system produces information about nonterminals as well as terminals,
//        so we could use @exp1 to get it's information about the locations of exp1
//        writing, e.g., Position::fromLex(@exp1) or instead of $exp1.AST->pos()
//
	;

%%

void
yy::tigerParser::error(const location_type& l,
          	       const std::string& m)
  {
	  EM_debug("In yy::tigerParser::error");
	  EM_error(m, true, Position::fromLex(l));
  }
