int f(){
    int x;

    switch(10){
        case(1) : {
            int y = 6;
            x = 5;
            return y; }
        case(10) :
            x = 15;
        case(11) :
            x = x + 5;
            return x;
    }
}