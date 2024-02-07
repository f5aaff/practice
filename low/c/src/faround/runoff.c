#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define ARR_SIZE(x) (sizeof(x)/sizeof(x[0]))


struct Node
{
        void *data;
        struct Node *next;
};


void openBook(char *reader,char *title){
    char com[sizeof(char)*(strlen(reader)+strlen(title)+1)];
    sprintf(com,"%s %s",reader,title);
    system(com);
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


int longestlink(Node *node){
    int temp = 0;
    while(node !=NULL){
        int linklen = strlen((char *)node->data);
        if(linklen>temp)
            temp = linklen;
        node = node->next;
    }
    return temp;
}



struct book{
    char *path;
    char *title;
    int *id;
};

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


