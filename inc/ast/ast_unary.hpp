#ifndef AST_UNARY_HPP
#define AST_UNARY_HPP

#include <string>

#include "ast_expression.hpp"
#include "ast_variable.hpp"

class Unary_Expression : public Expression{
    protected:
        ExpressionPtr right;
        std::string Operator;

    public:
        Unary_Expression(const std::string &_operator, ExpressionPtr _right) : right(_right), Operator(_operator) {}

        ExpressionPtr getRight() const;
        virtual const std::string getOperator() const;

        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
        virtual void printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const;
};

#endif