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
    int len = linkedlistlen(pdfs)+2;
    char *choices[len];
    linkedtoarr(pdfs,choices);
    choices[len-2] = "Exit";
    choices[len-1] = (char *)NULL;

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
    for(i=0; i<n_choices;i++){
        app_items[i] = new_item(choices[i],choices[i]);
        printf("%s",choices[i]);
/*  }
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
