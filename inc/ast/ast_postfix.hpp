#ifndef AST_POSTFIX_HPP
#define AST_POSTFIX_HPP

#include <string>

#include "ast_expression.hpp"
#include "ast_variable.hpp"

class Postfix_Expression : public Expression{
    protected:
        ExpressionPtr left;
        std::string Operator;
        std::string ID;
        ExpressionPtr right;

    public:
        Postfix_Expression(ExpressionPtr _left, const std::string &_operator, const std::string &_ID = "") : left(_left), Operator(_operator), ID(_ID) {}
        Postfix_Expression(ExpressionPtr _left, const std::string &_operator, ExpressionPtr _right) : left(_left), Operator(_operator), right(_right) {}

        ExpressionPtr getleft() const;
        virtual const std::string getOperator() const;
        const std::string getID() const;

        virtual void printPy(std::ostream &dst, int depth = 0) const {}
        virtual void printMips(std::ostream &dst, Context &ctx) const;
        virtual void printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const;
};

#endif