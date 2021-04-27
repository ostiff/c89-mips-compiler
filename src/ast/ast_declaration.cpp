#include "ast_declaration.hpp"

void Declaration::printPy(std::ostream &dst, int depth) const{
    if(declList != NULL){
        declList->printPy(dst,depth,2);
    }
}

void Declaration::printMips(std::ostream &dst, Context &ctx) const { 
    for(int i = 0; i < declList->getSize(); i++){   
        ExpressionPtr tmp = declList->getElement(i);
        tmp->printInitDeclaration(dst,ctx, declSpec);
    }
}

void Init_Declarator::printPy(std::ostream &dst, int depth) const{
    if(depth == 0){
        py_var_table.push_back(decl);
    }
    if(init != NULL){
        decl->printPy(dst,depth);
        dst << " = ";
        init->printPy(dst,depth);
    }
    else{
        decl->printPy(dst,depth);
        dst << " = 0";
    }
    dst << "\n";
}

void Init_Declarator::printInitDeclaration(std::ostream &dst, Context &ctx, const std::string &Type) const {
    std::string mips_type;

    if (Type.find("int") != std::string::npos){
        mips_type = ".word ";
    }
    else if(Type.find("double") != std::string::npos){
        mips_type = ".double ";
    }
    else if(Type.find("float") != std::string::npos){
        mips_type = ".float ";
    }
    else if(Type.find("char") != std::string::npos){
        mips_type = ".byte ";
    }
    else if(Type.find("short") != std::string::npos){
        mips_type = ".halfword ";
    }

    if(init != NULL){
        if(dynamic_cast<Array*> (decl)){
            if(ctx.getScope() == 0){
                //std::string var = makeName("var");
                std::string _ID = decl->getID();
                ctx.insertBindingGlobal(_ID, _ID, Type);
                dst << "\t.data\n\t.globl\n" << _ID << ": .word ";
                int tmp = decl->getSize();
                for(int i = 0; i < tmp; i++){
                    if(dynamic_cast<Integer_Constant*> (init->getElement(i))){
                        dst << init->getElement(i)->getSize();
                        if(i != tmp-1) dst << ", ";
                    }
                    else{
                        dst << "0";
                        if(i != tmp-1) dst << ", ";
                    }
                }
                dst <<"\n\t.text\n"; 
            }
            else{
                int rel_add = (1+ctx.getVariableCounter())*(-4);
                std::string _ID = decl->getID();
                ctx.insertBindingLocal(_ID, Type, rel_add);
                std::string reg = "$t0";
                for(int i = 0; i < decl->getSize(); i++){
                    ctx.increaseVariableCounter();
                    rel_add = ctx.getVariableCounter()*(-4);
                    init->getElement(i)->printMipsExpr(dst, reg, ctx);
                    dst << "sw $t0, " << rel_add << "($fp)" << "\n";
                    dst << "addiu $sp, $sp, -4\n";  
                }
            }
        }
        else if(dynamic_cast<Identifier*> (decl)){
            std::string _ID = decl->getID();
            if(ctx.getScope() == 0){
                //std::string var = makeName("var");
                ctx.insertBindingGlobal(_ID, _ID, Type);
                dst << "\t.data\n\t.globl\n" << _ID << ": " << mips_type;
                if(dynamic_cast<Integer_Constant*> (init)){
                    dst << init->getSize();
                }
                else{
                    dst << " 0";
                }
                dst << "\n\t.text\n";
            }
            else{
                ctx.increaseVariableCounter();
                int rel_add = ctx.getVariableCounter()*(-4);
                ctx.insertBindingLocal(_ID, Type, rel_add);
                std::string reg = "$t0";
                init->printMipsExpr(dst, reg, ctx);
                dst << "sw $t0, " << rel_add << "($fp)" << "\n";
                dst << "addiu $sp, $sp, -4\n";
            }
        }
        else{
            std::cerr << "\nError declaring var w/ initital value\n";
            exit(1);
        }
    }
    else{
        if(dynamic_cast<Array*> (decl)){
            if(ctx.getScope() == 0){
                std::string _ID = decl->getID();
                ctx.insertBindingGlobal(_ID, _ID, Type);
                dst << "\t.data\n" << _ID << ": .space "<< 4*decl->getSize() <<"\n\t.text\n";            
            }
            else{
                int rel_add = (1+ctx.getVariableCounter())*(-4);
                std::string _ID = decl->getID();
                ctx.insertBindingLocal(_ID, Type, rel_add);
                for(int i = 0; i < decl->getSize(); i++){
                    ctx.increaseVariableCounter();
                }
                dst << "addiu $sp, $sp, " << -4*decl->getSize()-1<< "\n";
            }
        }
        else if(dynamic_cast<Identifier*> (decl)){
            std::string _ID = decl->getID();
        
            if(ctx.getScope() == 0){
                ctx.insertBindingGlobal(_ID, _ID, Type);
                dst << "\t.data\n\t.globl\n" << _ID << ": " << mips_type << "0\n\t.text\n";
            }
            else{
                ctx.increaseVariableCounter();
                int rel_add = ctx.getVariableCounter()*(-4);
                ctx.insertBindingLocal(_ID, Type, rel_add);
                dst << "addu $t0, $zero, $zero\n";
                dst << "sw $t0, " << rel_add << "($fp)" << "\n";
                dst << "addiu $sp, $sp, -4\n";
            }
        }
        else{
            decl->printMips(dst,ctx);
        }
    }
}