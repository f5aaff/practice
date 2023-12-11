#include <stdio.h>
#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4


/* A linked list node */
struct Node
{
	// Any data type can be stored in this node
	void *data;

	struct Node *next;
};


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

void PrintContentstoFile(struct Node *node)
{
    FILE *fp;
    fp = fopen("fuckingBOOKS","wb");

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



void openContent(char *reader,char *title){
    char com[sizeof(char)*(strlen(reader)+strlen(title)+1)];
    sprintf(com,"%s %s",reader,title);
    system(com);
}



char *path = "bookies";
char *extensions[] = {"pdf"};
char *choices[] = {
    "choice 1",
    "choice 2",
    "choice 3",
    "choice 4",
    "choice 5",
    "choice 6",
    "choice 7",
    "choice 8",
    "choice 9",
    "choice 10",
    "Exit",
    (char *)NULL,
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

void getTitle(struct Node *node){
        char *data = (char *)node->data;
        char *title = apply_regex_to_string("[^\\/\\\\]*(.pdf)", data);
        printf("%s\n",title);
}

void getItemNumber(struct Node *node){
    int i = 0;
    while(node != NULL){
        i++;
        node = node->next;
    }
}
int main(){

    struct Node *docs = collectFiles(extensions[0]);

    ITEM **my_items;
    MENU *app_menu;
        WINDOW *app_win;
        int n_choices, i;
/*
 * initialise curses, the 'screen' of the application
 */
        initscr();
        start_color();
            cbreak();
            noecho();
        keypad(stdscr, TRUE);
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2,COLOR_CYAN,COLOR_BLACK);


/*
 * create the items based on the number of choices present, putting them in an array.
 */
        n_choices = ARRAY_SIZE(choices);
        ITEM** app_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i=0; i<n_choices;i++)
            app_items[i] = new_item(choices[i],choices[i]);

/*
 * create a menu, initialising it as taking item pointer pointers, and app items.
 */
        app_menu = new_menu((ITEM **)app_items);

        menu_opts_off(app_menu,0);

/*
 * create the window for the application
 */
        app_win = newwin(10, 70, 4, 4);
        keypad(app_win, TRUE);

        set_menu_win(app_menu,app_win);
        set_menu_sub(app_menu, derwin(app_win, 6,68,3,1));

        box(app_win, 0,0);

        attron(COLOR_PAIR(2));
        mvprintw(LINES -3,0,"Use Pgup & PgDown to Scroll");
        mvprintw(LINES -3,0,"Use Arrow Keys to Navigate(F1 to Exit)");
        attroff(COLOR_PAIR(2));
        refresh();

        post_menu(app_menu);
        wrefresh(app_win);

        int c = wgetch(app_win);
        while((c = wgetch(app_win))  != KEY_F(1)){
            switch(c){
                case KEY_DOWN:
                    menu_driver(app_menu, REQ_DOWN_ITEM);
                    break;
                case KEY_UP:
                    menu_driver(app_menu, REQ_UP_ITEM);
                    break;
                case KEY_LEFT:
                    menu_driver(app_menu, REQ_LEFT_ITEM);
                    break;

                case KEY_RIGHT:
                    menu_driver(app_menu, REQ_RIGHT_ITEM);
                    break;

                case KEY_NPAGE:
                    menu_driver(app_menu, REQ_SCR_DPAGE);
                    break;

                case KEY_PPAGE:
                    menu_driver(app_menu, REQ_SCR_UPAGE);
                    break;
            }
            wrefresh(app_win);
        }

        /*
         * free up the memory taken
         */
        unpost_menu(app_menu);
        free_menu(app_menu);
        for(i=0; i< n_choices; i++)
            free_item(app_items[i]);
    endwin();

}
