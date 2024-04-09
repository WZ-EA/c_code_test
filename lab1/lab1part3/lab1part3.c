#include <stdio.h>
#include <math.h>

int main(void){

    const double gravitationalConstant = 6.6726E-11;
    double kiloCircumference, Acceleration;
    double planetRadius, planetMass, escapeVelocity, radiusMeter,conventionMass;

    printf("Circumference (km) of planet? ");
    scanf("%lf", &kiloCircumference);

    printf("Acceleration due to gravity (m/s^2) on planet? ");
    scanf("%lf", &Acceleration);

    printf("\nCalculating the escape velocity...\n");

    planetRadius = kiloCircumference / (2 * M_PI);
    radiusMeter = planetRadius * 1000;
    planetMass = Acceleration * pow(radiusMeter, 2) / gravitationalConstant;
    conventionMass = planetMass / pow(10, 21);
    escapeVelocity = sqrt(2 * gravitationalConstant * planetMass / radiusMeter) / 1000;

    printf("Planet radius:  %.1lf km\n", planetRadius);
    printf("Planet mass:  %.1lf x 10^21 kg\n", conventionMass);
    printf("Escape velocity:  %.1lf km/s\n", escapeVelocity);

    return 0;

}
