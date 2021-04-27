#include "ast_conditional.hpp"


void Conditional_Expression::printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const {
        std::string _end = makeName("if_end");
        std::string _else = makeName("else");
        std::string reg = "$t0";
        logical->printMipsExpr(dst, reg, ctx);
        dst << "beq $t0, $zero, " << _else << "\n";
        dst << "nop\n"; // is this nop needed?
        expr->printMipsExpr(dst, destreg, ctx);
        dst << "j " << _end << "\n";
        dst << "nop\n";
        dst << _else << ":\n";
        conditional->printMipsExpr(dst, destreg, ctx);
        dst << _end << ":\n";
}