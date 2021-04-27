#ifndef AST_DIRECTDECL_HPP
#define AST_DIRECTDECL_HPP

#include <string>

#include "ast_expression.hpp"
#include "ast_variable.hpp"
#include "ast_list.hpp"
#include "ast_parameter.hpp"

class Direct_Declarator : public Expression {
    private:
        ExpressionPtr directDecl;
        std::string string1;
        ExpressionPtr arbitrary;
        std::string string2;

    public:
        Direct_Declarator(ExpressionPtr _directDecl = NULL, const std::string &_string1 = "", ExpressionPtr _arbitrary = NULL, const std::string &_string2 = "") : directDecl(_directDecl), string1(_string1), arbitrary(_arbitrary), string2(_string2) {}
        
        int getArgNumber();

        virtual void printPy(std::ostream &dst, int depth = 0) const;
        virtual void printMips(std::ostream &dst, Context &ctx) const;
};


class Direct_Abstract_Declarator : public Expression {
    
    private:

    public:


};


#endif
