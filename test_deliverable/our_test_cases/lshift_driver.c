int f();

int main(){

    if(f()==10){
        return 0;
    }
    
    return f();
}