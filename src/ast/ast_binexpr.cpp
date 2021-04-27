#include "ast_binexpr.hpp"


ExpressionPtr Binary_Expression::getLeft() const{
    return left;
}

ExpressionPtr Binary_Expression::getRight() const{
    return right;
}

const std::string Binary_Expression::getOperator() const {
    return Operator;
}

void Binary_Expression::printPy(std::ostream &dst, int depth) const{
    std::string op;
    if(Operator == "&&"){
        op = " and ";
    }
    else if(Operator == "||"){
        op = " or ";
    }
    else{
        op  = Operator;
    }

    if(dynamic_cast<Binary_Expression*> (left)){
        dst << "(";
        left->printPy(dst,depth);
        dst << ")";
    }
    else{
        left->printPy(dst,depth);
    }

    dst << op;

    if(dynamic_cast<Binary_Expression*> (right)){
        dst << "(";
        right->printPy(dst,depth);
        dst << ")";
    }
    else{
        right->printPy(dst,depth);
    }

}

void Binary_Expression::printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const { 
    if(Operator == "+"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "add " << destreg << ", $t1, " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "-"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "sub " << destreg << ", $t1, " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "<<"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "sllv " << destreg << ", $t1, " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == ">>"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "srav " << destreg << ", $t1, " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "*"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "mul " << destreg << ", $t1, " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "/"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "div $t1, " << destreg << "\n";
        dst << "mflo " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "%"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "div $t1, " << destreg << "\n";
        dst << "mfhi " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "<"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "slt " << destreg << ", $t1, " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == ">"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "slt " << destreg << ", " << destreg << ", $t1\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "<="){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "slt $t2, $t1, " << destreg << "\n";
        dst << "xor $t3, " << destreg << ", $t1\n";
        dst << "sltiu $t3, $t3, 1\n";
        dst << "or " << destreg << ", $t2, $t3\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == ">="){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "slt $t2, " << destreg << ", $t1\n";
        dst << "xor $t3, " << destreg << ", $t1\n";
        dst << "sltiu $t3, $t3, 1\n";
        dst << "or " << destreg << ", $t2, $t3\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "=="){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "xor $t1, " << destreg << ", $t1\n";
        dst << "sltiu " << destreg << ", $t1, 1\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "!="){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "xor $t1, " << destreg << ", $t1\n";
        dst << "sltu " << destreg << ", $zero, $t1\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "&"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "and " << destreg << ", $t1, " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "|"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "or " << destreg << ", $t1, " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "^"){
        left->printMipsExpr(dst, destreg, ctx);
        dst << "sw " << destreg << ", 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "lw $t1, 4($sp)\n";
        dst << "xor " << destreg << ", $t1, " << destreg << "\n";
        dst << "addiu $sp, $sp, 4\n";
    }
    else if(Operator == "="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
    else if(Operator == "&&"){
        std::string _success_end = makeName("logical_and_success");
        std::string _fail_end = makeName("logical_and_fail");
        left->printMipsExpr(dst, destreg, ctx);
        dst << "beq " << destreg << ", $zero, " << _fail_end << "\n";
        dst << "nop\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "beq " << destreg << ", $zero, " << _fail_end << "\n";
        dst << "nop\n";
        dst << "addiu " << destreg << ", $zero, 1\n";
        dst << "j " << _success_end << "\n";
        dst << "nop\n";
        dst << _fail_end << ":\n";
        dst << "addu " << destreg << ", $zero, $zero\n";
        dst << _success_end << ":\n";
    }
    else if(Operator == "||"){
        std::string _success_end = makeName("logical_or_success");
        std::string _fail_end = makeName("logical_or_fail");
        left->printMipsExpr(dst, destreg, ctx);
        dst << "bne " << destreg << ", $zero, " << _success_end << "\n";
        dst << "nop\n";
        right->printMipsExpr(dst, destreg, ctx);
        dst << "bne " << destreg << ", $zero, " << _success_end << "\n";
        dst << "nop\n";
        dst << "addu " << destreg << ", $zero, $zero\n";
        dst << "j " << _fail_end << "\n";
        dst << "nop\n";
        dst << _success_end << ":\n";
        dst << "addiu " << destreg << ", $zero, 1\n";
        dst << _fail_end << ":\n";
    }
    else if(Operator == "+="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "add " << destreg << ", " << destreg << ", " << reg << "\n";
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "add " << destreg << ", " << destreg << ", " << reg << "\n";
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
    else if(Operator == "-="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "sub " << destreg << ", " << reg << ", " << destreg << "\n";
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "sub " << destreg << ", " << reg << ", " << destreg << "\n";
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
    else if(Operator == "*="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "mul " << destreg << ", " << destreg << ", " << reg << "\n";
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "mul " << destreg << ", " << destreg << ", " << reg << "\n";
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
    else if(Operator == "<<="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "sllv " << destreg << ", " << reg << ", " << destreg << "\n";
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "sllv " << destreg << ", " << reg << ", " << destreg << "\n";
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
    else if(Operator == ">>="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "srav " << destreg << ", " << reg << ", " << destreg << "\n";
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "srav " << destreg << ", " << reg << ", " << destreg << "\n";
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
    else if(Operator == "&="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "and " << destreg << ", " << destreg << ", " << reg << "\n";
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "and " << destreg << ", " << destreg << ", " << reg << "\n";
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
    else if(Operator == "|="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "or " << destreg << ", " << destreg << ", " << reg << "\n";
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "or " << destreg << ", " << destreg << ", " << reg << "\n";
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
    else if(Operator == "^="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "xor " << destreg << ", " << destreg << ", " << reg << "\n";
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "xor " << destreg << ", " << destreg << ", " << reg << "\n";
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
    else if(Operator == "/="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "div " << reg << ", " << destreg << "\n";
            dst << "mflo " << destreg << "\n";
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "div " << reg << ", " << destreg << "\n";
            dst << "mflo " << destreg << "\n";
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
    else if(Operator == "%="){
        if(dynamic_cast<Postfix_Expression*> (left)){
            left->printMips(dst,ctx);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "div " << reg << ", " << destreg << "\n";
            dst << "mfhi " << destreg << "\n";
            dst << "sw " << destreg << ", 0($t7)\n";
        }
        else{
            std::string var = left->getID();
            var = ctx.returnID(var);
            right->printMipsExpr(dst, destreg, ctx);
            std::string reg = "$t1";
            left->printMipsExpr(dst, reg, ctx);
            dst << "div " << reg << ", " << destreg << "\n";
            dst << "mfhi " << destreg << "\n";
            dst << "sw " << destreg << ", " << var << "\n";
        }
    }
}