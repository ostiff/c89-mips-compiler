#ifndef AST_FUNCTION_HPP
#define AST_FUNCTION_HPP

#include <string>
#include <iostream>
#include <typeinfo>
#include <sstream>

#include "ast_expression.hpp"
#include "ast_variable.hpp"
#include "ast_directDecl.hpp"
#include "context.hpp"

class Function_Definition : public Expression {
    private:
        std::string decSpec;
        ExpressionPtr decl;
        ExpressionPtr decList;
        ExpressionPtr compStat;

        int argNumber;

    public:
        Function_Definition(const std::string &_decSpec = "", ExpressionPtr _decl = NULL, ExpressionPtr _decList = NULL, ExpressionPtr _compStat = NULL) : decSpec(_decSpec), decl(_decl), decList(_decList), compStat(_compStat) {
            argNumber = decl->getArgNumber();
        }

        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

class Function_Call : public Expression {
    private:
        ExpressionPtr postfixexpr;
        ExpressionPtr arglist;

    public:
        Function_Call(ExpressionPtr _postfixexpr, ExpressionPtr _arglist = NULL) : postfixexpr(_postfixexpr), arglist(_arglist) {}

        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
        virtual void printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const;
};

#endif