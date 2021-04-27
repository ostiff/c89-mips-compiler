#ifndef AST_EXPRESSION_HPP
#define AST_EXPRESSION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "context.hpp"

class Expression;

typedef  Expression *ExpressionPtr;

extern std::vector<ExpressionPtr> py_var_table; // used for python global variables
extern int PyTab;
extern std::string current_function_type;
extern std::string current_function_name;
extern std::vector<std::string> break_label;
extern std::vector<std::string> continue_label;
extern std::vector<int> switch_number;


// All other expressions inherit from this Expression class (e.g. Binary_Expression)
class Expression{
    public:
        virtual void insert(ExpressionPtr element) {}
        virtual ~Expression() {}
        virtual void printPy(std::ostream &dst, int depth = 0) const {}
        virtual void printPy(std::ostream &dst, int depth, int listType) const {}
        virtual void printMips(std::ostream &dst, Context &ctx) const {}
        virtual void printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const {}
        virtual std::string getID() {return "";}
        virtual ExpressionPtr getElement(int i) {return NULL;}
        virtual int getSize() {return 0;}
        virtual int getArgNumber() {return 0;}
        virtual ExpressionPtr getDecl() const {return NULL;}
        virtual void printInitDeclaration(std::ostream &dst, Context &ctx, const std::string &Type) const {}
};

#endif