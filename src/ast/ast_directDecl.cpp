#include "ast_directDecl.hpp"

int Direct_Declarator::getArgNumber(){
    if(arbitrary != NULL){
        return arbitrary->getSize();
    }
    return 0;
}

void Direct_Declarator::printPy(std::ostream &dst, int depth) const{
    if(string1 == "(" && string2 == ")" && directDecl == NULL){
        dst << "(";
        arbitrary->printPy(dst,depth);
        dst << ")";
    }
    else if(string1 == "(" && string2 == ")" && directDecl != NULL && arbitrary == NULL){
        directDecl->printPy(dst,depth);
        dst << "()";
    }
    else if(string1 == "(" && string2 == ")" && directDecl != NULL && arbitrary != NULL){
        directDecl->printPy(dst,depth);
        dst << "(";
        arbitrary->printPy(dst,depth,0);
        dst << ")";
    }
}

void Direct_Declarator::printMips(std::ostream &dst, Context &ctx) const { 
    if(dynamic_cast<Identifier*> (directDecl)){
        current_function_name = directDecl->getID();
    }
    std::vector<std::string> params;
    if(dynamic_cast<List*> (arbitrary)){
        for(int i = 0; i < arbitrary->getSize(); i++){
            if(dynamic_cast<Parameter_Declaration*> (arbitrary->getElement(i))){
                std::string tmp = arbitrary->getElement(i)->getDecl()->getID();
                params.push_back(tmp);
            }
        }
    }
    ctx.insertFunction(current_function_name, params);
}
