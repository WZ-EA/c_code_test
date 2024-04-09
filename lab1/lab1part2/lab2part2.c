#include <stdio.h>

int main(void){

    const double standardCelcius = 22;
    const double standardFahrenheit = standardCelcius * 9 / 5 + 32;
    double imputFahrenheit, outputCelsius, fahrenheitDifference;

    printf("Enter the thermostat temperature: ");
    scanf("%lf", &imputFahrenheit);

    outputCelsius = (imputFahrenheit - 32) * 5/9;
    printf("The temperature in Celsius is: %.1lf\n\n", outputCelsius);

    fahrenheitDifference = imputFahrenheit - standardFahrenheit;
    printf("You are %.1lf degrees Fahrenheit away from a nice 22 degrees Celsius.\n", fahrenheitDifference);

    return 0;

}
