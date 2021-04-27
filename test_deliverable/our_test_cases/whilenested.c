int f(){
    int i = 0;
    int j = 0;
    int k = 0;
    while(i < 10){
        i++;
        k++;
        while(j < 10){
            j++;
            k++;
        }
    }
    return k;
}



