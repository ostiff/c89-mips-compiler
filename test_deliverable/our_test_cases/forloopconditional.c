
int f(){
    int i = 0;
    int x = 0;
    int k;

    for(i; i < 50;){
        x++;

        if(x%2 == 0)
            i++;
        else
            i+=2;

        k = x + i;
    }
    return k;
}