#include <stdio.h>
#include <math.h>

int main(void){

    double lengthA, lengthB, degreeC, radianC;
    double degreeA, degreeB, radianA, radianB, lengthC, ratio;
    const double pi = 3.14159265;

    printf("Enter the length of side A: ");
    scanf("%lf", &lengthA);

    printf("Enter the length of side B: ");
    scanf("%lf", &lengthB);

    printf("Enter the measure of angle alpha in degrees: ");
    scanf("%lf", &degreeA);

    radianA = degreeA * (pi / 180);

    ratio = lengthA / sin(radianA);

    radianB = asin(lengthB / ratio);
    radianC = pi - radianB - radianA;

    degreeB = radianB * (180 / pi);
    degreeC = radianC * (180 / pi);

    lengthC = sin(radianC) * ratio;

    printf("Results:\n");
    printf("Side A: %.2lf\n", lengthA);
    printf("Side B: %.2lf\n", lengthB);
    printf("Side C: %.2lf\n", lengthC);
    printf("Angle Alpha: %.2lf degrees\n", degreeA);
    printf("Angle Beta: %.2lf degrees\n", degreeB);
    printf("Angle Gamma: %.2lf degrees\n", degreeC);

    return 0;

}
