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

    int n;
    bool con;

    srand(42);

    printf("Number of monte carlo iterations: ");
    scanf("%d", &n);

    for(int i = 1; i <= n; i += 1){
        double x = randDouble();
        double y = randDouble();

        con = inBounds(x,y);

        printf("Random x coordinate: %f\n", x);
        printf("Random y coordinate: %f\n", y);
        printf("%d\n", con);
        printf("\n");
    }
    return 0;
}
