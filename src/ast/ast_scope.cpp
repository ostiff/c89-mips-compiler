#include "ast_scope.hpp"

void Scope::printPy(std::ostream &dst, int depth) const{
    PyTab ++; // increase indentation when entering a new scope
    if(declList != NULL){
        declList->printPy(dst,depth+1,1);
    }
    if(statList != NULL){
        statList->printPy(dst,depth+1,1);
    }
    if(declList == NULL && statList==NULL){
        for(int j = 0; j < PyTab; j++){
            dst << "\t";
        }
        dst << "pass\n";
    }
    PyTab --; // decrease indentation when leaving the scope
}

void Scope::printMips(std::ostream &dst, Context &ctx) const { 
    if(declList != NULL){
        for(int i = 0; i < declList->getSize(); i++){   
            ExpressionPtr tmp = declList->getElement(i);
            tmp->printMips(dst,ctx);
        }
    }
    if(statList != NULL){
        for(int i = 0; i < statList->getSize(); i++){
            ExpressionPtr tmp = statList->getElement(i);
            if(dynamic_cast<Binary_Expression*> (tmp) || dynamic_cast<Unary_Expression*> (tmp) || dynamic_cast<Postfix_Expression*> (tmp)){
                std::string reg = "$t0";
                tmp->printMipsExpr(dst,reg, ctx);
            }
            else{
                tmp->printMips(dst,ctx);
            }
        }
    }
}