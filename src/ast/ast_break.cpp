#include "ast_break.hpp"

void Break_Statement::printMips(std::ostream &dst, Context &ctx) const {
    dst << "j " << break_label[break_label.size()-1] << "\n";
    dst << "nop\n";
}