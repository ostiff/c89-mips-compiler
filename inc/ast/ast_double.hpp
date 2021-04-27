#ifndef AST_DOUBLE_HPP
#define AST_DOUBLE_HPP


#include "ast_expression.hpp"

class Floating_Constant : public Expression {
    private:
        double value;

    public:
        Floating_Constant(double _value) : value(_value) {}
        
        virtual void printPy(std::ostream &dst, int depth = 0) const{}
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};

#endif