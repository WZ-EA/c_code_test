#include <stdio.h>

int main(void){

    int currentHour, currentMinute;
    double tripTime;
    int tripHour, tripMinute;
    int extraHour, sumMinute, sumHour;
    int arrivalHour, arrivalMinute;

    printf("Enter current time: ");
    scanf("%d %d", &currentHour, &currentMinute);
    printf("Enter trip time: ");
    scanf("%lf", &tripTime);

    printf("\nCurrent time is %02d:%02d\n", currentHour,currentMinute);
    
    tripHour = (int)(tripTime / 1);
    tripMinute = (int)(60 * (tripTime - tripHour));

    sumMinute = currentMinute + tripMinute;

    if(sumMinute >= 60){

        arrivalMinute = sumMinute - 60;
        extraHour = 1;

    }else{

        arrivalMinute = sumMinute;
        extraHour = 0;
    }

    sumHour = currentHour + tripHour + extraHour;

    if(sumHour >= 24){

        arrivalHour = sumHour - 24;
        printf("Arrival Time is next day %02d:%02d\n", arrivalHour, arrivalMinute);

    }else{

        arrivalHour = sumHour;
        printf("Arrival Time is same day %02d:%02d\n", arrivalHour, arrivalMinute);
    }

    return 0;
    
}
