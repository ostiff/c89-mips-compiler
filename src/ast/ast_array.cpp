#include "ast_array.hpp"

int Array::getSize(){
    if(dynamic_cast<Integer_Constant*> (expr)){
        return expr->getSize();
    }
    std::cerr << "ERROR: Variable array declared: not yet supported\n";
    exit(1);
}

std::string Array::getID(){
    if(dynamic_cast<Identifier*> (postfixexpr)){
        return postfixexpr->getID();
    }
    return "";
}