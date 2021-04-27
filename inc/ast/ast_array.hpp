#ifndef AST_ARRAY_HPP
#define AST_ARRAY_HPP

#include <string>

#include "ast_expression.hpp"
#include "ast_int.hpp"
#include "ast_variable.hpp"

class Array : public Expression {
    private:
        ExpressionPtr postfixexpr;
        ExpressionPtr expr;

    public:
        Array(ExpressionPtr _postfixexpr, ExpressionPtr _expr) : postfixexpr(_postfixexpr), expr(_expr) {} 
        virtual void printMips(std::ostream &dst, Context &ctx) const {}
        virtual int getSize();
        virtual std::string getID();
};

#endif