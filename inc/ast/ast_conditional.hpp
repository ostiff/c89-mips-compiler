#ifndef AST_CONDITIONAL_HPP
#define AST_CONDITIONAL_HPP

#include <string>

#include "ast_expression.hpp"

class Conditional_Expression : public Expression{
    protected:
        ExpressionPtr logical;
        ExpressionPtr expr;
        ExpressionPtr conditional;

    public:
        Conditional_Expression(ExpressionPtr _logical, ExpressionPtr _expr, ExpressionPtr _conditional) : logical(_logical), expr(_expr), conditional(_conditional) {}

        virtual void printPy(std::ostream &dst, int depth = 0) const {}
        virtual void printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const;
};

#endif