#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

double randDouble(void) {
    return (double)rand() / ((double)RAND_MAX);
}

bool inBounds(double x, double y) {
    bool condition;

    if((x*x + y*y) <= 1){
        condition = true;
    }else{
        condition = false;
    }
    return condition;
}

int main(void) {

    double n;
    double numberIn = 0.0;
    bool whetherIn;
    double pi;

    srand(42);

    printf("Number of monte carlo iterations: ");
    scanf("%lf", &n);

    for(int i = 1; i <= n; i += 1){
        double x = randDouble();
        double y = randDouble();

        whetherIn = inBounds(x,y);

        if(whetherIn == true){
            numberIn += 1;
        }

        pi = 4 * (numberIn / n);
    }

    printf("Pi: %.4lf\n", pi);

    return 0;
}
