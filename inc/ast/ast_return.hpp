#ifndef AST_RETURN_HPP
#define AST_RETURN_HPP

#include <string>

#include "ast_expression.hpp"
#include "context.hpp"
#include "ast_int.hpp"

class Return_Statement : public Expression {
    private:
        ExpressionPtr expr;

    public:
        Return_Statement(ExpressionPtr _expr = NULL) : expr(_expr) {}

        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;        
};  

#endif