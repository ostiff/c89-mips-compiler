#include "ast_dowhile.hpp"

void Do_Statement::printMips(std::ostream &dst, Context &ctx) const{
    int tmp = ctx.getVariableCounter();
    ctx.increaseScopeCounter();
    std::string _top = makeName("while_top");
    std::string _end = makeName("while_end");
    std::string _continue = makeName("continue");

    //break_label = _end;
    break_label.push_back(_end);

    //continue_label = _continue;
    continue_label.push_back(_top);

    dst << _top << ":\n";
    statement->printMips(dst, ctx);
    if(ctx.getVariableCounter() > tmp){
        int another_tmp = (ctx.getVariableCounter()-tmp)*4;
        dst << "addiu $sp, $sp, " << another_tmp << "\n";
    }
    std::string reg = "$t0";
    dst << _continue << ":\n";
    expr->printMipsExpr(dst, reg, ctx);
    dst << "bne " << reg << ", $zero, " << _top << "\n";
    dst << _end << ":\n";

    break_label.pop_back();
    continue_label.pop_back();

    ctx.clearBindings();
    ctx.decreaseScopeCounter();
    ctx.setVariableCounter(tmp);
}