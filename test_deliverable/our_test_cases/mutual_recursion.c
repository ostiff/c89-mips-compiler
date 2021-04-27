int is_odd(int n);

int is_even(int n){
    if (n==0)
        return 112;
    else
        return is_odd(n-1);
}

int is_odd(int n){
    if (n==0)
        return 0;
    else
        return is_even(n-1);
}