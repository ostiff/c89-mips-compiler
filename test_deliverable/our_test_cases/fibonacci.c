int fib(int a){
    return a < 2 ? a : fib(a-1)+fib(a-2);
}