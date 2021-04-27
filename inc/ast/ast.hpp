#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <iostream>
#include <memory>
#include <initializer_list>
#include <vector>
#include <map>

#include "ast_arglist.hpp"
#include "ast_array.hpp"
#include "ast_binexpr.hpp"
#include "ast_break.hpp"
#include "ast_castExpr.hpp"
#include "ast_char.hpp"
#include "ast_conditional.hpp"
#include "ast_continue.hpp"
#include "ast_declaration.hpp"
#include "ast_directDecl.hpp"
#include "ast_double.hpp"
#include "ast_dowhile.hpp"
#include "ast_expression.hpp"
#include "ast_forloop.hpp"
#include "ast_function.hpp"
#include "ast_goto.hpp"
#include "ast_if.hpp"
#include "ast_int.hpp"
#include "ast_labeled.hpp"
#include "ast_list.hpp"
#include "ast_parameter.hpp"
#include "ast_parlist.hpp"
#include "ast_pointer.hpp"
#include "ast_postfix.hpp"
#include "ast_program.hpp"
#include "ast_return.hpp"
#include "ast_scope.hpp"
#include "ast_string.hpp"
#include "ast_struct.hpp"
#include "ast_switch.hpp"
#include "ast_unary.hpp"
#include "ast_variable.hpp"
#include "ast_varlist.hpp"
#include "ast_whileloop.hpp"

extern const Expression *parseAST(const char file[]);

#endif