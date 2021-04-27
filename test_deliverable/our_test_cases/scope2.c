
int f(){
    int x = 5;
    {
        int xx = 10;
        x = x + xx;
    }
    {
        int yy = 10;
        x = x + yy;
    }

    return x;
}