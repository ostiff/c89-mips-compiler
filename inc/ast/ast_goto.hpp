#ifndef AST_GOTO_HPP
#define AST_GOTO_HPP

#include <string>

#include "ast_expression.hpp"

class Goto_Statement : public Expression {

    private:
        std::string label;

    public:
        Goto_Statement(const std::string &_label) : label(_label) {}
        virtual void printPy(std::ostream &dst, int depth = 0) const{}
        virtual void printMips(std::ostream &dst, Context &ctx) const { }
};

#endif