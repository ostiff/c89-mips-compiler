#ifndef AST_IF_HPP
#define AST_IF_HPP

#include <typeinfo>
#include <iostream>

#include "ast_expression.hpp"
#include "ast_scope.hpp"

class If_Statement : public Expression {
    private:
        ExpressionPtr expr;
        ExpressionPtr statement_if;
        ExpressionPtr statement_else;

    public:
        If_Statement(ExpressionPtr _expr, ExpressionPtr _statement_if, ExpressionPtr _statement_else = NULL) : expr(_expr), statement_if(_statement_if), statement_else(_statement_else) {}
        
        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

#endif