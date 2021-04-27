#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iterator>
#include <iostream>

static int makeNameUnq=0;

static std::string makeName(std::string base){
    makeNameUnq += 1;
    return "_"+base+"_"+std::to_string(makeNameUnq);
}

struct varData{
    int scope; // scope of this variable so we know the scope it belongs to
    std::string type;
    int relative_to_FP;
};

struct varGlobal {
    std::string mips_var_name;
    std::string type;
};

class Context {
    private:
        std::map<std::string, varGlobal> global_bindings;
        std::multimap<std::string,varData> bindings;
        std::map<std::string, std::vector<std::string>> functionMap;
        int scope_counter; // count the number of scopes
        int variable_counter;
        int switch_counter;
        int case_counter;

    public:
        Context() : scope_counter(0), variable_counter(0), switch_counter(0), case_counter(0) {}
        
        void insertBindingGlobal(const std::string &_ID, const std::string &_mips_ID, const std::string _type);
        void insertBindingLocal(const std::string &_varID, const std::string &_type, int _relative_to_FP);

        std::string GlobalReturnID(const std::string &_ID);
        int LocalReturnAddress(const std::string &_varID);

        void insertFunction(std::string &_functName, std::vector<std::string> _params);
        int getArgNumber(std::string &_functName);

        void increaseScopeCounter();
        void decreaseScopeCounter();
        int getScope();

        void increaseVariableCounter();
        int getVariableCounter();
        void setVariableCounter(int value);

        void increaseSwitchCounter();
        int getSwitchCounter();

        void increaseCaseCounter();
        void resetCaseCounter();
        int getCaseCounter();

        bool checkBindings(const std::string &_varID); // check if binding exists in the map
        void clearBindings();

        int ArgIndex(std::string _ID, std::string _functName);

        std::string returnID(std::string &_var);
};

#endif

/*

GENERAL MIPS REGISTER ALLOCATION

|Register | Assembly name | Comment |
|r0       | $zero         | Always 0 |
|r1       | $at           | Reserved for assembler |
|r2-r3    | $v0-$v1       | Stores result |
|r4-r7    | $a0-$a3       | Stores arguments |
|r8-r15   | $t0-$t7       | Temporaries, not saved |
|r16-r23  | $s0-$s7       | Contents saved for later |
|r24-r25  | $t8-$t9       | More temporaries not saved |
|r26-r27  | $k0-$k1       | Reserved by OS |
|r28      | $gp           | Global pointer |
|r29      | $sp           | Stack pointer |
|r30      | $fp           | Frame pointer |
|r31      | $ra           | Return address |

...........................................................................

WHAT WE DO...

$v0       | return for functions and program
$a0-$a3   | function arguments
$t0       | return value for all statements (functions also return to this)
$t1       | temporary for binary expressions
$t2       | temporary for binary expressions
$t3       | temporary for binary expressions
$t5       | dedicated switch register
$t6       | dedicated switch register
$t7       | dedicated array register, used to store address during expressions
*/