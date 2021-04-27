#ifndef AST_CASTEXPR_HPP
#define AST_CASTEXPR_HPP

#include <string>

#include "ast_expression.hpp"

class Cast_Expression : public Expression{
    protected:
        ExpressionPtr typeName;
        ExpressionPtr expr;

    public:
        Cast_Expression(ExpressionPtr _typeName, ExpressionPtr _expr) : typeName(_typeName), expr(_expr) {}
        // took this function directly from one of the labs
        // this function not(?) needed since we won't have classes inheriting from Binary_Expression class
        virtual void printPy(std::ostream &dst, int depth = 0) const{}
        virtual void printMips(std::ostream &dst, Context &ctx) const { }
};

#endif