#include "ast_function.hpp"

void Function_Definition::printPy(std::ostream &dst, int depth) const{
    dst << "\ndef ";
    decl->printPy(dst, depth);
    if(decList != NULL){
        decList->printPy(dst,depth,0);
    }
    dst << ":\n";
    for(unsigned i = 0; i < py_var_table.size(); i++){
        dst << "\tglobal " ;
        py_var_table[i]->printPy(dst,0);
        dst << "\n";
    }
    compStat->printPy(dst,depth);
}

void Function_Definition::printMips(std::ostream &dst, Context &ctx) const {
    //increase to keep track of vars
    ctx.increaseScopeCounter();

    current_function_type = decSpec; // function return type
    decl->printMips(dst,ctx);

    if(current_function_name == "main"){
        dst << "###MAIN: FUNCTION ENTRY###\n";

        //Function Preamble
        dst << "\t.set noreorder\n";
        dst << "\t.text\n";
        dst << "\t.align 2\n";
        dst << "\t.globl ";
        dst << current_function_name << "\n";
        dst << current_function_name << ":\n";

        dst << "addiu $sp, $sp, -12\n";
        dst << "sw $fp, 4($sp)\n";
        dst << "sw $ra, 8($sp)\n";
        dst << "move $fp, $sp\n";
        dst << "addiu $sp, $sp, -4\n";

        //Function Body
        compStat->printMips(dst,ctx);
        dst << "###MAIN: FUNCTION RETURN###\n";

        dst << "_return_" << current_function_name << ":\n";
        dst << "move $sp, $fp\n";
        dst << "lw $ra, 8($fp)\n";
        dst << "lw $fp, 4($fp)\n";
        dst << "addiu $sp, $sp, 12\n";
        dst << "jr $ra\n";
        dst << "nop\n";
    }
    else{
        //Function Preamble
        dst << "###" << current_function_name << ": FUNCTION ENTRY###\n";

        dst << "\t.set noreorder\n";
        dst << "\t.text\n";
        dst << "\t.align 2\n";
        dst << "\t.globl ";
        dst << current_function_name << "\n";
        dst << current_function_name << ":\n";

        //Function Entry
        dst << "###STORING FUNCTION ARGUMENTS###\n";
        dst << "sw $a0, 0($sp)\n";
        dst << "sw $a1, 4($sp)\n";
        dst << "sw $a2, 8($sp)\n";
        dst << "sw $a3, 12($sp)\n";

        dst << "addiu $sp, $sp, -12\n";
        dst << "sw $fp, 4($sp)\n";
        dst << "sw $ra, 8($sp)\n";
        dst << "move $fp, $sp\n";
        dst << "addiu $sp, $sp, -4\n";

        //Function Body
        compStat->printMips(dst,ctx);

        dst << "###" << current_function_name << ": FUNCTION RETURN###\n";
        dst << "_return_" << current_function_name << ":\n";

        int arguments;

        if(argNumber <= 4){
            arguments = 4*4;
        }
        else{
            arguments = 4*argNumber;
        }

        dst << "move $sp, $fp\n";
        dst << "lw $ra, 8($fp)\n";
        dst << "lw $fp, 4($fp)\n";
        dst << "addiu $sp, $sp, 12\n";
        dst << "addiu $sp, $sp, " << arguments << "\n";
        dst << "jr $ra\n";
        dst << "nop\n";
    }
    ctx.clearBindings();
    ctx.decreaseScopeCounter();
}

void Function_Call::printPy(std::ostream &dst, int depth) const{
    postfixexpr->printPy(dst,depth);
    dst << "(";
    if(arglist != NULL){
        arglist->printPy(dst,depth,0);
    }
    dst << ")";
}

void Function_Call::printMipsExpr(std::ostream &dst, std::string &destreg, Context &ctx) const{
    std::stringstream jump_to;
    postfixexpr->printMips(jump_to,ctx);
    std::string jump_to_string = jump_to.str();
    dst << "###" << jump_to_string << ": FUNCTION CALL###\n";

    int argument_number = ctx.getArgNumber(jump_to_string);
    for(int j = 4-argument_number; j > 0; j--){
        dst << "addiu $sp, $sp, -4\n";
    }
    
    for(int i = ctx.getArgNumber(jump_to_string)-1; i >= 0 ; i--){
        ExpressionPtr tmp = arglist->getElement(i);
        std::string reg = "$t0";
        tmp->printMipsExpr(dst,reg, ctx);
        if(i<4){
            dst << "addu $a" << i << ", $zero, $t0\n";
        }
        dst << "sw $t0, 0($sp)\n";
        dst << "addiu $sp, $sp, -4\n";
    }    
    dst << "jal " << jump_to_string;
    dst << "\nnop\n";
    dst << "add $t0, $zero, $v0\n";

    dst << "###RESTORING FUNCTION ARGUMENTS###\n";
    dst << "lw $a3, 12($sp)\n";
    dst << "lw $a2, 8($sp)\n";
    dst << "lw $a1, 4($sp)\n";
    dst << "lw $a0, 0($sp)\n";
    dst << "###" << jump_to_string << ": END FUNCTION CALL###\n";

}

void Function_Call::printMips(std::ostream &dst, Context &ctx) const{
    std::string reg = "$t8"; // choose a random register...
    printMipsExpr(dst, reg, ctx);
}