#include <stdio.h>

#define arraylen(arr) ((sizeof arr / sizeof arr[0]))

struct whale{
    char *name;
    float length;
    int mass;
};

typedef struct node {
    struct whale;
    struct node * next;
} node_t;
void fio(void){
    /*
      in any typical POSIX shell, you can direct the standard out, and standard
      error to seperate locations:
        ./foo > output 2> errors
        the above, will send 2, the standard error, to a file called errors;
        whilst sending the former, the standard out, to output.
        the below fprint statement writes the given string to standard output
        to specify what is written in such an operation.
     */
    printf("this is a string");
    fprintf(stdout,"this is a string to file\n");

}



void fio1(void){
    FILE *fp;
    int c;

    fp = fopen("test","r");
    while ((c = fgetc(fp)) !=EOF)
        printf("%c",c);
    printf("\n");
    fclose(fp);
}




void fio2(void){
    FILE *fp;
    fp = fopen("test","r" );
    char s[1024];
    int line = 0;
    while(fgets(s,sizeof s,fp)!= NULL)
        printf("%d:%s\n",line++,s);
    fclose(fp);

}
void fio3(void){
    FILE *fp;
    fp = fopen("test","a" );
    fputs("this is a test string\n",fp);
    fclose(fp);

    fio2();


}
void fio4(void){
    struct whale whale1 = {.name = "lard",.length = 99.999, .mass = 1000};
    struct whale whale2 = {.name = "butter",.length = 99.999, .mass = 1000};
    struct whale whale3 = {.name = "marg'",.length = 99.999, .mass = 1000};
    struct whale whales[3] = {whale1,whale2,whale3};

    FILE *fp;

    fp = fopen("whales","a");

    for(int i = 0; i<arraylen(whales); i++){
        struct whale whale = whales[i];
        fprintf(fp,"name: %s\tlength: %f\tmass: %d\n",whale.name,whale.length,whale.mass);
    }
    fclose(fp);
    struct whale junkwhale = {};
    fp = fopen("whales","r");
    while(fscanf(fp, "name: %s\tlength: %f\tmass: %d\n", junkwhale.name,junkwhale.length,junkwhale.mass)!=EOF)
        printf("%s %f %d",junkwhale.name,junkwhale.length,junkwhale.mass);

}


int main(void){
    int exe;
    printf("enter exercise no.:");
    scanf("%d",&exe);

    switch(exe) {
        case 0:
            fio();
            break;
        case 1:
            fio1();
            break;
        case 2:
            fio2();
            break;
        case 3:
            fio3();
            break;
        case 4:
            fio4();
            break;
    }
}





