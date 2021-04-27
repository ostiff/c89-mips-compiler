#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ast.hpp"
#include "context.hpp"

std::vector<ExpressionPtr> py_var_table; // Used for py global vars
int PyTab = 0; // used for python tabs

int main(int argc, char *argv[]){

    if(argc == 5){
        if(std::string(argv[3]) == "-o"){
            if(std::string(argv[1]) == "--translate"){
                std::ofstream output(argv[4]);
                //make ast with argv[2] as input file
                //print to output file
                const Expression *ast = parseAST(argv[2]);
                //make main first fn in python
                ast->printPy(output);

                output << "\n\nif __name__ == \"__main__\":\n";
                output << "\timport sys\n";
                output << "\tret=main()\n";
                output << "\tsys.exit(ret)\n";

            }
            else if(std::string(argv[1]) == "-S"){
                std::ofstream output(argv[4]);
                //make ast and output MIPS I code
                Context ctx;
                const Expression *ast = parseAST(argv[2]);
                ast->printMips(output,ctx);
            }
            else{
                std::cout << "Error : Invalid Flag :\t" << argv[1] << "\nUse:" << "\t-S : C-compiler\n\t--translate : C-translator" << std::endl;
            }
        }
        else{
            std::cout << "Error: Invalid Flag :\t" << argv[3] <<"\n-o must be used : bin/c_compiler [flag] [source-file.c] -o [dest-file.s]" << std::endl;
        }
    }
    else {
        std::cout << "Error: " << argc-1 << " out of 4 arguments provided" << std::endl;
    }

    return 0;
}
