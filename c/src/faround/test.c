#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define ARR_SIZE(x) (sizeof(x)/sizeof(x[0]))


char *extension="pdf";
char *storePath = "bookies";


/* A linked list node */
struct Node
{
	// Any data type can be stored in this node
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
        result = (char *)malloc(len + 1);
        if (result == NULL) {
            printf("Error allocating memory for result\n");
            return NULL;
        }
        strncpy(result, string + match.rm_so, len);
        result[len] = '\0';
    } else if (reti == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        printf("Error applying regex\n");
        return NULL;
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

char *  getTitle(struct Node *node){
        char *data = (char *)node->data;
        char *title = apply_regex_to_string("[^\\/\\\\]*(.pdf)", data);
        return title;
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

struct Node* generateLibrary(struct Node *node){

    struct Node *libraryStart = NULL;
    while(node != NULL){
        char *path = (char *)node->data;
        char *title = getTitle(node);
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
        printf("%s\n",(char *)node->data);
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
    printf(array[1]);
    return *array;
}




int main(void){
    struct Node *pdfs = collectFiles("pdf");
    int listlen = linkedListLen(pdfs);

    char *temp = To_Array(pdfs, listlen);
    char *Path1 = &temp[0];
    //printf("%s",Path1);

}




