#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define ARR_SIZE(x) (sizeof(x)/sizeof(x[0]))

char *extension="pdf";
char *storePath = "bookies";
char *STORE_PATH = "/home/f5adff/.zath_library/files";

struct Node
{
        void *data;
        struct Node *next;
};

struct book{
    char *path;
    char *title;
    int *id;
};

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

/* Function to add a node at the beginning of Linked List.
This function expects a pointer to the data to be added
and size of the data type */
void push(struct Node** head_ref, void *new_data, size_t data_size)
{
        // Allocate memory for node
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data = malloc(data_size);
        new_node->next = (*head_ref);
        // Copy contents of new_data to newly allocated memory.
        // Assumption: char takes 1 byte.
        int i;
        for (i=0; i<data_size; i++)
                *(char *)(new_node->data + i) = *(char *)(new_data + i);
        // Change head pointer as new node is added at the beginning
        (*head_ref) = new_node;
}

void openBook(char *reader,char *title){
    char com[sizeof(char)*(strlen(reader)+strlen(title)+1)];
    sprintf(com,"%s %s",reader,title);
    system(com);
}

char *  gettitle(char *data){
        return apply_regex_to_string("[^\\/\\\\]*(.pdf)", data);
}

void PrintContentstoFile(struct Node *node,char *path)
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

 struct Node* collectTitles(char *extension){
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


int findLongestPath(){
    char *command = "find ~/ -type f -print| grep -i \"\\.pdf\"  | awk '{print length($0)}' | sort -n";
    FILE *cmd=popen(command,"r");
    char res[1000]={0x0};
    unsigned strsize = sizeof(char[10]);
    int i = 0;
    while(fgets(res, sizeof(res),cmd) != NULL){
        char j = *(char *)res;
        int k = j;

        if(k>i){
            i = k;
            printf("%d\n",i);
        }
    }
    return i;
}


struct Node* generateLibrary(struct Node *node){

    struct Node *libraryStart = NULL;
    while(node != NULL){
        char *path = (char *)node->data;
        char *title = gettitle(path);
        struct book book = {book.title = path, book.title = title};
        unsigned booksize = sizeof(book);
        push(&libraryStart,&book,booksize);
    }

    return libraryStart;
}


int linkedListLen(struct Node *node){
    int listlen;
    while (node!=NULL){
        listlen ++;
        node = node->next;
    };
    return listlen;
}

char *  To_Array(struct Node *head, int listlen) {
    struct Node *current = head;
    int i = 0;
    char *array[listlen];
    while (current != NULL) {
        array[i] = (char *)current->data;
        current = current->next;
        i++;

    }
    return *array;
}





int main(void){
    struct Node *pdfs = collectFiles("pdf");
    PrintContentstoFile(pdfs,STORE_PATH);
    char  arrayOfDocs[100][2][1000];
    FILE *fptr = NULL;
    int i = 0;
    fptr = fopen(STORE_PATH,"r");
    char line[1000];

    while(fgets(line,ARR_SIZE(line),fptr)!=NULL){
        char *path = line;
        char *title = apply_regex_to_string("[^\\/\\\\]*(.pdf)", path);
        if(title != NULL){
            strcpy(arrayOfDocs[i][0],path);
            strcpy(arrayOfDocs[i][1],title);
            i++;
        }
    }

 //   for(int j=0; j < ARR_SIZE(arrayOfDocs); j++){
 //       printf("%s: %ld",arrayOfDocs[j][0],strlen(arrayOfDocs[j][0]));
 //       //printf("%s",arrayOfDocs[j][1]);
 //   }
    printf("%d",findLongestPath());



}






