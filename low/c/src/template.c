#include <stdio.h>

void arith(void){};
void arith1(void){};
void arith2(void){};
void arith3(void){};
void arith4(void){};



int main(void){
    int exe;
    printf("exercise no.:");
    scanf("%d",&exe);
    switch(exe){
        case 0:
            arith();
            break;
        case 1:
            arith1();
            break;

        case 2:
            arith2();
            break;

        case 3:
            arith3();
            break;

        case 4:
            arith4();
            break;


    }
}
