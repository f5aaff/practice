#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define ARR_SIZE(x) (sizeof(x)/sizeof(x[0]))
#define REGEX_STR ("[^\\/\\\\]*(.pdf)")
char *extension="pdf";
char *STORE_PATH = "/home/f5adff/.zath_library/files";

typedef struct Node
{
        void *data;
        struct Node *next;
}Node;
char *apply_regex_to_string(char *regex_str, char *string) {
    regex_t regex;
    int reti;
    char *result = NULL;
    reti = regcomp(&regex, regex_str, REG_EXTENDED);
    if (reti) {
        printf("Error compiling regex\n");
        return NULL;
    }
    regmatch_t match;
    reti = regexec(&regex, string, 1, &match, 0);
    if (!reti) {
        int len = match.rm_eo - match.rm_so;
        result = (char *)malloc(len + 2);
        if(result == NULL){
            printf("uhoh");
        }
        memset(result,0,(len+2)*sizeof(char));

        strncpy(result, string + match.rm_so, len);
        //printf("\n");
    }
    regfree(&regex);
    return result;
}

void push(Node** head_ref, void *new_data, size_t data_size)
{
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data = malloc(data_size);
        new_node->next = (*head_ref);
        // Assumption: char takes 1 byte.
        int i;
        for (i=0; i<data_size; i++)
                *(char *)(new_node->data + i) = *(char *)(new_data + i);
        (*head_ref) = new_node;
}

char *  gettitle(char *data){
        return apply_regex_to_string(REGEX_STR, data);
}

void PrintContentstoFile(Node *node,char *path)
{
    FILE *fp;
    fp = fopen(path,"wb");
    while(node != NULL){
        char *data = (char *)node->data;
        char *seperator = "\n";
        char op[sizeof(char)*(strlen(data)+strlen(seperator))];
        sprintf(op,"%s%s",data,seperator);
        fwrite(op, sizeof(char)*strlen(op),1,fp);
        node = node->next;
    }
    fclose(fp);
}


struct Node* ReadContentsFromFile(char *path){

    FILE *fp;
    fp = fopen(path,"r");
    struct Node *start = NULL;
    char junk[1000];
    while(fscanf(fp,"%s\n",junk)!=EOF){
        push(&start,junk,(sizeof(char)*strlen(junk)));
    }
    fclose(fp);

    return start;
}

 struct Node* collectFiles(char *extension){
    char *func = "find";
    char *target = "~/";
    int comlen = strlen(func)+strlen(target)+strlen(extension);
    char command[comlen];
    sprintf(command,"%s %s | grep -i \"\\.%s\"",func,target,extension);
    FILE *cmd=popen(command,"r");
    char res[1000]={0x0};
    unsigned strsize = sizeof(char[1000]);
    struct Node *start = NULL;
    while (fgets(res, sizeof(res), cmd) !=NULL){
        push(&start,res,strsize);
    }
    pclose(cmd);
    return start;
}

int linkedlistlen(Node *node){
    int i = 0;
    while(node !=NULL){
        i++;
        node = node->next;
    }
    return i;
}

void linkedtoarr(Node *node,char* arr[]){

    int i=0;
    while(node !=NULL){
        char *path = (char *)node->data;
        arr[i] = path;
        node = node->next;
        i++;
    }
}

int main(void){
    struct Node *pdfs = collectFiles("pdf");
    int len = linkedlistlen(pdfs);
    char *patharr[len];
    linkedtoarr(pdfs,patharr);
    for(int i=0; i<ARR_SIZE(patharr);i++){
       printf("%s",patharr[i]);
    }



}






