#include "ast_labeled.hpp"

ExpressionPtr Labeled_Statement::getStatement() const{
    return statement;
}

ExpressionPtr Labeled_Statement::getExpression() const{
    return expr;
}

const std::string Labeled_Statement::getID() const {
    return ID;
}

void Labeled_Statement::printMips(std::ostream &dst, Context &ctx) const{
    if(ID == "case"){
        dst << "case_" << ctx.getSwitchCounter() << "_" << ctx.getCaseCounter() << ":\n";
        std::string reg = "$t0";
        dst << "bne $t5, $zero, case_start_" << ctx.getSwitchCounter() << "_" << ctx.getCaseCounter() << "\n";
        dst << "nop\n";
        expr->printMipsExpr(dst, reg, ctx);
        ctx.increaseCaseCounter();
        dst << "bne $t6, $t0, " << "case_" << ctx.getSwitchCounter() << "_" << ctx.getCaseCounter() << "\n";
        dst << "nop\n";
        dst << "case_start_" << ctx.getSwitchCounter() << "_" << ctx.getCaseCounter()-1 << ":\n";
        dst << "addiu $t5, $zero, 1\n";
        if(dynamic_cast<Binary_Expression*> (statement) || dynamic_cast<Unary_Expression*> (statement) || dynamic_cast<Postfix_Expression*> (statement)){
            std::string reg = "$t0";
            statement->printMipsExpr(dst,reg, ctx);
        }
        else{
            statement->printMips(dst,ctx);
        }
    }
}
