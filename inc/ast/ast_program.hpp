#ifndef AST_PROGRAM_HPP
#define AST_PROGRAM_HPP

#include <vector>
#include <typeinfo>

#include "ast_expression.hpp"
#include "ast_declaration.hpp"
#include "ast_function.hpp"

class Program : public Expression {
    private:
        std::vector<ExpressionPtr> program_fragment;

    public:
        void insert(ExpressionPtr _expression);

        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

#endif