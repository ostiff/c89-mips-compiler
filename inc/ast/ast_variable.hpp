#ifndef AST_VARIABLE_HPP
#define AST_VARIABLE_HPP

#include <string>
#include <iostream>

#include "ast_expression.hpp"
#include "context.hpp"


class Identifier : public Expression {
    private:
        std::string ID;

    public:
        Identifier(const std::string &_ID) : ID(_ID) {}
        
        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
        virtual void printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const;
        virtual std::string getID();
};

#endif