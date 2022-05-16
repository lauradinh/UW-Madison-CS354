
// for each of the following functions 
// correct the prototype
// write function body
// replace return with the correct return statement
//
// you may write as many helper functions here as you wish

int algorithm_1() {
    int x = 8000;
    int y = 63;
    return x+y;  
}

int algorithm_2(int p1, int p2) {
    int sol = 0;
    if(p1 >= p2) {
        sol = p1/p2;
    }
    else {
        sol = 3 * p1 + p2;
    }
    return sol;
}

int algorithm_3(int p3, int p4) {
    int sol = 0;
    while(p4 > 0) {
        sol += p3;
        p4--;
    }
    return sol;
}

void algorithm_4(int p5, int *p) {
    *p = 3 * p5;
}



