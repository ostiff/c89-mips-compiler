int f();

int main(){

    if(f()==32){
        return 0;
    }
    
    return f();
}