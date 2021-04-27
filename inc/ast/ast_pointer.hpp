#ifndef AST_POINTER_HPP
#define AST_POINTER_HPP

#include "ast_expression.hpp"

class Pointer : public Expression {
    private:
        ExpressionPtr type_qual_list;
        ExpressionPtr ptr;

    public:
        Pointer(ExpressionPtr _type_qual_list = NULL, ExpressionPtr _ptr = NULL) : type_qual_list(_type_qual_list), ptr(_ptr) {}
};

#endif