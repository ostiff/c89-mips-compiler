#include "ast_if.hpp"

void If_Statement::printPy(std::ostream &dst, int depth) const{
    dst << "if (";
    expr->printPy(dst,depth);
    dst << "):\n";
    if(statement_if !=NULL){
        if(dynamic_cast<Scope*> (statement_if)){
            statement_if->printPy(dst,depth);
        }
        else{
            PyTab ++;
            for(int i = 0; i < PyTab;i++){
                dst << "\t";
            }
            statement_if->printPy(dst,depth);
            dst << "\n";
            PyTab --;
        }
    }
    else{
        PyTab ++;
        for(int i = 0; i < PyTab;i++){
            dst << "\t";
        }
        dst << "pass\n";
        PyTab --;
    }
    if(statement_else != NULL){
        for(int i = 0; i < PyTab;i++){
            dst << "\t";
        }
        dst << "else:\n";
        if(dynamic_cast<Scope*> (statement_else)){
            statement_else->printPy(dst,depth);
        }
        else{
            PyTab ++;
            for(int i = 0; i < PyTab;i++){
                dst << "\t";
            }
            statement_else->printPy(dst,depth);
            PyTab --;
        }


    }
    else{
        for(int i = 0; i < PyTab;i++){
            dst << "\t";
        }
        dst << "else:\n";
        PyTab ++;
        for(int i = 0; i < PyTab;i++){
            dst << "\t";
        }
        dst << "pass\n";
        PyTab --;
    }        
}

void If_Statement::printMips(std::ostream &dst, Context &ctx) const{
    int tmp = ctx.getVariableCounter();
    ctx.increaseScopeCounter();
    if(statement_else != NULL){
        std::string _end = makeName("if_end");
        std::string _else = makeName("else");
        std::string reg = "$t0";
        expr->printMipsExpr(dst, reg, ctx);
        dst << "beq $t0, $zero, " << _else << "\n";
        dst << "nop\n";

        if (dynamic_cast<Binary_Expression*> (statement_if) || dynamic_cast<Unary_Expression*> (statement_if) || dynamic_cast<Postfix_Expression*> (statement_if)) {
            std::string reg = "$t0";
            statement_if->printMipsExpr(dst, reg, ctx);
        }
        else{
            statement_if->printMips(dst, ctx);
        }
        
        if(ctx.getVariableCounter() > tmp){
            int another_tmp = (ctx.getVariableCounter()-tmp)*4;
            dst << "addiu $sp, $sp, " << another_tmp << "\n";
        }

        ctx.setVariableCounter(tmp);
        dst << "j " << _end << "\n";
        dst << "nop\n";
        dst << _else << ":\n";
        ctx.clearBindings();

        if (dynamic_cast<Binary_Expression*> (statement_else) || dynamic_cast<Unary_Expression*> (statement_else) || dynamic_cast<Postfix_Expression*> (statement_else)) {
            std::string reg = "$t0";
            statement_else->printMipsExpr(dst, reg, ctx);
        }
        else{
            statement_else->printMips(dst, ctx);
        }

        if(ctx.getVariableCounter() > tmp){
            int another_tmp = (ctx.getVariableCounter()-tmp)*4;
            dst << "addiu $sp, $sp, " << another_tmp << "\n";
        }
        ctx.setVariableCounter(tmp);
        dst << _end << ":\n";
    }
    else{
        std::string _end = makeName("if_end");
        std::string reg = "$t0";
        expr->printMipsExpr(dst, reg, ctx);
        dst << "beq $t0, $zero, " << _end << "\n";
        dst << "nop\n";

        if (dynamic_cast<Binary_Expression*> (statement_if) || dynamic_cast<Unary_Expression*> (statement_if) || dynamic_cast<Postfix_Expression*> (statement_if)) {
            std::string reg = "$t0";
            statement_if->printMipsExpr(dst, reg, ctx);
        }
        else{
            statement_if->printMips(dst, ctx);
        }  
              
        if(ctx.getVariableCounter() > tmp){
            int another_tmp = (ctx.getVariableCounter()-tmp)*4;
            dst << "addiu $sp, $sp, " << another_tmp << "\n";
        }
        ctx.setVariableCounter(tmp);
        dst << _end << ":\n";
    }
    ctx.clearBindings();
    ctx.decreaseScopeCounter();
}
