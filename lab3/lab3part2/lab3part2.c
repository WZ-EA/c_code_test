#include <stdio.h>
#include <math.h>

int main(void){

    double d, h;
    const double g = 9.81;
    const double l = 2;
    const double v = 20;
    const double pi = 3.1415926535;

    do{
        printf("Please enter the horizontal distance from the wall between 3 and 30 m:\n");
        scanf("%lf", &d);
    }while(d < 3.0 || d > 30);

    do{
        printf("Please enter the target height between 3 and 6 m:\n");
        scanf("%lf", &h);
    }while(h < 3 || h > 6);

    double vx, vy;
    double t;
    double degree, radian;
    double y;
    double difference;

    for(degree = 0; degree <= 90; degree += 1.0){

        radian = degree * (pi / 180);
        vx = v * cos(radian);
        vy = v * sin(radian);
        t = d / vx;
        y = l + (vy * t) - (0.5 * g * pow(t,2));
        difference = fabs(h - y);

        if(difference <= 0.3){
            printf("The angle should be %.2lf\n", degree);
            break;
        }else{
            continue;
        }
    }

    return 0;

}
