int x;

int f(){
    x = 5;
    {
        int xx = 10;
        x = x + xx;
    }

    return x;
}