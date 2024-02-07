#include <stdio.h>
#include <string.h>
#define ARRSIZE(x) ((sizeof(x)/sizeof((x)[0])))

//Covers chapter 7 of the beej.us C tutorial

void str(void){
//chapter 7.4

    //this is a pointer to a string literal, and is immutable.
    char *s = "Hello, World!";
    /*
     * s[0] = 'z'; -- this will cause a crash!
     */

    //this is defined as an array, and can therefore be modified positionally.
    char t[] = "Hello, Again!";

    /*
      strings can also be string formatted the same way arrays can, as they are essentially arrays
      of characters.
    */
    for(int i = 0;i<13; i++){
        printf("%c",s[i]);
    }
    t[0] = 'z';

    printf("\n%s\n",t);
}

void str1(void){
    char *s = "this is a string";
    printf("string is: %zu bytes long\n", strlen(s));
}

int getStrLen(char *s)
{
    int count = 0;
    while (s[count] != '\0')
    {
        count++;
    }
    return count;
}
void str2(void){
    /*
      C uses a special character to terminate strings, denoted by '/0'.
      it does not however, track the *length* of strings, so they have to be
      determined either as an array, or with strlen() from string.h.
     */

    //this is effectively "this is also a string\0" behind the scenes
    char s[] = "this is also a string";
    printf("the length of this string is %d\n",getStrLen(s));

    /*
     length can also be found the same way as with a typical array
     this will include the terminating character at the end, so the final size
     will be one greater than the actual string itself.
     */

    printf("the length determined by the macro is %ld\n",ARRSIZE(s)-1);
}

void str3(void)
{
    /*
      much like pointers in previous chapters, they point to the location of the value
      in memory, so by assigning a pointer to it, then editing the value via the pointer,
      we can modify the string in memory.
     */
    char s[] = "this is very much a string";
    char *t;
    t=s;
    printf("%s\n",s);
    t[0] = 'z';
    printf("%s\n",s);

    /*
     this can be achieved with the strcpy function from string.h more easily.
     */

    char e[50];
    printf("%ld\n",ARRSIZE(s));
    strcpy(e,s);

    printf("%s\n",e);

}


int main(void)
{
    int exer;
    printf("enter an exercise number:");
    scanf("%d",&exer);

    switch (exer) {
        default:
            printf("not an exercise");
            break;
        case 0:
            str();
            break;
        case 1:
            str1();
            break;
        case 2:
            str2();
            break;
        case 3:
            str3();
            break;

    }
}
