#ifndef AST_BINEXPR_HPP
#define AST_BINEXPR_HPP

#include <string>

#include "ast_expression.hpp"
#include "ast_postfix.hpp"

class Binary_Expression : public Expression{
    protected:
        ExpressionPtr left;
        ExpressionPtr right;
        std::string Operator;

    public:
        Binary_Expression(ExpressionPtr _left, const std::string &_operator, ExpressionPtr _right) : left(_left), right(_right), Operator(_operator) {}

        ExpressionPtr getLeft() const;
        ExpressionPtr getRight() const;
        virtual const std::string getOperator() const;
        
        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const;
};

#endif