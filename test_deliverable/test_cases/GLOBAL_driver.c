extern int global_variable;

int f();

int main(){
    f();
    if(global_variable==5){
        return 0;
    }
    return 1;
}