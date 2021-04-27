#ifndef AST_WHILELOOP_HPP
#define AST_WHILELOOP_HPP

#include <string>

#include "context.hpp"
#include "ast_expression.hpp"
#include "ast_scope.hpp"

class While_Statement : public Expression {
    private:
        ExpressionPtr expr;
        ExpressionPtr statement;

    public:
        While_Statement(ExpressionPtr _expr, ExpressionPtr _statement) : expr(_expr), statement(_statement){}
        
        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

#endif