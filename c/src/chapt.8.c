#include <stdio.h>

#define ARRSIZE(x) (sizeof(x)/sizeof((x)[0]))

struct car {
    char *name;
    float price;
    int speed;
};

void set_price(struct car *c, float new_price)
{
    /*
     the struct has to be dereferenced in order to get rid of the pointer and get to the struct
     itself, this results in the struct car that that this points to, that the . operator can be
     used on.
     */
    (*c).price = new_price;

    /*
     the above is an ugly way of doing this though, and luckily C has some syntactic flair
     to get around this otherwise icky syntax.
     */
    c->price = new_price;

}

void struc(void)
{
    struct car eee = {.speed=100, .name="jalopy"};

    set_price(&eee, 1.00);
    printf("%f is the new price\n",eee.price);
}

void struc1(void){
    /*
      structs can be copied directly, this is not a deep copy, and copies all fields
      as is; including pointers to values
     */
    struct car a = {.name="junker", .speed=10, .price = 5.00};
    struct car b = a;

    printf("%s\n%s\n",a.name,b.name);
}
void struc2(void){
    /*
     the safest way to compare two structs, is by comparing each field individually.
     memcmp() won't necessarily work, as it does not account for padding bytes,
     that said, if memset() is used to clear the struct to zero; it might work. but this
     can result in weird elements that won't compare as intended.
     */
    struct car a = {.name="junker", .speed=10, .price = 5.00};
    struct car b = {.price= 1.00, .speed=100, .name="jalopy"};


}
void struc3(void){}
void struc4(void){}


int main(void)
{
    int exe;
    printf("enter an exercise number:");
    scanf("%d",&exe);

    switch(exe) {
        default:
            printf("not an exercise");
            break;
        case 0:
            struc();
            break;
        case 1:
            struc1();
            break;
        case 2:
            struc2();
            break;
        case 3:
            struc3();
            break;
    }
}
