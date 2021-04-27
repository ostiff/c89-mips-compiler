int f(){
    int i = 0;
    int j = 0;
    int k = 0;

    for(i; i<10; i++){
        k++;
        for(j; j<10; j++){
            k++;
        }
    }
    return k;
}