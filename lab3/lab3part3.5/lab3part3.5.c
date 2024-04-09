#include <stdio.h>
#include <math.h>

double f(double x) {
    return exp(-1 * x * x); // e^(-x^2)
}

int main(void) {
    int n;
    double a, b, width, midpoint, area = 0.0;

    // Prompt the user for the number of rectangles
    printf("Please enter the number of rectangles (n): ");
    scanf("%d", &n);
    if (n < 1) {
        printf("Exiting.\n");
        return 0; // Exit if n is less than 1
    }

    // Prompt the user for the interval of integration
    printf("Please enter the interval of integration (a b): ");
    scanf("%lf %lf", &a, &b);
    
    // Check if the interval is valid
    if (a >= b) {
        printf("Invalid interval!\n");
        return 0; // Exit if the interval is not valid
    }

    width = (b - a) / n; // Calculate the width of each rectangle

    // Calculate the area using the rectangle method
    for (int i = 0; i < n; ++i) {
        midpoint = a + width * (i + 0.5); // Calculate the midpoint of each rectangle
        area += f(midpoint) * width; // Sum up the areas of each rectangle
    }

    // Output the result
    printf("The integral of e^(-x^2) on [%.5lf, %.5lf] with n = %d is: %.5lf\n", a, b, n, area);

    return 0;
}
