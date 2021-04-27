#ifndef AST_LABELED_HPP
#define AST_LABELED_HPP

#include <string>

#include "ast_expression.hpp"
#include "ast_binexpr.hpp"
#include "ast_postfix.hpp"
#include "ast_unary.hpp"

class Labeled_Statement : public Expression{
    protected:
        std::string ID;
        ExpressionPtr expr;
        ExpressionPtr statement;

    public:
        Labeled_Statement(const std::string &_ID, ExpressionPtr _expr = NULL, ExpressionPtr _statement = NULL) : ID(_ID), expr(_expr), statement(_statement) {}

        ExpressionPtr getStatement() const;
        ExpressionPtr getExpression() const;
        virtual const std::string getID() const;
        
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};


#endif
