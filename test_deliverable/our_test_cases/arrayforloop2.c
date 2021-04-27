
int f(){
    int arr[10] = {0,0,0,0,0,0,0,0,0,0};
    int i = 0;
    int sum = 0;

    for(i; i < 10; i++){
        arr[i] = i;
        sum = sum + arr[i];
    }

    return sum;    
}