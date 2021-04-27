#ifndef AST_CHAR_HPP
#define AST_CHAR_HPP

#include <string>

#include "ast_expression.hpp"


class Char_Constant : public Expression {
    private:
        std::string char_constant;

    public:
        Char_Constant(const std::string &_char_constant) : char_constant(_char_constant) {} 
        
        virtual void printPy(std::ostream &dst, int depth = 0) const{}
        virtual void printMips(std::ostream &dst, Context &ctx) const { }
};

#endif