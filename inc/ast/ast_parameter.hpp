#ifndef AST_PARAMETER_HPP
#define AST_PARAMETER_HPP

#include <string>

#include "ast_expression.hpp"

class Parameter_Declaration : public Expression{
    protected:
        std::string declSpec;
        ExpressionPtr decl;
        ExpressionPtr abstDecl;
        
    public:
        Parameter_Declaration(const std::string &_declSpec, ExpressionPtr _decl = NULL, ExpressionPtr _abstDecl = NULL) : declSpec(_declSpec), decl(_decl), abstDecl(_abstDecl) {}

        std::string getdeclSpec() const;
        ExpressionPtr getDecl() const;
        ExpressionPtr getAbstDecl() const;
       
        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const { }
};


#endif