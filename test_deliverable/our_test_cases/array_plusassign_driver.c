int f();

int main(){
    if(f()==14){
        return 0;
    }
    else{
        return f();
    }
}