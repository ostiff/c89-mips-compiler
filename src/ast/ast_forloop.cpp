#include "ast_forloop.hpp"

void For_Statement::printMips(std::ostream &dst, Context &ctx) const{
    int tmp = ctx.getVariableCounter();
    ctx.increaseScopeCounter();
    std::string _top = makeName("for_top");
    std::string _end = makeName("for_end");
    std::string _continue = makeName("for_continue");

    //break_label = _end;
    break_label.push_back(_end);

    //continue_label = _top;
    continue_label.push_back(_continue);

    std::string reg = "$t0";
    if(expr1 != NULL){
        expr1->printMipsExpr(dst, reg, ctx);
    }
    dst << _top << ":\n";



    if(expr2 != NULL){
        expr2->printMipsExpr(dst, reg, ctx);
    }
    else{
        dst << "addiu " << reg << ", $zero, 1\n"; 
    }
    dst << "beq $t0, $zero, " << _end << "\n";
    dst << "nop\n";
    statement->printMips(dst, ctx);
    if(ctx.getVariableCounter() > tmp){
        int another_tmp = (ctx.getVariableCounter()-tmp)*4;
        dst << "addiu $sp, $sp, " << another_tmp << "\n";
    }
    dst << _continue << ":\n";
    if(expr3 != NULL){
        expr3->printMipsExpr(dst, reg, ctx);
    }
    dst << "j " << _top << "\n";
    dst << "nop\n";
    dst << _end << ":\n";

    
    break_label.pop_back();
    continue_label.pop_back();

    ctx.clearBindings();
    ctx.decreaseScopeCounter();
    ctx.setVariableCounter(tmp);
}
