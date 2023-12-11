#include <stdio.h>
#include <math.h>
//covers Chapter five of bee.jus C tutorial

void mem(void){
    //chapter 5.1
    int i = 10;
//print the value, and address of the Int i
    printf("value: %d\n",i);
    printf("address: %p\n",(void *)&i);

}

void mem1(void){
    //chapter 5.2

    //int i, assign a value with the type of integer.
    int i = 10;

    //instantiate a pointer with type int, meaning it is a pointer, that'll point
    //to an int
    int *p;

    /*
      assign p to the *address* of i,
      meaning that it now points to i's location in the buffer
    */
    p = &i;
    printf("pointer: %d\n address: %p\n ",*p,(void *)&i);
}

void mem2(void){
//chapter 5.3
    int i;
    int *p;
    p = &i;

    /*
     the pointer has been set to point to the location of i in memory,
     the pointer is then dereferenced, and assigned a new value.
     this changes the value of i.
    */
    i = 10;
    printf("int dereference value: %d\n",i);
    printf("pointer before dereference: %d\n",*p);
    *p = 20;
    printf("int after dereference: %d\n",i);
    printf("pointer after dereference: %d\n",*p);
}

void increment(int *p)
{
    *p = *p + 1;
}

void mem3(void){
    //chapter 5.4

    /*
     here we assign a value to an integer variable,
     then assign a pointer to it's memory address
     we then use a function to increment the int pointer by one.
     this in turn increments the integer variable, as the pointer is directed to it's
     location in memory.
     this is achieved without without passing the integer itself, as the 'directions'
     to the variable, if you will,
     are passed instead.
    */
    int i = 10;
    /*
     the '*' acts as an address of operator, creating a memory address *of* an integer.
     this is handed to the increment function, and can be used to essentially use a pointer
     as a variable
    */
    int *j = &i;
    printf("value stored in pointer before dereference and increment: %d\n", *j);

    increment(j);
    printf("value stored in integer: %d\n", i);

}

void mem4(void)
{
    //chapter 5.5
    /*
     Both of these declarations are fine, however, if I were to write:
        int *p = NULL;
    this would cause a crash, as the pointer isn't actually pointing to a value
    */
    int *p;
    p = NULL;
}

void mem5(void)
{
    /*


    int a, *p;

    int *p, q;

    int* p,q;

    int *a, b, c d*, e, *f, g, h, *i;

    */
}


int main(void){

    int entry;
    scanf("%d", &entry);

    switch (entry) {
        case 0:
            mem();
            break;
        case 1:
            mem1();
            break;
        case 2:
            mem2();
            break;
        case 3:
            mem3();
            break;
        default:
            printf("that isn't an exercise!\n");
            break;
    }
}
