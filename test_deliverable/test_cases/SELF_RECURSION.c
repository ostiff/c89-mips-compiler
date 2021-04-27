int f(int a){
    if(a == 0){
        return 1;
    }
    return f(a-1)*a;
}