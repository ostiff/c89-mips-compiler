#ifndef AST_SCOPE_HPP
#define AST_SCOPE_HPP

#include <iostream>

#include "ast_expression.hpp"
#include "ast_list.hpp"
#include "ast_binexpr.hpp"
#include "ast_unary.hpp"
#include "ast_postfix.hpp"

class Scope : public Expression {
    private:
        ExpressionPtr declList;
        ExpressionPtr statList;

    public:
        Scope(ExpressionPtr _declList = NULL, ExpressionPtr _statList = NULL) : declList(_declList), statList(_statList) {}
        
        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};


#endif