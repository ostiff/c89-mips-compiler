#include "ast_unary.hpp"

ExpressionPtr Unary_Expression::getRight() const{
    return right;
}

const std::string Unary_Expression::getOperator() const {
    return Operator;
}

void Unary_Expression::printPy(std::ostream &dst, int depth) const{
    if(Operator == "-"){
        dst << "-(";
        right->printPy(dst, 0);
        dst << ")";
    }
}

void Unary_Expression::printMips(std::ostream &dst, Context &ctx) const{}

void Unary_Expression::printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const{
    if(Operator == "++"){
        std::string var = right->getID();
        var = ctx.returnID(var);
        std::string reg = "$t1";
        right->printMipsExpr(dst, reg, ctx);
        dst << "addiu " << destreg << ", " << reg << ", 1\n";
        dst << "sw " << destreg << ", " << var << "\n";
    }
    else if(Operator == "--"){
        std::string var = right->getID();
        var = ctx.returnID(var);
        std::string reg = "$t1";
        right->printMipsExpr(dst, reg, ctx);
        dst << "addiu " << destreg << ", " << reg << ", -1\n";
        dst << "sw " << destreg << ", " << var << "\n";
    }
    else if(Operator == "~"){ // bitwise not
        right->printMipsExpr(dst, destreg, ctx);
        dst << "nor " << destreg << ", " << destreg << ", $zero\n";
    }
    else if(Operator == "!"){ // logical not
        std::string _one = makeName("one");
        std::string _end = makeName("end");
        right->printMipsExpr(dst, destreg, ctx);
        dst << "bne " << destreg << ", $zero," << _one << "\n";
        dst << "nop\n";
        dst << "addiu " << destreg << ", $zero, 1\n";
        dst << "j " << _end << "\n";
        dst << "nop\n";
        dst << _one << ":\n";
        dst << "addu " << destreg << ", $zero, $zero\n";
        dst << _end << ":\n";
    }
    else if(Operator == "+"){
        right->printMipsExpr(dst, destreg, ctx);
    }
    else if(Operator == "-"){
        right->printMipsExpr(dst, destreg, ctx);
        dst << "nor " << destreg << ", " << destreg << ", $zero\n";
        dst << "addiu " << destreg << ", " << destreg << ", 1\n";
    }
    else if(Operator == "&"){
        std::string var = right->getID();
        var = ctx.returnID(var);
        dst << "la " << destreg << ", " << var << "\n";
    }
    else if(Operator == "*"){
            
    }
}

