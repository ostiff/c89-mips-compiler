int f();

int main(){
    if(f()==3){
        return 0;
    }
    return f();
}