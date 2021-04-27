#include "ast_int.hpp"


void Integer_Constant::printPy(std::ostream &dst, int depth) const{
    dst << value;
}

void Integer_Constant::printMips(std::ostream &dst, Context &ctx) const {
    dst << value;
}

void Integer_Constant::printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const{
    int tmp_hi = (value & 0b11111111111111110000000000000000)>>16;
    int tmp_lo = value & 0b00000000000000001111111111111111;
    
    dst << "lui " << destreg << ", " << tmp_hi << "\n"; 
    dst << "li " << destreg << ", " << tmp_lo << "\n"; 
}

int Integer_Constant::getSize(){
    return value;
}