#ifndef AST_SWITCH_HPP
#define AST_SWITCH_HPP

#include "ast_expression.hpp"
#include "context.hpp"

class Switch_Statement : public Expression {
    private:
        ExpressionPtr expr;
        ExpressionPtr statement;

    public:
        Switch_Statement(ExpressionPtr _expr, ExpressionPtr _statement) : expr(_expr), statement(_statement){}
        
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

#endif