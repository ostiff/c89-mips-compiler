#include "ast_return.hpp"

void Return_Statement::printPy(std::ostream &dst, int depth) const{
    dst << "return ";
    if(expr != NULL){
        expr->printPy(dst,depth);
    }
}

void Return_Statement::printMips(std::ostream &dst, Context &ctx) const {
    if(expr){
        if((current_function_type == "float") || (current_function_type == "double")){
            if(dynamic_cast<Integer_Constant*> (expr)){
                dst << "addiu $f0, $0, ";
                expr->printMips(dst, ctx);
                dst << "\n";
            }
            else{
                std::string destreg = "$f0";
                expr->printMipsExpr(dst, destreg, ctx);
            }
        }
        // int
        else{
            if(dynamic_cast<Integer_Constant*> (expr)){
                dst << "addiu $v0, $0, ";
                expr->printMips(dst, ctx);
                dst << "\n";
            }
            else{
                std::string destreg = "$v0";
                expr->printMipsExpr(dst, destreg, ctx);
            }
        }
    }
    dst << "j _return_" << current_function_name << "\n";
    dst << "nop\n";
}