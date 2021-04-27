#include "ast_parameter.hpp"

std::string Parameter_Declaration::getdeclSpec() const{
    return declSpec;
}

ExpressionPtr Parameter_Declaration::getDecl() const{
    return decl;
}

ExpressionPtr Parameter_Declaration::getAbstDecl() const{
    return abstDecl;
}

void Parameter_Declaration::printPy(std::ostream &dst, int depth) const{
    if(decl != NULL){
        decl->printPy(dst,depth);
    }
}