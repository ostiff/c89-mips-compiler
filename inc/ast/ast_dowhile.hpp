#ifndef AST_DOWHILE_HPP
#define AST_DOWHILE_HPP

#include <string>
#include <iostream>

#include "context.hpp"
#include "ast_expression.hpp"

class Do_Statement : public Expression {
    private:
        ExpressionPtr statement;
        ExpressionPtr expr;

    public:
        Do_Statement(ExpressionPtr _statement, ExpressionPtr _expr) : statement(_statement), expr(_expr){}
        
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

#endif