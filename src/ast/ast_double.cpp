#include "ast_double.hpp"

void Floating_Constant::printMips(std::ostream &dst, Context &ctx) const { 
    dst << value;
}