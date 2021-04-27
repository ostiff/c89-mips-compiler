#include "ast_postfix.hpp"

ExpressionPtr Postfix_Expression::getleft() const{
    return left;
}

const std::string Postfix_Expression::getOperator() const{
    return Operator;
}

const std::string Postfix_Expression::getID() const{
    return ID;
}

void Postfix_Expression::printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const{
    if(Operator == "++"){
        std::string var = left->getID();
        var = ctx.returnID(var);
        std::string reg = "$t1";
        left->printMipsExpr(dst, reg, ctx);
        dst << "addiu " << destreg << ", " << reg << ", 1\n";
        dst << "sw " << destreg << ", " << var << "\n";
        dst << "addiu " << destreg << ", " << destreg << ", -1\n";
    }
    else if(Operator == "--"){
        std::string var = left->getID();
        var = ctx.returnID(var);
        std::string reg = "$t1";
        left->printMipsExpr(dst, reg, ctx);
        dst << "addiu " << destreg << ", " << reg << ", -1\n";
        dst << "sw " << destreg << ", " << var << "\n";
        dst << "addiu " << destreg << ", " << destreg << ", 1\n";
    }
    else if(Operator == "["){
        std::string reg = "$t1";
        std::string var = left->getID();
        if(ctx.checkBindings(var)){//local array
            var = ctx.returnID(var);
            int pos = std::stoi(var);
            right->printMipsExpr(dst, reg, ctx);
            dst << "addi $t2, $zero, -4\n";
            dst << "mul $t1, $t1, $t2\n";
            dst << "addi $t1, $t1, " << pos << "\n";
            dst << "add $t1, $t1, $fp\n";
        }
        else{
            right->printMipsExpr(dst, reg, ctx);
            dst << "addi $t2, $zero, 4\n";
            dst << "mul $t1, $t1, $t2\n";
            dst << "la $t2, " << var << "\n";
            dst << "add $t1, $t1, $t2\n";
        }
        dst << "lw " << destreg << ", 0($t1)\n";
    }
}

void Postfix_Expression::printMips(std::ostream &dst, Context &ctx) const{
    std::string var = left->getID(); //t7 designated array register
    std::string reg = "$t7";
    if(ctx.checkBindings(var)){//local array
        var = ctx.returnID(var);
        int pos = std::stoi(var);
        right->printMipsExpr(dst, reg, ctx);
        dst << "addi $t2, $zero, -4\n";
        dst << "mul $t7, $t7, $t2\n";
        dst << "addi $t7, $t7, " << pos << "\n";
        dst << "add $t7, $t7, $fp\n";
    }
    else{//global array
        right->printMipsExpr(dst, reg, ctx);
        dst << "addi $t2, $zero, 4\n";
        dst << "mul $t7, $t7, $t2\n";
        dst << "la $t2, " << var << "\n";
        dst << "add $t7, $t7, $t2\n";
    }
}
