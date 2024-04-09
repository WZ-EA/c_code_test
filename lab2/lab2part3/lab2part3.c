#include <stdio.h>
#include <math.h>

int main(void) {

    const double k = 8.9875E9;
    char inputUnit1, inputC1, inputUnit2, inputC2;
    double inputValue1, inputValue2, distance;

    printf("Enter the value of the two charges separated by a space: ");
    scanf("%lf%c%c %lf%c%c", &inputValue1, &inputUnit1, &inputC1, &inputValue2, &inputUnit2, &inputC2);
    printf("Enter distance between charges in metres: ");
    scanf("%lf", &distance);

    double coulomb1, coulomb2;

    if(inputUnit1 == 'n'){
        if(inputUnit2 == 'n'){
            coulomb1 = inputValue1 * 1E-9;
            coulomb2 = inputValue2 * 1E-9;
        }else{
            coulomb1 = inputValue1 * 1E-9;
            coulomb2 = inputValue2 * 1E-6;
        }
    }else{
        if(inputUnit2 == 'n'){
            coulomb1 = inputValue1 * 1E-6;
            coulomb2 = inputValue2 * 1E-9;
        }else{
            coulomb1 = inputValue1 * 1E-6;
            coulomb2 = inputValue2 * 1E-6;
        }
    }

    double force, finalValue;
    force = k * fabs(coulomb1 * coulomb2) / pow(distance, 2);

    if(force < 1E-6){
        finalValue = force / 1E-9;
        printf("The force between charges is %.2lfnN (less than 1uN)\n", finalValue);
    }else if(force < 1E-3){
        finalValue = force / 1E-6;
        printf("The force between charges is %.2lfuN (less than 1mN)\n", finalValue);
    }else if(force < 1.00){
        finalValue = force / 1E-3;
        printf("The force between charges is %.2lfmN (less than 1N)\n", finalValue);
    }else{
        finalValue = force;
        printf("The force between charges is %.2lfN (1N or greater)\n", finalValue);
    }
    
    return 0;
}
