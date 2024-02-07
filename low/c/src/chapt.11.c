#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define arrSize(a) (sizeof(a)/sizeof((a)[0]))
void arith(void){
/*
    C is aware that p is an int pointer, so it knows the sizeof an int.
    therefore, it knows to skip that many bytes to get to the next int.
    printing *p is the equivalent of printing *p+0, as you are effectively
    returning the value p is pointing to, with no offset.

 */


    int a[5] = {1,2,3,4,5};
    int *p = &a[0];

    printf("%d\n", *p);
    printf("%d\n", *(p+1));
};
void arith1(void){


    int a[5] = {1,2,3,4,5};
    int *p = &a[0];

    for (int i=0 ; i < arrSize(a) ; i++ ) {
        printf("%d, ", *(p+i));
    }
};
void arith2(void){
    /*
      here the pointer itself is moved one position further, again informed
      by the fact that it is an integer pointer, so the correct number of bytes
      can be skipped.
     */
    int a[] = {123,456,789,1000};

    int *p = &a[0];

    while(*p != 1000) {
        printf("p:%d\n",*p);
        p++;
    }
};

int getStrLen(char *s){
    char *p = s;

    while (*p != '\0')
        p++;
    return p-s;
}
void arith3(void){
    /*
      subtraction operations can be performed on pointers as well,
      here the length of the string is determined by subtracting the final
      position from the initial position of the pointer to find the difference,
      and therefore, the length of the string.
      --this can only be done between two pointers that point to the same array!--
     */
    printf("%d\n", getStrLen("this is a test string"));
};
void arith4(void){
    int a[] = {1,2,3,4,5,6,7,8,9,10};

    int *p = a;

    for(int i = 0; i < arrSize(a); i++)
        printf("%d",a[i]);                  //Array notation with a

    for(int i = 0; i < arrSize(a); i++)
        printf("%d",p[i]);                  //Array notation with p


    for(int i = 0; i < arrSize(a); i++)
        printf("%d",*(a+i));                //Pointer notation with a


    for(int i = 0; i < arrSize(a); i++)
        printf("%d",*(p+i));                //Pointer notation with p


    for(int i = 0; i < arrSize(a); i++)
        printf("%d",*(p++));                //Moving pointer p
};


void arith5(void){

    /*
      Since arrays are equivalent to pointers, any function that accepts a
      pointer as input, will also take an array. take the getStrLen function
      from above; it expects a char pointer as input.
      If it took an array, a pointer would work as well.
     */
    char s[] = "this be a string";
    char *t = "this also be a string";

    printf("%d\n",getStrLen(s));
    printf("%d\n",getStrLen(t));
}

struct goblin{
   int limb_count;
   char *name;
};
struct nilbog{};
void arith6(void){

    /*
     here, memcpy is used to copy the entirety of s into t,
     memcpy uses void pointers to agnostically copy from one pointer to another.
     that's why it takes a size as an argument. in the first instance, the totality
     of s is copied into t, using arrSize.
     in the latter, the entirety of a is copied into b, using the size of the array
     multiplied by the size of an integer, as integers take more than a single byte.

     */

    char s[] = "goblins!";
    char t[100];

    memcpy(t,s,arrSize(s));
    printf("%s\n", t);

    int a[] = {1,2,3};
    int b[arrSize(a)];

    memcpy(b,a, arrSize(a) * sizeof(int));

    printf("%d\n", b[1]);

    /*
     this even works for structs, although, using the '=' operator is better
     practice
     */
    struct goblin goblin;
    struct nilbog nilbog;

    memcpy(&goblin, &nilbog, sizeof(goblin));

}

void arith7(void){
    char a = 'X';

    void *p = &a;
    char *q = p;

  //printf("%c\n" *p) a void pointer cannot be dereferenced!
    printf("%c\n", *q);
}

void *cpyStuff(void *dest, void *src, int byte_count){
    //convert void*s to char*s
    char *s = src, *d = dest;

    while (byte_count--){
        *d++ = *s++;
    }

    //most of these return the dest, in case that's useful.

    return dest;
}

int compar(const void *elem1, const void *elem2){
    const struct goblin *goober = elem1;
    const struct goblin *gleeb = elem2;

    if (goober->limb_count > gleeb->limb_count){
        return 1;
    }
    if (gleeb->limb_count > goober->limb_count){
    return 0;
    }
};

void arith8(void){
    struct goblin goblins[] = {
        {.name="belch", .limb_count=4},
        {.name="groob", .limb_count=3},
        {.name="wert", .limb_count=6},
        {.name="wort", .limb_count=2},
        {.name="plote", .limb_count=3}
    };
    qsort(goblins,arrSize(goblins),sizeof(struct goblin),compar);
    for(int i = 0; i< arrSize(goblins); i++){
        printf("%d: %s\n", goblins[i].limb_count, goblins[i].name);
    }
 }
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
        case 5:
            arith5();
            break;
        case 6:
            arith6();
            break;
        case 7:
            arith7();
            break;
        case 8:
            arith8();
            break;
    }
}
