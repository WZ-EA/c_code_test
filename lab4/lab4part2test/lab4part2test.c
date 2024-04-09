#include <stdio.h>
#include <math.h>

int main(void) {

    int numZero;
    int k = 0;
    int i = 0;
    int j = 0;
    int num;

    printf("Input an integer: ");
    scanf("%d", &numZero);
    if (numZero == 0){return 0;}


    while(numZero > 0){

        int digitZero;

        digitZero = numZero % 10;
        if (digitZero == 7){
            k++;
        }
        numZero = (numZero - digitZero) / 10;
    }
    if (k == 3){
        j++;
    }

    while(1){

        printf("Input an integer (0 to stop): ");
        scanf("%d", &num);

        if (num == 0){break;}

        while(num > 0){

            int digit;

            digit = num % 10;
            if (digit == 7){
                i++;
            }
            num = (num - digit) / 10;
        }
        if (i == 3){
            j++;
        }
    }
    printf("You entered %d lucky number(s)!", j);
}