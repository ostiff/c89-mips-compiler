int b();

int a(){
    if(5>1){
        return b();
    }
    else{
        return 23;
    }
}

int b(){
    if(5<1){
        return 13;
    }
    else{
        int x = 12;
        return x;
    }
}