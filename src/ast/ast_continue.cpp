#include "ast_continue.hpp"

void Continue_Statement::printMips(std::ostream &dst, Context &ctx) const{
    dst << "j " << continue_label[continue_label.size()-1] << "\n";
    dst << "nop\n";
}