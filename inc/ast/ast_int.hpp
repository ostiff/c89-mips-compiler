#ifndef AST_INT_HPP
#define AST_INT_HPP

#include <string>

#include "ast_expression.hpp"

class Integer_Constant : public Expression {
    private:
        int value;

    public:
        Integer_Constant(std::string _value) {
            std::string::size_type sz;
            if(_value[0] == '0'){
                if((_value[1] == 'x') || (_value[1] == 'X')){ // hex
                    value = std::stoi(_value, nullptr, 16);
                }
                else{ // octal
                    value = std::stoi(_value, nullptr, 8);
                }
            }
            else{ // base 10
                value = std::stoi(_value, &sz);
            }
        }
        
        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
        virtual void printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const;    
        virtual int getSize();
};

#endif