#include "ast_switch.hpp"

void Switch_Statement::printMips(std::ostream &dst, Context &ctx) const{
    ctx.increaseScopeCounter();
    ctx.increaseSwitchCounter();
    std::string _EXIT = "_EXIT_SWITCH_" + std::to_string(ctx.getCaseCounter());

    switch_number.push_back(ctx.getSwitchCounter());
    
    //break_label = _EXIT;
    break_label.push_back(_EXIT);

    std::string reg = "$t6"; // dedicated switch register
    expr->printMipsExpr(dst, reg, ctx);
    
    dst << "sw $t6, 0($sp)\n";
    dst << "addiu $sp, $sp, -4\n";
    dst << "sw $t5, 0($sp)\n";
    dst << "addiu $sp, $sp, -4\n";

    dst << "addu $t5, $zero, $zero\n";
    statement->printMips(dst, ctx);
    dst << "case_" << switch_number[switch_number.size()-1] << "_" << ctx.getCaseCounter() << ":\n";
    dst << _EXIT << ":\n";

    dst << "addiu $sp, $sp, 4\n";
    dst << "lw $t5, 0($sp)\n";
    dst << "addiu $sp, $sp, 4\n";
    dst << "lw $t6, 0($sp)\n";

    break_label.pop_back();
    switch_number.pop_back();

    ctx.clearBindings();
    ctx.decreaseScopeCounter();
    ctx.resetCaseCounter();
}
