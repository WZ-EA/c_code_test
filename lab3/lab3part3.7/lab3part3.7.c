#include <stdio.h>
#include <math.h>

int main(void){

    int n;
    double a,b;
    double width;
    double xi;
    double area = 0.0;

    printf("Please enter the number of rectangles (n): ");
    scanf("%d", &n);

    printf("Please enter the interval of integration (a b): ");
    scanf("%lf %lf", &a, &b);

    width = (b - a) / n;

    for (int i = 0; i < n; ++i) {

        xi = a + width * (i + 0.5); 
        area += exp(-1 * xi * xi) * width;
    }

    printf("The integral of e^(-x^2) on [%.5lf, %.5lf] with n = %d is: %.5lf\n", a, b, n, area);
}
