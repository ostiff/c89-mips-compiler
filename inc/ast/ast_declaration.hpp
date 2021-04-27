#ifndef AST_DECLARATION_HPP
#define AST_DECLARATION_HPP

#include <string>
#include <typeinfo>
#include <iostream>

#include "ast_expression.hpp"
#include "ast_list.hpp"
#include "ast_variable.hpp"
#include "context.hpp"
#include "ast_array.hpp"
#include "ast_binexpr.hpp"


class Declaration : public Expression {
    private:
        std::string declSpec;
        ExpressionPtr declList;

    public:
        Declaration(const std::string &_declSpec, ExpressionPtr _declList = NULL) : declSpec(_declSpec), declList(_declList){}
        
        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

class Init_Declarator : public Expression {
    private:
        ExpressionPtr decl;
        ExpressionPtr init;

    public:
        Init_Declarator(ExpressionPtr _decl, ExpressionPtr _init = NULL) : decl(_decl), init(_init){}
        
        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const{}
        virtual void printInitDeclaration(std::ostream &dst, Context &ctx, const std::string &Type) const ;
};

#endif
