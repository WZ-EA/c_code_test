#include <stdio.h>
#include <math.h>

int main(void){

    double n;
    double a,b;
    double width;
    double area;
    double x1;

    while(1){

        printf("\nPlease enter the number of rectangles (n): ");
        scanf("%lf", &n);

        printf("Please enter the interval of integration (a b): ");
        scanf("%lf %lf", &a, &b);

        if(a >= b){

            printf("Invalid interval\n");

        }else{

            width = (b - a) / n;
            x1 = a + 0.5 * (width);
            area = exp(-1 * x1 * x1);

            for(int iMinusOne = 1; iMinusOne <= (n + 1); iMinusOne += 1){

                area += exp(-1 * (x1 + n * iMinusOne) * (x1 + n * iMinusOne)) * width;
            }

            int intn = (int)n;
            printf("The integral of e^-x^2 on [%.5lf, %.5lf] with n = %d is: %lf\n", a, b, intn, area);
        }
    }
    return 0;
}
