#include <stdio.h>
#include <stdlib.h>
#define arrlen(x) (sizeof x / sizeof x[0])

void mma(void){
    /*
     memory is manually allocated in C, with automatic, scoped parameters being
     refered to as in the 'stack' and manually or 'malloc'd' parameters being
     in the 'heap'. if you manually allocate memory, you have to free that memory,
     as that memory will persistently be reserved until freed.
     */

    /*
     to know how much memory to allocate, here we use sizeof to allocate one int's
     worth of memory to the int pointer p.
     */

    /*
     the below statements are equivalent, as p is an int, so it has the same size
     as an int.
    */

    int *p = malloc(sizeof(int));

    int *q = malloc(sizeof *p);
    *p =12;

    printf("%d\n", *p);
    //we then use free to free the memory allocated to p, to prevent a memory leak.
    free(p);
    free(q);
};
void mma1(void){
    /*
     some OSes don't return NULL if memmory cannot be allocated, but most do.
     In this case, error handling is needed to check for and handled memory
     running out.
    */
    int *x;
    if ((x = malloc(sizeof(int) * 10)) == NULL){
        printf("not enough space for 10 ints, get more mem poor boy");
        //do some error handling
    }
};
void mma2(void){
    /*
     malloc can also be used to intantiate an array by multiplying the size of
     an element by the number of elements needed.
     */
    int *p = malloc(sizeof(int) * 10);
    for (int i = 0; i< 10; i++){
        p[i] = i * 5;
    }
    for(int i = 0; i<10;i++){
        printf("%d ",p[i]);
    }
    free(p);
};
void mma3(void){};
void mma4(void){};



int main(void){
    int exe;
    printf("exercise no.:");
    scanf("%d",&exe);
    switch(exe){
        case 0:
            mma();
            break;
        case 1:
            mma1();
            break;

        case 2:
            mma2();
            break;

        case 3:
            mma3();
            break;

        case 4:
            mma4();
            break;


    }
}
