
DEF hello_world -> string () {
    PRINT "Hello World inside function";
}

DEF func -> int (a, b) {
    int sum = a + b;
    int diff = a - b;
    int prod = a * b;
    int quo = a / b;
    PRINT sum;
    PRINT diff;
    PRINT prod;
    PRINT quo;
    return sum
}

DEF main -> int () {
    int num1 = 5;
    int num2 = 10;
    char chr = 'h';
    string str = "Hello, World";
    int sum = num1 + num2;
    PRINT str;
}