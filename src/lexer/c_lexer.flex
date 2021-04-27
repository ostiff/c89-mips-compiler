%option noyywrap

%{
    #include <stdio.h>
    #include <iostream>
    #include <vector>
    #include <string>
    #include <iomanip>

	  //void yyerror (char const *s);
    /* Now in a section of C that will be embedded
    into the auto-generated code. Flex will not
    try to interpret code surrounded by %{ ... %} */

    /* Bring in our declarations for token types and
    the yylval variable. */
    #include "c_parser.tab.hpp"


    // This is to work around an irritating bug in Flex
    // https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
    extern "C" int fileno(FILE *stream);

    int TokenUsed(int tokenType, const char* tokenValue);

    //vector of tokens used for lexer testing
    std::vector<std::string> translator{
        "T_DOUBLE",
        "T_INT",
        "T_LONG",
        "T_FLOAT",
        "T_SHORT",
        "T_UNSIGNED",
        "T_SIGNED",
        "T_CHAR",
        "T_CONST",
        "T_AUTO",
        "T_STATIC",
        "T_VOID",
        "T_VOLATILE",
        "T_STRUCT",
        "T_FOR",
        "T_WHILE",
        "T_IF",
        "T_ELSE",
        "T_BREAK",
        "T_SWITCH",
        "T_CONTINUE",
        "T_GOTO",
        "T_CASE",
        "T_ENUM",
        "T_DO",
        "T_RETURN",
        "T_REGISTER",
        "T_TYPEDEF",
        "T_EXTERN",
        "T_UNION",
        "T_DEFAULT",
        "T_SIZEOF",
        "T_LEFT_SQUARE",
        "T_RIGHT_SQUARE",
        "T_LEFT_BRACKET",
        "T_RIGHT_BRACKET",
        "T_LEFT_CURLY_BRACKET",
        "T_RIGHT_CURLY_BRACKET",
        "T_SEMI_COLON",
        "T_ELLIPSIS",
        "T_DOT",
        "T_ARROW",
        "T_INCREMENT",
        "T_DECREMENT",
        "T_BITWISE_AND",
        "T_ASTERIX",
        "T_PLUS",
        "T_MINUS",
        "T_BITWISE_NOT",
        "T_LOGICAL_NOT",
        "T_FORWARD_SLASH",
        "T_MODULUS",
        "T_SHIFT_L",
        "T_SHIFT_R",
        "T_LESS_THAN",
        "T_GREATER_THAN",
        "T_LESS_EQUAL",
        "T_GREATER_EQUAL",
        "T_EQUAL_TO",
        "T_NOT_EQUAL_TO",
        "T_BITWISE_XOR",
        "T_BITWISE_OR",
        "T_LOGICAL_AND",
        "T_LOGICAL_OR",
        "T_QUESTION",
        "T_COLON",
        "T_ASSIGNMENT",
        "T_MULT_ASSIGNMENT",
        "T_DIV_ASSIGNMENT",
        "T_MODULO_ASSIGNMENT",
        "T_SUB_ASSIGNMENT",
        "T_ADD_ASSIGNMENT",
        "T_BITWISE_LSHIFT_ASSIGNMENT",
        "T_BITWISE_RSHIFT_ASSIGNMENT",
        "T_BITWISE_AND_ASSIGNMENT",
        "T_BITWISE_XOR_ASSIGNMENT",
        "T_BITWISE_OR_ASSIGNMENT",
        "T_COMMA",
        "T_HASH",
        "T_HASH_HASH",
        "T_IDENTIFIER",
        "T_INTEGER_CONSTANT",
        "T_FLOATING_CONSTANT",
        "T_CHAR_CONSTANT",
        "T_STRING_LITERAL",
        "T_MULT",
        "T_DIVIDE",
        "T_PREFIX_INCREMENT",
        "T_PREFIX_DECREMENT",
        "T_UNARY_PLUS",
        "T_UNARY_MINUS",
        "T_DEREFERENCE",
        "T_POSTFIX_INCREMENT",
        "T_POSTFIX_DECREMENT"
    };

    /* End the embedded code section. */
%}

DIGIT                [0-9]
NONZERO_DIGIT        [1-9]
DIGIT_SEQUENCE       {DIGIT}+
OCTAL_DIGIT          [0-7]
HEX_DIGIT            [0-9a-fA-F]

SIGN                 [+\-]
FLOATING_SUFFIX      [flFL]
LONG_SUFFIX          [lL]
UNSIGNED_SUFFIX      [uU]
INTEGER_SUFFIX       ({UNSIGNED_SUFFIX}{LONG_SUFFIX}?)|({LONG_SUFFIX}{UNSIGNED_SUFFIX}?)


/*---------------FLOATING CONSTANTS---------------*/
EXPONENT_PART        [eE]{SIGN}?{DIGIT_SEQUENCE}
FRACTIONAL_CONSTANT  ({DIGIT_SEQUENCE}?[.]{DIGIT_SEQUENCE})|({DIGIT_SEQUENCE}[.])
FLOATING_CONSTANT    ({FRACTIONAL_CONSTANT}{EXPONENT_PART}?{FLOATING_SUFFIX}?)|({DIGIT_SEQUENCE}{EXPONENT_PART}{FLOATING_SUFFIX}?)

/*---------------INTEGER CONSTANTS---------------*/
HEXADECIMAL_CONSTANT 0[xX]{HEX_DIGIT}+
OCTAL_CONSTANT       0({OCTAL_DIGIT}*)
DECIMAL_CONSTANT     {NONZERO_DIGIT}{DIGIT}*
INTEGER_CONSTANT     ({HEXADECIMAL_CONSTANT}|{OCTAL_CONSTANT}|{DECIMAL_CONSTANT}){INTEGER_SUFFIX}?

/*---------------ENUM CONSTANTS---------------*/
NONDIGIT             [_a-zA-Z]
IDENTIFIER           {NONDIGIT}({DIGIT}|{NONDIGIT})*

/*---------------CHAR CONSTANTS / STRING LITERALS---------------*/
C_CHAR               [^\\'\n]|{ESCAPE_SEQUENCE}
S_CHAR               [^\\"\n]|{ESCAPE_SEQUENCE}
C_CHAR_SEQUENCE      {C_CHAR}+
S_CHAR_SEQUENCE      {S_CHAR}+

STRING_LITERAL       [L]?(\"{S_CHAR_SEQUENCE}?\")
CHAR_CONSTANT        [L]?\'{C_CHAR_SEQUENCE}\'

ESCAPE_SEQUENCE         {SIMPLE_ESCAPE_SEQUENCE}|{OCTAL_ESCAPE_SEQUENCE}|{HEX_ESCAPE_SEQUENCE}
SIMPLE_ESCAPE_SEQUENCE  \\a|\\b|\\f|\\n|\\r|\\t|\\v|\\\\|\\\'|\\\"|\\\?
OCTAL_ESCAPE_SEQUENCE   \\{OCTAL_DIGIT}{1,3}
HEX_ESCAPE_SEQUENCE     \\x{HEX_DIGIT}+

%%

auto        { yylval.string=new std::string(yytext); return TokenUsed(T_AUTO, yytext); }
double      { yylval.string=new std::string(yytext); return TokenUsed(T_DOUBLE, yytext); }
int         { yylval.string=new std::string(yytext); return TokenUsed(T_INT, yytext); }
struct      { yylval.string=new std::string(yytext); return TokenUsed(T_STRUCT, yytext); }
break       { yylval.string=new std::string(yytext); return TokenUsed(T_BREAK, yytext); }
else        { yylval.string=new std::string(yytext); return TokenUsed(T_ELSE, yytext); }
long        { yylval.string=new std::string(yytext); return TokenUsed(T_LONG, yytext); }
switch      { yylval.string=new std::string(yytext); return TokenUsed(T_SWITCH, yytext); }
case        { yylval.string=new std::string(yytext); return TokenUsed(T_CASE, yytext); }
enum        { yylval.string=new std::string(yytext); return TokenUsed(T_ENUM, yytext); }
register    { yylval.string=new std::string(yytext); return TokenUsed(T_REGISTER, yytext); }
typedef     { yylval.string=new std::string(yytext); return TokenUsed(T_TYPEDEF, yytext); }
char        { yylval.string=new std::string(yytext); return TokenUsed(T_CHAR, yytext); }
extern      { yylval.string=new std::string(yytext); return TokenUsed(T_EXTERN, yytext); }
return      { yylval.string=new std::string(yytext); return TokenUsed(T_RETURN, yytext); }
union       { yylval.string=new std::string(yytext); return TokenUsed(T_UNION, yytext); }
const       { yylval.string=new std::string(yytext); return TokenUsed(T_CONST, yytext); }
float       { yylval.string=new std::string(yytext); return TokenUsed(T_FLOAT, yytext); }
short       { yylval.string=new std::string(yytext); return TokenUsed(T_SHORT, yytext); }
unsigned    { yylval.string=new std::string(yytext); return TokenUsed(T_UNSIGNED, yytext); }
continue    { yylval.string=new std::string(yytext); return TokenUsed(T_CONTINUE, yytext); }
for         { yylval.string=new std::string(yytext); return TokenUsed(T_FOR, yytext); }
signed      { yylval.string=new std::string(yytext); return TokenUsed(T_SIGNED, yytext); }
void        { yylval.string=new std::string(yytext); return TokenUsed(T_VOID, yytext); }
default     { yylval.string=new std::string(yytext); return TokenUsed(T_DEFAULT, yytext); }
goto        { yylval.string=new std::string(yytext); return TokenUsed(T_GOTO, yytext); }
sizeof      { yylval.string=new std::string(yytext); return TokenUsed(T_SIZEOF, yytext); }
volatile    { yylval.string=new std::string(yytext); return TokenUsed(T_VOLATILE, yytext); }
do          { yylval.string=new std::string(yytext); return TokenUsed(T_DO, yytext); }
if          { yylval.string=new std::string(yytext); return TokenUsed(T_IF, yytext); }
static      { yylval.string=new std::string(yytext); return TokenUsed(T_STATIC, yytext); }
while       { yylval.string=new std::string(yytext); return TokenUsed(T_WHILE, yytext); }

\[          { yylval.string=new std::string(yytext); return TokenUsed(T_LEFT_SQUARE, yytext); }
\]          { yylval.string=new std::string(yytext); return TokenUsed(T_RIGHT_SQUARE, yytext); }
\(          { yylval.string=new std::string(yytext); return TokenUsed(T_LEFT_BRACKET, yytext); }
\)          { yylval.string=new std::string(yytext); return TokenUsed(T_RIGHT_BRACKET, yytext); }
\{          { yylval.string=new std::string(yytext); return TokenUsed(T_LEFT_CURLY_BRACKET, yytext); }
\}          { yylval.string=new std::string(yytext); return TokenUsed(T_RIGHT_CURLY_BRACKET, yytext); }

\;          { yylval.string=new std::string(yytext); return TokenUsed(T_SEMI_COLON, yytext); }
\.\.\.      { yylval.string=new std::string(yytext); return TokenUsed(T_ELLIPSIS, yytext); }
\.          { yylval.string=new std::string(yytext); return TokenUsed(T_DOT, yytext); }
\-\>        { yylval.string=new std::string(yytext); return TokenUsed(T_ARROW, yytext); }
\+\+        { yylval.string=new std::string(yytext); return TokenUsed(T_INCREMENT, yytext); }
\-\-        { yylval.string=new std::string(yytext); return TokenUsed(T_DECREMENT, yytext); }
\&          { yylval.string=new std::string(yytext); return TokenUsed(T_BITWISE_AND, yytext); }
\*          { yylval.string=new std::string(yytext); return TokenUsed(T_ASTERIX, yytext); }
\+          { yylval.string=new std::string(yytext); return TokenUsed(T_PLUS, yytext); }
\-          { yylval.string=new std::string(yytext); return TokenUsed(T_MINUS, yytext); }
\~          { yylval.string=new std::string(yytext); return TokenUsed(T_BITWISE_NOT, yytext); }
\!          { yylval.string=new std::string(yytext); return TokenUsed(T_LOGICAL_NOT, yytext); }
\/          { yylval.string=new std::string(yytext); return TokenUsed(T_FORWARD_SLASH, yytext); }
\%          { yylval.string=new std::string(yytext); return TokenUsed(T_MODULUS, yytext); }
\<\<        { yylval.string=new std::string(yytext); return TokenUsed(T_SHIFT_L, yytext); }
\>\>        { yylval.string=new std::string(yytext); return TokenUsed(T_SHIFT_R, yytext); }
\<          { yylval.string=new std::string(yytext); return TokenUsed(T_LESS_THAN, yytext); }
\>          { yylval.string=new std::string(yytext); return TokenUsed(T_GREATER_THAN, yytext); }
\<\=        { yylval.string=new std::string(yytext); return TokenUsed(T_LESS_EQUAL, yytext); }
\>\=        { yylval.string=new std::string(yytext); return TokenUsed(T_GREATER_EQUAL, yytext); }
\=\=        { yylval.string=new std::string(yytext); return TokenUsed(T_EQUAL_TO, yytext); }
\!\=        { yylval.string=new std::string(yytext); return TokenUsed(T_NOT_EQUAL_TO, yytext); }
\^          { yylval.string=new std::string(yytext); return TokenUsed(T_BITWISE_XOR, yytext); }
\|          { yylval.string=new std::string(yytext); return TokenUsed(T_BITWISE_OR, yytext); }
\&\&        { yylval.string=new std::string(yytext); return TokenUsed(T_LOGICAL_AND, yytext); }
\|\|        { yylval.string=new std::string(yytext); return TokenUsed(T_LOGICAL_OR, yytext); }
\?          { yylval.string=new std::string(yytext); return TokenUsed(T_QUESTION, yytext); }
\:          { yylval.string=new std::string(yytext); return TokenUsed(T_COLON, yytext); }
\=          { yylval.string=new std::string(yytext); return TokenUsed(T_ASSIGNMENT, yytext); }
\*\=        { yylval.string=new std::string(yytext); return TokenUsed(T_MULT_ASSIGNMENT, yytext); }
\/\=        { yylval.string=new std::string(yytext); return TokenUsed(T_DIV_ASSIGNMENT, yytext); }
\%\=        { yylval.string=new std::string(yytext); return TokenUsed(T_MODULO_ASSIGNMENT, yytext); }
\+\=        { yylval.string=new std::string(yytext); return TokenUsed(T_ADD_ASSIGNMENT, yytext); }
\-\=        { yylval.string=new std::string(yytext); return TokenUsed(T_SUB_ASSIGNMENT, yytext); }
\<\<\=      { yylval.string=new std::string(yytext); return TokenUsed(T_BITWISE_LSHIFT_ASSIGNMENT, yytext); }
\>\>\=      { yylval.string=new std::string(yytext); return TokenUsed(T_BITWISE_RSHIFT_ASSIGNMENT, yytext); }
\&\=        { yylval.string=new std::string(yytext); return TokenUsed(T_BITWISE_AND_ASSIGNMENT, yytext); }
\^\=        { yylval.string=new std::string(yytext); return TokenUsed(T_BITWISE_XOR_ASSIGNMENT, yytext); }
\|\=        { yylval.string=new std::string(yytext); return TokenUsed(T_BITWISE_OR_ASSIGNMENT, yytext); }
\,          { yylval.string=new std::string(yytext); return TokenUsed(T_COMMA, yytext); }
\#          { yylval.string=new std::string(yytext); return TokenUsed(T_HASH, yytext); }
\#\#        { yylval.string=new std::string(yytext); return TokenUsed(T_HASH_HASH, yytext); }

{IDENTIFIER}            { yylval.string=new std::string(yytext); return TokenUsed(T_IDENTIFIER, yytext); }
{INTEGER_CONSTANT}      { yylval.string=new std::string(yytext);  return TokenUsed(T_INTEGER_CONSTANT, yytext); }
{FLOATING_CONSTANT}     { yylval.floating_constant=atof(yytext); return TokenUsed(T_FLOATING_CONSTANT, yytext); }
{CHAR_CONSTANT}         { yylval.string=new std::string(yytext); return TokenUsed(T_CHAR_CONSTANT, yytext); }
{STRING_LITERAL}        { yylval.string=new std::string(yytext); return TokenUsed(T_STRING_LITERAL, yytext); }

\/\*([^*]|[\n]|([\*]+([^*/]|[\n])))*[\*]+\/ { }

\/\/.*          { } //single line comments
#.*             { } //remove headers (change if decide to implement)
[\n]            { } //remove newlines
.               { } //no rule matched
%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s){
  fprintf(stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}

int TokenUsed(int tokenType, const char* tokenValue){
	//Use cerr for loging/debigging purposes 
	//std::cerr << "Token: " << std::setw(30) << translator[tokenType-258] << std::setw(30) << std::string(tokenValue) << std::endl;
	return tokenType;
}
