#include <stdio.h>
#include <math.h>

int main(void) {

    int k = 0;
    int i = 0;
    int j = 0;
    int numZero;

    printf("Input an integer: ");
    scanf("%d", &numZero);

    if (numZero == 0){
        
        printf("You entered %d lucky number(s)!", j);
        return 0;

    }else{

        int digitZero;
        int innerNZ = numZero;

        while(innerNZ != 0){

            digitZero = innerNZ % 10;

            if (digitZero == 7){
            k++;
            }
            
            innerNZ = (innerNZ - digitZero) / 10;

            if (k == 3){
            j += 1;
        }
    }
    }
    
    bool flag = true;

    do{

        printf("Input an integer (0 to stop): ");
        scanf("%d", &num);

        if (num == 0){
            flag = false;
        }else{

            int num;
            int digit;

            digit = num % 10;
            if (digit == 7){
                i++;
            }
            num = (num - digit) / 10;

            if (i == 3){
            j++;
            }
        }
        
    }while(flag);

    printf("You entered %d lucky number(s)!", j);
}