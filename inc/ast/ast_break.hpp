#ifndef AST_BREAK_HPP
#define AST_BREAK_HPP

#include <string>

#include "ast_expression.hpp"

class Break_Statement : public Expression {
    public:
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

#endif