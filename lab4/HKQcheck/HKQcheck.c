#include <stdio.h>
#include <math.h>

int main(void){

    int first_value;
    int total_number = 0;
    int inner_first_seven_count = 0;


    printf("Input an integer: ");
    scanf("%d", &first_value);
    
    if(first_value == 0){

        printf("You entered %d lucky number(s)!\n", total_number);
        return 0;

    }else{

        int inner_first_remainder;

        do{
            inner_first_remainder = first_value % 10;

            if(inner_first_remainder == 7){
                inner_first_seven_count += 1; 
            }

            first_value = (first_value - inner_first_remainder) / 10;

        }while(first_value != 0);

        if(inner_first_seven_count == 3){

            total_number += 1;

        }

        printf("You entered %d lucky number(s)!\n", total_number);
    }

    return 0;
}
