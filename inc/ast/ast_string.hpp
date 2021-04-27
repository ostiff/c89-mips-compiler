#ifndef AST_STRING_HPP
#define AST_STRING_HPP

#include <string>

#include "ast_expression.hpp"


class String_Literal : public Expression {
    private:
        std::string stringLit;

    public:
        String_Literal(const std::string &_stringLit) : stringLit(_stringLit) {} 
        
        virtual void printPy(std::ostream &dst, int depth = 0) const{}
        virtual void printMips(std::ostream &dst, Context &ctx) const {}
};


#endif