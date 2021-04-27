#ifndef AST_LIST_HPP
#define AST_LIST_HPP

#include <vector>
#include <string>

#include "ast_expression.hpp"

class List : public Expression {

    private:
        std::vector<ExpressionPtr> element_list;

    public:
        List(ExpressionPtr _element){
            insert(_element);
        }

        void insert(const ExpressionPtr _expression); //added const!!!

        virtual void printPy(std::ostream &dst, int depth, int listType) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const { }

        virtual ExpressionPtr getElement(int i);
        virtual int getSize();
};

#endif