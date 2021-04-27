#include "context.hpp"

void Context::insertBindingGlobal(const std::string &_ID, const std::string &_mips_ID, const std::string _type){
    varGlobal var;
    var.type = _type;
    var.mips_var_name = _mips_ID;
    global_bindings.insert(std::make_pair(_ID, var));
}

void Context::insertBindingLocal(const std::string &_varID, const std::string &_type, int _relative_to_FP){
    varData var; // new variable
    var.type = _type;
    var.scope = scope_counter;
    var.relative_to_FP = _relative_to_FP;
    bindings.insert(std::make_pair(_varID, var));
    /*
    //DEBUG
    std::cerr << "\n\n\tScope: " <<scope_counter << "\n";
    for(std::multimap<std::string, varData>::iterator it = bindings.begin(); it != bindings.end();it++){
        std::cerr << "\t" <<  (it->first) << "\t" << it->second.scope<<"\t" << it->second.type<<"\t" << it->second.relative_to_FP << "\n";
    }
    */
}

void Context::insertFunction(std::string &_functName, std::vector<std::string> _params){
    functionMap.insert(std::make_pair(_functName, _params));
}

std::string Context::GlobalReturnID(const std::string &_ID){
    for(std::map<std::string, varGlobal>::iterator it = global_bindings.begin(); it != global_bindings.end(); it++){
        if(((it->first) == _ID) ){
            return it->second.mips_var_name;
        }
    }
    return _ID;
}

int Context::LocalReturnAddress(const std::string &_varID){
    int relative_address = 0;
    int max_scope = 0;
    for(std::multimap<std::string, varData>::iterator it = bindings.begin(); it != bindings.end();it++){
        if(((it->first) == _varID) && (it->second.scope >= max_scope)){
            max_scope = it->second.scope;
            relative_address = it->second.relative_to_FP;
        }
    }
    return relative_address;
}

bool Context::checkBindings(const std::string &_varID){
    for(std::multimap<std::string, varData>::iterator it = bindings.begin(); it != bindings.end();it++){
        if(it->first == _varID){
            //std::cerr << _varID << " already declared\t";
            return true;
        }
    }
    return false;
}

int Context::ArgIndex(std::string _ID, std::string _functName){
    std::vector<std::string> tmp;
    for(std::map<std::string, std::vector<std::string>>::iterator it = functionMap.begin(); it != functionMap.end(); it++){
        if((it->first) == _functName){
            tmp = it->second;
        }
    }
    for(unsigned int i = 0; i < tmp.size(); i++){
        if(tmp[i] == _ID){
            return i;
        }
    }
    return -1;
}

int Context::getArgNumber(std::string &_functName){
    if(!(functionMap.find(_functName)->second).empty()){
        return (functionMap.find(_functName)->second).size();
    }
    return 0;
}

void Context::clearBindings(){
    for(std::multimap<std::string, varData>::iterator it = bindings.begin(); it != bindings.end();){
        if((it->second.scope) == scope_counter){
            it = bindings.erase(it);
        }
        else{
            it++;
        }
    }
    if(scope_counter == 1){
        variable_counter = 0;
    }
}

void Context::increaseScopeCounter(){
    scope_counter ++;
}

void Context::decreaseScopeCounter(){
    scope_counter --;
}

int Context::getScope(){
    return scope_counter;
}

void Context::increaseVariableCounter(){
    variable_counter ++;
}
        
int Context::getVariableCounter(){
    return variable_counter;
}

void Context::setVariableCounter(int value){
    variable_counter = value;
}

std::string Context::returnID(std::string &_var){
    int rel_add = LocalReturnAddress(_var);
    if(rel_add == 0){
        return GlobalReturnID(_var);
    }
    std::string relative = std::to_string(rel_add)+"($fp)";
    return relative;
}

void Context::increaseSwitchCounter(){
    switch_counter ++;
}

int Context::getSwitchCounter(){
    return switch_counter;
}

void Context::increaseCaseCounter(){
    case_counter ++;
}

int Context::getCaseCounter(){
    return case_counter;
}

void Context::resetCaseCounter(){
    case_counter = 0;
}