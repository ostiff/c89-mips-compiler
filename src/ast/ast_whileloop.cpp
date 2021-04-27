#include "ast_whileloop.hpp"

void While_Statement::printPy(std::ostream &dst, int depth) const{

    if(dynamic_cast<Scope*> (statement)){
        dst << "while (";
        expr->printPy(dst,depth);
        dst << "):\n";
        statement->printPy(dst,depth);
    }
    else{
        dst << "while (";
        expr->printPy(dst,depth);
        dst << "):\n";
        PyTab ++;
        for(int i = 0; i < PyTab;i++){
            dst << "\t";
        }
        if(statement !=NULL){
            statement->printPy(dst,depth);
        }
        else{
            dst << "pass\n";
        }
        PyTab --;
        
    }
}

void While_Statement::printMips(std::ostream &dst, Context &ctx) const {
    int tmp = ctx.getVariableCounter();
    ctx.increaseScopeCounter();
    std::string _top = makeName("while_top");
    std::string _end = makeName("while_end");

    //break_label = _end;
    break_label.push_back(_end);

    //continue_label = _top;
    continue_label.push_back(_top);

    dst << _top << ":\n";
    std::string reg = "$t0";
    expr->printMipsExpr(dst, reg, ctx);
    dst << "beq $t0, $zero, " << _end << "\n";
    dst << "nop\n";
    statement->printMips(dst, ctx);
    if(ctx.getVariableCounter() > tmp){
        int another_tmp = (ctx.getVariableCounter()-tmp)*4;
        dst << "addiu $sp, $sp, " << another_tmp << "\n";
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
