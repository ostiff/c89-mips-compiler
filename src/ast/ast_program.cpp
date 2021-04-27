#include "ast_program.hpp"

void Program::insert(ExpressionPtr _expression){
    if(_expression){
        program_fragment.push_back(_expression);
    }
}

void Program::printPy(std::ostream &dst, int depth) const{
    for(unsigned i = 0; i < program_fragment.size(); i++){
        if(dynamic_cast<Declaration*> (program_fragment[i])){
            program_fragment[i]->printPy(dst);
        }
    }
    
    for(unsigned i = 0; i < program_fragment.size(); i++){
        if(dynamic_cast<Function_Definition*> (program_fragment[i])){
            program_fragment[i]->printPy(dst);
        }
    }
}

void Program::printMips(std::ostream &dst, Context &ctx) const{
    for(unsigned i = 0; i < program_fragment.size(); i++){
        if(dynamic_cast<Declaration*> (program_fragment[i])){
            program_fragment[i]->printMips(dst,ctx);
        }
    }
    
    for(unsigned i = 0; i < program_fragment.size(); i++){
        if(dynamic_cast<Function_Definition*> (program_fragment[i])){
            program_fragment[i]->printMips(dst,ctx);
        }
    }

}