int f(){
    int i = 0;
    while(i<10){
        i++;
        if(i==5){
            continue;
        }
    }
    return i;
}