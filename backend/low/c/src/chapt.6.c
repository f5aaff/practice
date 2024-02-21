#include <stdio.h>
#include <stdlib.h>

//Chapter 6 practice following the C tutorial from beej.us


// this is a macro, essentially, a short hand defined at the top of compiling,
// this is used to define calculations ahead of time, to prevent duplicate code.
#define ArrSize(x) (sizeof(x)/sizeof((x)[0]))


void arr1(void)
{
    /*
      here, an array of floats is instantiated, in C, an array has to be intantiated with
      an explicit size, here a size of 4.
      the size is then retrieved using the aforementioned macro.
      this is then iterated over, and populated with random numbers.
      then iterated over again, and each position printed.
     */
    float f[4];
    for (int i = 0; i<4 ; i++){
        f[i] = rand();
    };
    printf("length of array: %ld\n",ArrSize(f));
    for(int i = 0; i<ArrSize(f);i++){
        printf("%f\n",f[i]);
    };
}

void arr2(void)
{
    /*
      arrays can be initialised with values, by using curly braces.
     */

    int a[5] = {1,2,3,4,5};
    for(int i=0;i<ArrSize(a);i++) printf("%d\n",a[i]);

}

void arr3(void)
{
    /*
     multidimensional arrays are much the same as in any other language, except, you can run over the end of the array,
     and encounter unexpected behaviour.
     */
    int a[2][5] = {
        {0,1,2,3,4},
        {5,6,7,8,9}
    };

    for(int row = 0 ;row < 2; row++){
        for(int col = 0; col < 5; col++) {
            printf("(%d,%d) = %d\n",row,col,a[row][col]);
        }
    }
}

void arr4(void)
{
    /*
      3x3 identity matrixes
     */

    int a[3][3] = {[0][0]= 1, [1][1] = 2, [2][2] = 3};
    for(int row = 0 ;row < 3; row++){
        for(int col = 0; col < 3; col++) {
            printf("(%d,%d) = %d\n",row,col,a[row][col]);
        }
    }

}

void multArray(int a[],int multiplier,int len)
{

    for(int i = 0; i < len; i++){
        printf("multiplied by %d: %d\n",multiplier,a[i] * multiplier);
    }
}

void multPointer(int *a, int multiplier,int len)
{
    for(int i = 0; i < len; i++){
        printf("multiplied by %d: %d\n",multiplier,a[i] * multiplier);
    }
}

void multFixedLen(int a[5],int multiplier,int len)
{
    for(int i = 0; i < len; i++){
        printf("multiplied by %d: %d\n",multiplier,a[i] * multiplier);
    }
}

void arr5(void)
{
    //chapter 6.6.2
    /*
     each of these functions performs the exact same task,
     however, they each take a different form as input. the compiler generally
     will not care what form the array comes in - as all it is is a pointer to the start of the array.
     with that said, the size of the array will be enforced with multidimensional arrays.

     */
    int x[5] = {1,2,3,4,5};
    int len = ArrSize(x);
    multArray(x,2,len);
    multPointer(x,5,len);
    multFixedLen(x,9,len);
}


void double_array(int *a, int len)
{
    for(int i = 0; i < len;i++ ){
        a[i] *=2;
    }
}

void arr6(void)
{
    //chapter 6.6.3
    /*
      despite the array being passed as a parameter, the pointer can still be accessed positionally as
      if it were an array. This is todo with the equivalence between arrays and pointers; which will be covered later.
      apparently.
     */
    int x[5] = {1,2,3,4,5};
    double_array(x, ArrSize(x));

    for(int i=0;i<ArrSize(x);i++)
    {
        printf("%d\n", x[i]);
    }
}

void print_2D_array(int a[2][3])
{
    for(int row=0; row < 2; row++) {
        for (int col = 0; col < 3; col++)
            printf("%d ", a[row][col]);
        printf("\n");
    }
}

void arr7(void)
{
    //chapter 6.6.4
    /*
     this function takes a 2D array as an input, C requires the final dimension to be declared in order to know how
     far in memory to skip for each increment of the first dimension; so it does not need the first dimension.
     so, this function could state:
        void print_2D_array(int a[][3])
                    or
        void print_2D_array(int (*a)[3])
    and function exactly the same without errors.
     */
    int x[2][3] = {
        {1,2,3},
        {4,5,6}
    };
    print_2D_array(x);
}
int main(void){

    int exno;
    printf("enter an exercise number:");
    scanf("%d",&exno);

    switch (exno) {
        case 1:
            arr1();
            break;
        case 2:
            arr2();
            break;
        case 3:
            arr3();
            break;
        case 4:
            arr4();
            break;
        case 5:
            arr5();
            break;
        case 6:
            arr6();
            break;
        case 7:
            arr7();
            break;
        default:
            printf("not an exercise");
    }
}


