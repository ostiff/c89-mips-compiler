#include "ast_list.hpp"

void List::insert(const ExpressionPtr _expression){ //added const!!!
    element_list.push_back(_expression);
}

void List::printPy(std::ostream &dst, int depth, int listType) const{ //virtual??
    if((element_list.size() > 0) && (listType == 0)){
        for(unsigned i = 0; i < element_list.size()-1; i++){
            element_list[i]->printPy(dst,depth);
            dst << ", ";
        }
        element_list[element_list.size()-1]->printPy(dst,depth);
    }
    else if((element_list.size() > 0) && (listType == 1)){
        for(unsigned i = 0; i < element_list.size(); i++){
            for(int j = 0; j < PyTab; j++){
                dst << "\t";
            }
            element_list[i]->printPy(dst,depth);
            dst << "\n";
        }
    }
    else if((element_list.size() > 0) && (listType == 2)){
        for(unsigned i = 0; i < element_list.size(); i++){
            element_list[i]->printPy(dst,depth);
            //if(i!=0){
                for(int j = 0; j < PyTab; j++){
                    dst << "\t";
                }
            //}
        }

        //element_list[element_list.size()-1]->printPy(dst,depth);
    }
    else{
        //error
    }
}

ExpressionPtr List::getElement(int i){
    return element_list[i];
}

int List::getSize(){
    return element_list.size();
}