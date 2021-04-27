#ifndef AST_CONTINUE_HPP
#define AST_CONTINUE_HPP

#include <string>

#include "ast_expression.hpp"

class Continue_Statement : public Expression {
    public:
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

#endif