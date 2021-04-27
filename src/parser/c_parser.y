%code requires{
  #include "ast.hpp"
    
  #include <vector>
  #include <cassert>
  #include <string>
  #include <utility>
  #include <iostream>
  
  extern Program *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

  extern FILE* yyin;
}

// Represents the value associated with any kind of
// AST node.
%union{
  ExpressionPtr expr; //all expressions/everything inherits from class Expression
  int integer_constant; //used in lexer
  double floating_constant; //used in lexer
  std::string *string; //used in lexer
}


%expect 1 //dangling else (resolved by order of rules)

%token T_DOUBLE T_INT T_LONG T_FLOAT T_SHORT T_UNSIGNED T_SIGNED T_CHAR T_CONST T_AUTO T_STATIC T_VOID T_VOLATILE T_STRUCT
%token T_FOR T_WHILE T_IF T_ELSE T_BREAK T_SWITCH T_CONTINUE T_GOTO T_CASE T_ENUM T_DO
%token T_RETURN T_REGISTER T_TYPEDEF T_EXTERN T_UNION T_DEFAULT T_SIZEOF 
%token T_LEFT_SQUARE T_RIGHT_SQUARE T_LEFT_BRACKET T_RIGHT_BRACKET T_LEFT_CURLY_BRACKET T_RIGHT_CURLY_BRACKET
%token T_SEMI_COLON T_ELLIPSIS T_DOT T_ARROW T_INCREMENT T_DECREMENT T_BITWISE_AND T_ASTERIX T_PLUS T_MINUS T_BITWISE_NOT  T_LOGICAL_NOT
%token T_FORWARD_SLASH T_MODULUS T_SHIFT_L T_SHIFT_R T_LESS_THAN T_GREATER_THAN T_LESS_EQUAL T_GREATER_EQUAL T_EQUAL_TO T_NOT_EQUAL_TO
%token T_BITWISE_XOR T_BITWISE_OR T_LOGICAL_AND T_LOGICAL_OR T_QUESTION T_COLON T_ASSIGNMENT T_MULT_ASSIGNMENT T_DIV_ASSIGNMENT T_MODULO_ASSIGNMENT
%token T_SUB_ASSIGNMENT T_ADD_ASSIGNMENT T_BITWISE_LSHIFT_ASSIGNMENT T_BITWISE_RSHIFT_ASSIGNMENT T_BITWISE_AND_ASSIGNMENT T_BITWISE_XOR_ASSIGNMENT
%token T_BITWISE_OR_ASSIGNMENT T_COMMA T_HASH T_HASH_HASH
%token T_IDENTIFIER T_INTEGER_CONSTANT T_FLOATING_CONSTANT T_CHAR_CONSTANT T_STRING_LITERAL


//NUMBERS
%type <floating_constant> T_FLOATING_CONSTANT

//TOKENS
%type <string> T_INTEGER_CONSTANT
%type <string> T_DOUBLE T_INT T_LONG T_FLOAT T_SHORT T_UNSIGNED T_SIGNED T_CHAR T_CONST T_AUTO T_STATIC T_VOID T_VOLATILE T_STRUCT
%type <string> T_FOR T_WHILE T_IF T_ELSE T_BREAK T_SWITCH T_CONTINUE T_GOTO T_CASE T_ENUM T_DO T_RETURN T_REGISTER T_TYPEDEF T_EXTERN T_UNION 
%type <string> T_DEFAULT T_SIZEOF T_LEFT_SQUARE T_RIGHT_SQUARE T_LEFT_BRACKET T_RIGHT_BRACKET T_LEFT_CURLY_BRACKET T_RIGHT_CURLY_BRACKET
%type <string> T_SEMI_COLON T_ELLIPSIS T_DOT T_ARROW T_INCREMENT T_DECREMENT T_BITWISE_AND T_ASTERIX T_PLUS T_MINUS T_BITWISE_NOT  T_LOGICAL_NOT
%type <string> T_FORWARD_SLASH T_MODULUS T_SHIFT_L T_SHIFT_R T_LESS_THAN T_GREATER_THAN T_LESS_EQUAL T_GREATER_EQUAL T_EQUAL_TO T_NOT_EQUAL_TO
%type <string> T_BITWISE_XOR T_BITWISE_OR T_LOGICAL_AND T_LOGICAL_OR T_QUESTION T_COLON T_ASSIGNMENT T_MULT_ASSIGNMENT T_DIV_ASSIGNMENT 
%type <string> T_MODULO_ASSIGNMENT T_SUB_ASSIGNMENT T_ADD_ASSIGNMENT T_BITWISE_LSHIFT_ASSIGNMENT T_BITWISE_RSHIFT_ASSIGNMENT T_BITWISE_AND_ASSIGNMENT
%type <string> T_BITWISE_XOR_ASSIGNMENT T_BITWISE_OR_ASSIGNMENT T_COMMA T_HASH T_HASH_HASH T_IDENTIFIER T_CHAR_CONSTANT T_STRING_LITERAL 
 
//PASRSER ONLY
%type <string> ASSIGNMENT_OPERATOR UNARY_OPERATOR TYPE_SPECIFIER STORAGE_CLASS_SPECIFIER STRUCT_OR_UNION TYPE_QUALIFIER DECLARATION_SPECIFIERS

%type <expr> EXTERNAL_DECLARATION DECLARATION DECLARATOR DIRECT_DECLARATOR
%type <expr> PRIMARY_EXPRESSION POSTFIX_EXPRESSION UNARY_EXPRESSION CAST_EXPRESSION MULTIPLICATIVE_EXPRESSION ADDITIVE_EXPRESSION SHIFT_EXPRESSION RELATIONAL_EXPRESSION
%type <expr> EQUALITY_EXPRESSION AND_EXPRESSION EXCLUSIVE_OR_EXPRESSION INCLUSIVE_OR_EXPRESSION LOGICAL_AND_EXPRESSION LOGICAL_OR_EXPRESSION CONDITIONAL_EXPRESSION
%type <expr> ASSIGNMENT_EXPRESSION  CONSTANT_EXPRESSION JUMP_STATEMENT ITERATION_STATEMENT SELECTION_STATEMENT STATEMENT LABELED_STATEMENT COMPOUND_STATEMENT EXPRESSION_STATEMENT EXPRESSION 

%type <expr> INIT_DECLARATOR ENUMERATOR ABSTRACT_DECLARATOR TYPE_NAME

%type <expr> FUNCTION_DEFINITION POINTER DIRECT_ABSTRACT_DECLARATOR
%type <expr> PARAMETER_DECLARATION STRUCT_DECLARATION INITIALIZER
%type <expr> PARAMETER_LIST PARAMETER_TYPE_LIST ARGUMENT_EXPRESSION_LIST DECLARATION_LIST ENUMERATOR_LIST IDENTIFIER_LIST INITIALIZER_LIST INIT_DECLARATOR_LIST STRUCT_DECLARATION_LIST STATEMENT_LIST TYPE_QUALIFIER_LIST SPECIFIER_QUALIFIER_LIST


%start TRANSLATION_UNIT

%%

TRANSLATION_UNIT : EXTERNAL_DECLARATION                      {g_root->insert($1); } //Adds a fragment to the program (e.g. function )
	               | TRANSLATION_UNIT EXTERNAL_DECLARATION     {g_root->insert($2); }
	               ;

FUNCTION_DEFINITION : DECLARATION_SPECIFIERS DECLARATOR DECLARATION_LIST COMPOUND_STATEMENT  { $$ = new Function_Definition(*$1,$2,$3,$4); } //function declaration 
	                  | DECLARATION_SPECIFIERS DECLARATOR COMPOUND_STATEMENT                   { $$ = new Function_Definition(*$1,$2,NULL,$3); } //constructor takes type and args
	                  | DECLARATOR DECLARATION_LIST COMPOUND_STATEMENT                         { $$ = new Function_Definition(NULL,$1,$2,$3); } //check what this is
	                  | DECLARATOR COMPOUND_STATEMENT                                          { $$ = new Function_Definition(NULL,$1,NULL,$2); }
                    | COMPOUND_STATEMENT                                                     { $$ = new Function_Definition(NULL,NULL,NULL,$1); }
                  	;

EXTERNAL_DECLARATION : FUNCTION_DEFINITION                { $$ = $1; }
                     | DECLARATION                        { $$ = $1; }
                     ;

PRIMARY_EXPRESSION : T_IDENTIFIER                               { $$ = new Identifier(*$1); }
                   | T_FLOATING_CONSTANT                        { $$ = new Floating_Constant($1); }
                   | T_INTEGER_CONSTANT                         { $$ = new Integer_Constant(*$1);}
                   | T_CHAR_CONSTANT                            { $$ = new Char_Constant(*$1); }
                   | T_STRING_LITERAL                           { $$ = new String_Literal(*$1); }
                   | T_LEFT_BRACKET EXPRESSION T_RIGHT_BRACKET  { $$ = $2; }
                   ;

POSTFIX_EXPRESSION : PRIMARY_EXPRESSION                                                           { $$ = $1; }
                   | POSTFIX_EXPRESSION T_LEFT_SQUARE EXPRESSION T_RIGHT_SQUARE                   { $$ = new Postfix_Expression($1,*$2,$3) ; }
                   | POSTFIX_EXPRESSION T_LEFT_BRACKET T_RIGHT_BRACKET                            { $$ = new Function_Call($1,NULL) ; } //function call
                   | POSTFIX_EXPRESSION T_LEFT_BRACKET ARGUMENT_EXPRESSION_LIST T_RIGHT_BRACKET   { $$ = new Function_Call($1,$3) ; } //function call
                   | POSTFIX_EXPRESSION T_DOT T_IDENTIFIER                                        { $$ = new Postfix_Expression($1,*$2,*$3) ; } // check if identifier is string
                   | POSTFIX_EXPRESSION T_ARROW T_IDENTIFIER                                      { $$ = new Postfix_Expression($1,*$2,*$3) ; }
                   | POSTFIX_EXPRESSION T_INCREMENT                                               { $$ = new Postfix_Expression($1,*$2,"") ; }
                   | POSTFIX_EXPRESSION T_DECREMENT                                               { $$ = new Postfix_Expression($1,*$2,"") ; }
                   ;

ARGUMENT_EXPRESSION_LIST : ASSIGNMENT_EXPRESSION                                     { $$ = new List($1);  }
                         | ARGUMENT_EXPRESSION_LIST T_COMMA ASSIGNMENT_EXPRESSION    {  $1->insert($3); $$ = $1; }
                         ;

UNARY_EXPRESSION : POSTFIX_EXPRESSION                                       { $$ = $1; }
                 | T_INCREMENT UNARY_EXPRESSION                             { $$ = new Unary_Expression(*$1,$2) ; }
                 | T_DECREMENT UNARY_EXPRESSION                             { $$ = new Unary_Expression(*$1,$2) ; }
                 | UNARY_OPERATOR CAST_EXPRESSION                           { $$ = new Unary_Expression(*$1,$2) ; }
                 | T_SIZEOF UNARY_EXPRESSION                                { $$ = new Unary_Expression(*$1,$2) ; }
                 | T_SIZEOF T_LEFT_BRACKET TYPE_NAME T_RIGHT_BRACKET        { $$ = new Unary_Expression(*$1,$3) ; } //need to differentiate type name from unary expression
                 ;

UNARY_OPERATOR : T_BITWISE_AND    { $$ = $1; }
               | T_ASTERIX        { $$ = $1; }
               | T_PLUS           { $$ = $1; }
               | T_MINUS          { $$ = $1; }
               | T_BITWISE_NOT    { $$ = $1; }
               | T_LOGICAL_NOT    { $$ = $1; }
               ; 

CAST_EXPRESSION : UNARY_EXPRESSION                                                      { $$ = $1; }
                | T_LEFT_BRACKET TYPE_NAME T_RIGHT_BRACKET CAST_EXPRESSION              { $$ = new Cast_Expression($2,$4) ; }
                ;

MULTIPLICATIVE_EXPRESSION : CAST_EXPRESSION                                             { $$ = $1; }
                          | MULTIPLICATIVE_EXPRESSION T_ASTERIX CAST_EXPRESSION         { $$ = new Binary_Expression($1,*$2,$3) ; }
                          | MULTIPLICATIVE_EXPRESSION T_FORWARD_SLASH CAST_EXPRESSION   { $$ = new Binary_Expression($1,*$2,$3) ; }
                          | MULTIPLICATIVE_EXPRESSION T_MODULUS CAST_EXPRESSION         { $$ = new Binary_Expression($1,*$2,$3) ; }
                          ;

ADDITIVE_EXPRESSION : MULTIPLICATIVE_EXPRESSION                                         { $$ = $1; }
                     | ADDITIVE_EXPRESSION T_PLUS MULTIPLICATIVE_EXPRESSION             { $$ = new Binary_Expression($1,*$2,$3) ; }
                     | ADDITIVE_EXPRESSION T_MINUS MULTIPLICATIVE_EXPRESSION            { $$ = new Binary_Expression($1,*$2,$3) ; }
                     ;

SHIFT_EXPRESSION : ADDITIVE_EXPRESSION                                                  { $$ = $1; }
                 | SHIFT_EXPRESSION T_SHIFT_L ADDITIVE_EXPRESSION                       { $$ = new Binary_Expression($1,*$2,$3) ; }
                 | SHIFT_EXPRESSION T_SHIFT_R ADDITIVE_EXPRESSION                       { $$ = new Binary_Expression($1,*$2,$3) ; }
                 ;

RELATIONAL_EXPRESSION : SHIFT_EXPRESSION                                                { $$ = $1; }
                      | RELATIONAL_EXPRESSION T_LESS_THAN SHIFT_EXPRESSION              { $$ = new Binary_Expression($1,*$2,$3) ; }
                      | RELATIONAL_EXPRESSION T_GREATER_THAN SHIFT_EXPRESSION           { $$ = new Binary_Expression($1,*$2,$3) ; }
                      | RELATIONAL_EXPRESSION T_LESS_EQUAL SHIFT_EXPRESSION             { $$ = new Binary_Expression($1,*$2,$3) ; }
                      | RELATIONAL_EXPRESSION T_GREATER_EQUAL SHIFT_EXPRESSION          { $$ = new Binary_Expression($1,*$2,$3) ; }
                      ;

EQUALITY_EXPRESSION : RELATIONAL_EXPRESSION                                             { $$ = $1; }
                    | EQUALITY_EXPRESSION T_EQUAL_TO RELATIONAL_EXPRESSION              { $$ = new Binary_Expression($1,*$2,$3) ; }
                    | EQUALITY_EXPRESSION T_NOT_EQUAL_TO RELATIONAL_EXPRESSION          { $$ = new Binary_Expression($1,*$2,$3) ; }
                    ;
                  
AND_EXPRESSION : EQUALITY_EXPRESSION                                                    { $$ = $1; }
               | AND_EXPRESSION T_BITWISE_AND EQUALITY_EXPRESSION                       { $$ = new Binary_Expression($1,*$2,$3) ; }
               ;

EXCLUSIVE_OR_EXPRESSION : AND_EXPRESSION                                                { $$ = $1; }
                        | EXCLUSIVE_OR_EXPRESSION T_BITWISE_XOR AND_EXPRESSION          { $$ = new Binary_Expression($1,*$2,$3) ; }
                        ;
  
INCLUSIVE_OR_EXPRESSION : EXCLUSIVE_OR_EXPRESSION                                       { $$ = $1; }
                        | INCLUSIVE_OR_EXPRESSION T_BITWISE_OR EXCLUSIVE_OR_EXPRESSION  { $$ = new Binary_Expression($1,*$2,$3) ; }
                        ;

LOGICAL_AND_EXPRESSION : INCLUSIVE_OR_EXPRESSION                                        { $$ = $1; }
                       | LOGICAL_AND_EXPRESSION T_LOGICAL_AND INCLUSIVE_OR_EXPRESSION   { $$ = new Binary_Expression($1,*$2,$3) ; }
                       ;

LOGICAL_OR_EXPRESSION : LOGICAL_AND_EXPRESSION                                          { $$ = $1; }
                      | LOGICAL_OR_EXPRESSION T_LOGICAL_OR LOGICAL_AND_EXPRESSION       { $$ = new Binary_Expression($1,*$2,$3) ; }
                      ;

CONDITIONAL_EXPRESSION : LOGICAL_OR_EXPRESSION                                                          { $$ = $1; }
                       | LOGICAL_OR_EXPRESSION T_QUESTION EXPRESSION T_COLON CONDITIONAL_EXPRESSION     { $$ = new Conditional_Expression($1,$3,$5) ; }
                       ;

ASSIGNMENT_EXPRESSION : CONDITIONAL_EXPRESSION                                           { $$ = $1; }
                      | UNARY_EXPRESSION ASSIGNMENT_OPERATOR ASSIGNMENT_EXPRESSION       { $$ = new Binary_Expression($1,*$2,$3) ; }
                      ;

ASSIGNMENT_OPERATOR : T_ASSIGNMENT                        { $$ = $1; }
                    | T_MULT_ASSIGNMENT                   { $$ = $1; }
                    | T_DIV_ASSIGNMENT                    { $$ = $1; }
                    | T_MODULO_ASSIGNMENT                 { $$ = $1; }
                    | T_ADD_ASSIGNMENT                    { $$ = $1; }
                    | T_SUB_ASSIGNMENT                    { $$ = $1; }
                    | T_BITWISE_LSHIFT_ASSIGNMENT         { $$ = $1; }
                    | T_BITWISE_RSHIFT_ASSIGNMENT         { $$ = $1; }
                    | T_BITWISE_AND_ASSIGNMENT            { $$ = $1; }
                    | T_BITWISE_XOR_ASSIGNMENT            { $$ = $1; }
                    | T_BITWISE_OR_ASSIGNMENT             { $$ = $1; }
                    ;

EXPRESSION : ASSIGNMENT_EXPRESSION                        { $$ = $1; } //is this right??
           | EXPRESSION T_COMMA ASSIGNMENT_EXPRESSION     { $$ = new Binary_Expression($1, *$2, $3) ; } //careful to evaluate $1 BEFORE $3 and use in result
           ;

CONSTANT_EXPRESSION : CONDITIONAL_EXPRESSION        { $$ = $1; } //is this right??
                    ;

DECLARATION : DECLARATION_SPECIFIERS T_SEMI_COLON                         { $$ = new Declaration(*$1,NULL); }
            | DECLARATION_SPECIFIERS INIT_DECLARATOR_LIST T_SEMI_COLON    { $$ = new Declaration(*$1,$2); }
            ;

DECLARATION_SPECIFIERS : STORAGE_CLASS_SPECIFIER                            { $$ = $1; }
                       | STORAGE_CLASS_SPECIFIER DECLARATION_SPECIFIERS     { $$ = new std::string(*$1 + " " + *$2); }
                       | TYPE_SPECIFIER                                     { $$ = $1; }
                       | TYPE_SPECIFIER DECLARATION_SPECIFIERS              { $$ = new std::string(*$1 + " " + *$2); }
                       | TYPE_QUALIFIER                                     { $$ = $1; }
                       | TYPE_QUALIFIER DECLARATION_SPECIFIERS              { $$ = new std::string(*$1 + " " + *$2); }
                       ;

INIT_DECLARATOR_LIST : INIT_DECLARATOR                                  { List *l = new List($1); $$ = l; }
                     | INIT_DECLARATOR_LIST T_COMMA INIT_DECLARATOR     { $1->insert($3); $$ = $1;  }
                     ;

INIT_DECLARATOR : DECLARATOR                              { $$ = new Init_Declarator($1, NULL); }
                | DECLARATOR T_ASSIGNMENT INITIALIZER     { $$ = new Init_Declarator($1,$3); }
                ;

STORAGE_CLASS_SPECIFIER : T_TYPEDEF         { $$ = $1; }
                        | T_EXTERN          { $$ = $1; }      
                        | T_STATIC          { $$ = $1; }      
                        | T_AUTO            { $$ = $1; }      
                        | T_REGISTER        { $$ = $1; }      
                        ;

TYPE_SPECIFIER : T_VOID                           { $$ = $1; }
               | T_CHAR                           { $$ = $1; }
               | T_SHORT                          { $$ = $1; }
               | T_INT                            { $$ = $1; }
               | T_LONG                           { $$ = $1; }
               | T_FLOAT                          { $$ = $1; }
               | T_DOUBLE                         { $$ = $1; }
               | T_SIGNED                         { $$ = $1; }
               | T_UNSIGNED                       { $$ = $1; }
               | STRUCT_OR_UNION_SPECIFIER        //do nothing??
               | ENUM_SPECIFIER                   //do nothing??
               //| TYPEDEF_NAME                   //check this     
               ;

STRUCT_OR_UNION_SPECIFIER : STRUCT_OR_UNION T_IDENTIFIER T_LEFT_CURLY_BRACKET STRUCT_DECLARATION_LIST T_RIGHT_CURLY_BRACKET  //do later if decide to implement structs
                          | STRUCT_OR_UNION T_LEFT_CURLY_BRACKET STRUCT_DECLARATION_LIST T_RIGHT_CURLY_BRACKET
                          | STRUCT_OR_UNION T_IDENTIFIER
                          ;

STRUCT_OR_UNION : T_STRUCT        { $$ = $1; }
                | T_UNION         { $$ = $1; }
                ;
  
STRUCT_DECLARATION_LIST : STRUCT_DECLARATION                            { $$ = new List($1); }
                        | STRUCT_DECLARATION_LIST STRUCT_DECLARATION    { $$ = $1; $1->insert($2); }
                        ;
    
STRUCT_DECLARATION : SPECIFIER_QUALIFIER_LIST STRUCT_DECLARATOR_LIST T_SEMI_COLON
                   ;

SPECIFIER_QUALIFIER_LIST : TYPE_SPECIFIER SPECIFIER_QUALIFIER_LIST      //{ $$ = $2; $2->insert($1); }   //sketchy!!
                         | TYPE_SPECIFIER                               //{ $$ = new List($1); }
                         | TYPE_QUALIFIER SPECIFIER_QUALIFIER_LIST      //{ $$ = $2; $2->insert($1); }
                         | TYPE_QUALIFIER                               //{ $$ = new List($1); }
                         ;

STRUCT_DECLARATOR_LIST : STRUCT_DECLARATOR
                       | STRUCT_DECLARATOR_LIST T_COMMA STRUCT_DECLARATOR
                       ;
    
STRUCT_DECLARATOR : DECLARATOR
                  | T_COLON CONSTANT_EXPRESSION
                  | DECLARATOR T_COLON CONSTANT_EXPRESSION
                  ;

ENUM_SPECIFIER : T_ENUM T_LEFT_CURLY_BRACKET ENUMERATOR_LIST T_RIGHT_CURLY_BRACKET
               | T_ENUM T_IDENTIFIER T_LEFT_CURLY_BRACKET ENUMERATOR_LIST T_RIGHT_CURLY_BRACKET 
               | T_ENUM T_IDENTIFIER
               ;

ENUMERATOR_LIST : ENUMERATOR                              //{ $$ = new List($1); }
                | ENUMERATOR_LIST T_COMMA ENUMERATOR      //{ $$ = $1; $1->insert($3); }
                ;
        
ENUMERATOR : T_IDENTIFIER
           | T_IDENTIFIER T_ASSIGNMENT CONSTANT_EXPRESSION
           ;

TYPE_QUALIFIER : T_CONST          { $$ = $1; }
               | T_VOLATILE       { $$ = $1; }
               ;

DECLARATOR : DIRECT_DECLARATOR            { $$ = $1; }
           | POINTER DIRECT_DECLARATOR    { $$ = $1; }
           ;

DIRECT_DECLARATOR : T_IDENTIFIER                                                               { $$ = new Identifier(*$1); }
                  | T_LEFT_BRACKET DECLARATOR T_RIGHT_BRACKET                                  { $$ = new Direct_Declarator(NULL,*$1,$2,*$3) ; }
                  | DIRECT_DECLARATOR T_LEFT_SQUARE CONSTANT_EXPRESSION T_RIGHT_SQUARE         { $$ = new Array($1,$3) ; } // { $$ = new Direct_Declarator($1,*$2,$3,*$4) ; }
                  | DIRECT_DECLARATOR T_LEFT_SQUARE T_RIGHT_SQUARE                             { $$ = new Direct_Declarator($1,*$2,NULL,*$3) ; }
                  | DIRECT_DECLARATOR T_LEFT_BRACKET PARAMETER_TYPE_LIST T_RIGHT_BRACKET       { $$ = new Direct_Declarator($1,*$2,$3,*$4) ; }
                  | DIRECT_DECLARATOR T_LEFT_BRACKET IDENTIFIER_LIST T_RIGHT_BRACKET           { $$ = new Direct_Declarator($1,*$2,$3,*$4) ; }
                  | DIRECT_DECLARATOR T_LEFT_BRACKET T_RIGHT_BRACKET                           { $$ = new Direct_Declarator($1,*$2,NULL,*$3) ; }
                  ;
 
POINTER : T_ASTERIX                               { $$ = new Pointer(NULL,NULL); }
        | T_ASTERIX TYPE_QUALIFIER_LIST           { $$ = new Pointer($2,NULL); }
        | T_ASTERIX POINTER                       { $$ = new Pointer(NULL,$2); }
        | T_ASTERIX TYPE_QUALIFIER_LIST POINTER   { $$ = new Pointer($2,$3); }
        ;

TYPE_QUALIFIER_LIST : TYPE_QUALIFIER                        //{ $$ = new List($1); } //are these strings??
                    | TYPE_QUALIFIER_LIST TYPE_QUALIFIER    //{ $$ = $1; $1->insert($2); }
                    ;

PARAMETER_TYPE_LIST : PARAMETER_LIST                            //{ $$ = new Parameter_Type_List($1, NULL); }
                    | PARAMETER_LIST T_COMMA T_ELLIPSIS         //{ $$ = new Parameter_Type_List($1, *$3); } ////////////// WHAT IS GOING ON HERE
                    ;

PARAMETER_LIST : PARAMETER_DECLARATION                              { $$ = new List($1); }   //list of Parameter_Declaration????
               | PARAMETER_LIST T_COMMA PARAMETER_DECLARATION       { $$ = $1; $1->insert($3); }
               ;

PARAMETER_DECLARATION : DECLARATION_SPECIFIERS DECLARATOR                 { $$ = new Parameter_Declaration(*$1,$2,NULL); }  ///FIRST PARAM CHGANGED TO STRING
                      | DECLARATION_SPECIFIERS ABSTRACT_DECLARATOR        { $$ = new Parameter_Declaration(*$1,NULL,$2); }
                      | DECLARATION_SPECIFIERS                            { $$ = new Parameter_Declaration(*$1,NULL,NULL); }
                      ;

IDENTIFIER_LIST : T_IDENTIFIER                              { $$ = new List(new Identifier(*$1)); } //changed from Identifier_List
                | IDENTIFIER_LIST T_COMMA T_IDENTIFIER      { $$ = $1; $1->insert(new Identifier(*$3)); }
                ;

TYPE_NAME : SPECIFIER_QUALIFIER_LIST                            { $$ = $1; } ///is this right??
          | SPECIFIER_QUALIFIER_LIST ABSTRACT_DECLARATOR
          ;

ABSTRACT_DECLARATOR : POINTER                                       //do we want abstract declarators
                    | DIRECT_ABSTRACT_DECLARATOR
                    | POINTER DIRECT_ABSTRACT_DECLARATOR                   
                    ;

DIRECT_ABSTRACT_DECLARATOR : T_LEFT_BRACKET ABSTRACT_DECLARATOR T_RIGHT_BRACKET
                           | DIRECT_ABSTRACT_DECLARATOR T_LEFT_SQUARE T_RIGHT_SQUARE
                           | DIRECT_ABSTRACT_DECLARATOR T_LEFT_SQUARE CONSTANT_EXPRESSION T_RIGHT_SQUARE
                           | T_LEFT_SQUARE T_RIGHT_SQUARE
                           | T_LEFT_SQUARE CONSTANT_EXPRESSION T_RIGHT_SQUARE
                           | DIRECT_ABSTRACT_DECLARATOR T_LEFT_BRACKET T_RIGHT_BRACKET
                           | DIRECT_ABSTRACT_DECLARATOR T_LEFT_BRACKET PARAMETER_TYPE_LIST T_RIGHT_BRACKET
                           | T_LEFT_BRACKET T_RIGHT_BRACKET
                           | T_LEFT_BRACKET PARAMETER_TYPE_LIST T_RIGHT_BRACKET
                           ;


INITIALIZER : ASSIGNMENT_EXPRESSION                                                 { $$ = $1 ; }
            | T_LEFT_CURLY_BRACKET INITIALIZER_LIST T_RIGHT_CURLY_BRACKET           { $$ = $2 ; }
            | T_LEFT_CURLY_BRACKET INITIALIZER_LIST T_COMMA T_RIGHT_CURLY_BRACKET   { $$ = $2 ; }
            ;

INITIALIZER_LIST : INITIALIZER                              { $$ = new List($1); }
                 | INITIALIZER_LIST T_COMMA INITIALIZER     { $$ = $1; $1->insert($3); }
                 ;

STATEMENT : LABELED_STATEMENT             { $$ = $1; }
          | COMPOUND_STATEMENT            { $$ = $1; }
          | EXPRESSION_STATEMENT          { $$ = $1; }
          | SELECTION_STATEMENT           { $$ = $1; }
          | ITERATION_STATEMENT           { $$ = $1; }  
          | JUMP_STATEMENT                { $$ = $1; }
          ;

LABELED_STATEMENT : T_IDENTIFIER T_COLON STATEMENT                    { $$ = new Labeled_Statement(*$1, NULL, $3) ; }
                  | T_CASE CONSTANT_EXPRESSION T_COLON STATEMENT      { $$ = new Labeled_Statement(*$1, $2, $4) ; }
                  | T_DEFAULT T_COLON STATEMENT                       { $$ = new Labeled_Statement(*$1, NULL, $3) ; }
                  ;

COMPOUND_STATEMENT : T_LEFT_CURLY_BRACKET T_RIGHT_CURLY_BRACKET                                     { $$ = new Scope(NULL,NULL); } //constructor takes 2 list of expressions
                   | T_LEFT_CURLY_BRACKET DECLARATION_LIST STATEMENT_LIST T_RIGHT_CURLY_BRACKET     { $$ = new Scope($2,$3); }
                   | T_LEFT_CURLY_BRACKET DECLARATION_LIST T_RIGHT_CURLY_BRACKET                    { $$ = new Scope($2,NULL); } 
                   | T_LEFT_CURLY_BRACKET STATEMENT_LIST T_RIGHT_CURLY_BRACKET                      { $$ = new Scope(NULL,$2); }
                   ;

DECLARATION_LIST : DECLARATION                      { $$ = new List($1); }       
                 | DECLARATION_LIST DECLARATION     { $$ = $1; $1->insert($2); }
                 ;

STATEMENT_LIST : STATEMENT                    { $$ = new List($1); }
               | STATEMENT_LIST STATEMENT     { $$ = $1; $1->insert($2); }
               ;

EXPRESSION_STATEMENT : T_SEMI_COLON                 { $$ = NULL; } // for case when for loop has null argument?
                     | EXPRESSION T_SEMI_COLON      { $$ = $1; }   //are these 2 correct??
                     ;

SELECTION_STATEMENT : T_IF T_LEFT_BRACKET EXPRESSION T_RIGHT_BRACKET STATEMENT                      { $$ = new If_Statement($3, $5, NULL) ; } 
                    | T_IF T_LEFT_BRACKET EXPRESSION T_RIGHT_BRACKET STATEMENT T_ELSE STATEMENT     { $$ = new If_Statement($3, $5, $7) ; }
                    | T_SWITCH T_LEFT_BRACKET EXPRESSION T_RIGHT_BRACKET STATEMENT                  { $$ = new Switch_Statement($3, $5) ; }
                    ;

ITERATION_STATEMENT : T_WHILE T_LEFT_BRACKET EXPRESSION T_RIGHT_BRACKET STATEMENT                                           { $$ = new While_Statement($3, $5) ; }
                    | T_DO STATEMENT T_WHILE T_LEFT_BRACKET EXPRESSION T_RIGHT_BRACKET T_SEMI_COLON                         { $$ = new Do_Statement($2, $5) ; }
                    | T_FOR T_LEFT_BRACKET EXPRESSION_STATEMENT EXPRESSION_STATEMENT T_RIGHT_BRACKET STATEMENT              { $$ = new For_Statement($3,$4,NULL,$6) ; }
                    | T_FOR T_LEFT_BRACKET EXPRESSION_STATEMENT EXPRESSION_STATEMENT EXPRESSION T_RIGHT_BRACKET STATEMENT   { $$ = new For_Statement($3,$4,$5,$7) ; }
                    ;

JUMP_STATEMENT : T_GOTO T_IDENTIFIER T_SEMI_COLON           { $$ = new Goto_Statement(*$2) ; }
               | T_CONTINUE T_SEMI_COLON                    { $$ = new Continue_Statement() ; }
               | T_BREAK T_SEMI_COLON                       { $$ = new Break_Statement() ; }
               | T_RETURN EXPRESSION T_SEMI_COLON           { $$ = new Return_Statement($2) ; }
               | T_RETURN T_SEMI_COLON                      { $$ = new Return_Statement(NULL) ; }
               ;

%%

Program *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST(const char file[]){
  g_root = new Program();
  yyin = fopen(file, "r");
  yyparse();
  return g_root;
}
