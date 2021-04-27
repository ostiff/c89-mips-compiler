#include "ast_variable.hpp"

void Identifier::printPy(std::ostream &dst, int depth) const{
    dst << ID;
}

void Identifier::printMips(std::ostream &dst, Context &ctx) const { 
    dst << ID;
}

void Identifier::printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const{
    if(ctx.checkBindings(ID)){
        dst << "lw " << destreg << ", " << ctx.LocalReturnAddress(ID) << "($fp)" << "\n"; // returns declared local variables
    }
    else if(ctx.ArgIndex(ID, current_function_name) != -1){ // returns function parameters
        int index = ctx.ArgIndex(ID, current_function_name);
        if(index <= 3){
            dst << "addu " << destreg << ", $a"<<  index << ", $zero\n";
        }
        else{
            int relative_address = 4*index+12;
            dst << "lw " << destreg << ", " << relative_address << "($fp)\n";
         }
    }
    else{
        dst << "lw " << destreg << ", " << ID << "\n"; //returns global variables
    }
}

std::string Identifier::getID(){
    return ID;
}