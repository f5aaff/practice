#include <stdio.h>
#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
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


char *extensions[]={
    "pdf"
};
int main(){

    Node *pdfs = collectFiles("pdf");
    int len = linkedlistlen(pdfs)+1;
    char *choices[len];
    linkedtoarr(pdfs,choices);
    choices[len-1] = "Exit";
    ITEM **junk = (ITEM **)calloc(ARRAY_SIZE(choices) + 1, sizeof(ITEM *));
    for(int i=0 ;i<ARRAY_SIZE(choices);i++){
        if(i!=len-1){
        junk[i] = new_item(apply_regex_to_string(REGEX_STR,choices[i]),choices[i]);
        //printf("\n%s\n%s\n",choices[i],apply_regex_to_string(REGEX_STR,choices[i]));
        }else{
            junk[i] = new_item(choices[i],choices[i]);
        }
    }
    ITEM **my_items;
	int c;
	MENU *my_menu;
        int n_choices, i;
	ITEM *cur_item;

	/* Initialize curses */
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

	/* Initialize items */
        n_choices = ARRAY_SIZE(choices);

        my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(apply_regex_to_string(REGEX_STR,choices[i]),choices[i]);
	my_items[n_choices] = (ITEM *)NULL;
	item_opts_off(my_items[3], O_SELECTABLE);
	item_opts_off(my_items[6], O_SELECTABLE);

	/* Create menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Set fore ground and back ground of the menu */
	set_menu_fore(my_menu, COLOR_PAIR(1) | A_REVERSE);
	set_menu_back(my_menu, COLOR_PAIR(2));
	set_menu_grey(my_menu, COLOR_PAIR(3));

	/* Post the menu */
	mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
	mvprintw(LINES - 2, 0, "Up and Down arrow keys to naviage (F1 to Exit)");
	post_menu(my_menu);
	refresh();

	while((c = getch()) != KEY_F(1))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
				move(20, 0);
				clrtoeol();
                int id = item_index(current_item(my_menu));
                char *current = choices[id];
				mvprintw(20, 0, "Item selected is : %d: %s",
					    id,current);
                char *docview = "zathura";
                char opencomm[strlen(docview)+strlen(current)];
                sprintf(opencomm,"%s %s 2>&1 /dev/null",docview,current);
                system(opencomm);
				pos_menu_cursor(my_menu);
				break;
		}
	}
	unpost_menu(my_menu);
	for(i = 0; i < n_choices; ++i)
		free_item(my_items[i]);
	free_menu(my_menu);
	endwin();
}

