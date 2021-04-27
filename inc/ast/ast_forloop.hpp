#ifndef AST_FORLOOP_HPP
#define AST_FORLOOP_HPP

#include <string>

#include "ast_expression.hpp"

class For_Statement : public Expression {
    private:
        ExpressionPtr expr1;
        ExpressionPtr expr2;
        ExpressionPtr expr3;
        ExpressionPtr statement;

    public:
        For_Statement(ExpressionPtr _expr1 = NULL, ExpressionPtr _expr2 = NULL, ExpressionPtr _expr3 = NULL, ExpressionPtr _statement = NULL) :expr1(_expr1), expr2(_expr2), expr3(_expr3), statement(_statement){}

        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

#endif