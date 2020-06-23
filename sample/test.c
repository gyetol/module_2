#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define ESCAPE 27
#define ENTER 10
char *file_item[] = {"","new", "open", "save", "save as"};
char *help_item[] = {"", "help", "about"};

WINDOW **file_menu_list(int start_col)
{
    int i;
    WINDOW **items;

    items=(WINDOW **)malloc(5 * sizeof(WINDOW *)); 

    items[0]=newwin(6,19,1,start_col);
    wbkgd(items[0], COLOR_PAIR(2));
    box(items[0],ACS_VLINE, ACS_HLINE);

    items[1]=subwin(items[0], 1, 17, 2, start_col+1);
    items[2]=subwin(items[0], 1, 17, 3, start_col+1);
    items[3]=subwin(items[0], 1, 17, 4, start_col+1);
    items[4]=subwin(items[0], 1, 17, 5, start_col+1);
    for (i =1; i < 5; i++)
        wprintw(items[i], "%s",file_item[i]);
    wbkgd(items[1], COLOR_PAIR(1));
    wrefresh(items[0]);
    return items;
}

void about_window()
{
    WINDOW *about;
    about = newwin(6, 40, 5, 10);
    box(about, ACS_VLINE, ACS_HLINE);
    wmove(about, 1, 2);
    wprintw(about, "Ncurses Test Verson 0.1"); 
    wmove(about, 2, 2);
    wprintw(about, "Made : yundream"); 
    wmove(about, 3, 2);
    wprintw(about, "Date : 2001.5.2"); 
    wmove(about, 4, 2);
    wprintw(about, "Press any key.. "); 
    wbkgd(about, COLOR_PAIR(3));
    refresh();
    wgetch(about);
    delwin(about);
}

int check_quit()
{
    WINDOW *check;
    int key;
    check = newwin(3, 40, 5, 10);
    wmove(check, 1, 2);
    wprintw(check, "Exit program (y/n) ? "); 
    wbkgd(check, COLOR_PAIR(2));
    box(check, ACS_VLINE, ACS_HLINE);
    refresh();
    key = wgetch(check);
    delwin(check);
    if (key == 'y')
        return 1;
    else 
        return 0;
}

WINDOW **help_menu_list(int start_col)
{
    int i;
    WINDOW **items;

    items=(WINDOW **)malloc(3 * sizeof(WINDOW *));

    items[0]=newwin(4,19,1,start_col);
    wbkgd(items[0], COLOR_PAIR(2));
    box(items[0],ACS_VLINE, ACS_HLINE);

    items[1]=subwin(items[0], 1, 17, 2, start_col+1);
    items[2]=subwin(items[0], 1, 17, 3, start_col+1);
    for (i = 1; i < 3; i++)
        wprintw(items[i], "%s", help_item[i]);
    wbkgd(items[1], COLOR_PAIR(1));
    wrefresh(items[0]);
    return items;
}

void delete_menu(WINDOW **items, int count)
{
    int i;
    for (i = 0; i < count; i++)
        delwin(items[i]);
    free(items);
}

int scroll_menu(WINDOW **items,int count,int menu_start_col, int index_num)
{
    int key;
    int selected=0;
    while (1) 
    {
        key=getch();
        if (key==KEY_DOWN || key==KEY_UP) 
        {
            wbkgd(items[selected+1],COLOR_PAIR(2));
            wnoutrefresh(items[selected+1]);
            if (key==KEY_DOWN) 
            {
                selected=(selected+1) % count;
            } 
            else 
            {
                selected=(selected+count-1) % count;
            }
            wbkgd(items[selected+1],COLOR_PAIR(1));
            wnoutrefresh(items[selected+1]);
            doupdate();
        } 
        else if (key==ESCAPE) 
        {
            return -1;
        } 
        else if (key==ENTER) 
        {
            return selected;
        }
    }
}

void init_scr()
{
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_WHITE);
    curs_set(2);
    noecho();
    keypad(stdscr, TRUE);
}

void make_menubar(WINDOW *menubar)
{
    wbkgd(menubar, COLOR_PAIR(2));

    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "File");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(a)");
    wmove(menubar, 0, 20);
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "Help");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(h)");
    wattron(menubar, COLOR_PAIR(3));
}



int main()
{
    WINDOW *menubar, *statusbar, *about;
    int key;
    init_scr();
    bkgd(COLOR_PAIR(1));
    menubar = subwin(stdscr, 1, 80, 0, 0);
    statusbar = subwin(stdscr, 1, 79, 23, 1);
    make_menubar(menubar);
    move(2, 1);
    printw("Press 'a' or 'h' to open the menus. ");
    printw("ESC or 'q' quits.");
    refresh();    
    while(1)
    {
        WINDOW **menu_items;            
        int selected_item;

        key = getch();
        werase(statusbar);
        wrefresh(statusbar);

        if (key == 'a')
        {
            menu_items=file_menu_list(0);
            selected_item = scroll_menu(menu_items, 4, 20, 0); 
            delete_menu(menu_items, 5);
            if (selected_item < 0)
                wprintw(statusbar, "You haven't selected any item");
            else
                wprintw(statusbar, "You have selected menu item %d.", selected_item);
            touchwin(stdscr);
            refresh();    
        }
        if (key == 'h')
        {
            menu_items=help_menu_list(20);
            selected_item = scroll_menu(menu_items, 2, 0, 1); 
            delete_menu(menu_items, 3);
            if (selected_item == 1)
            {
                about_window();
            }
            if (selected_item < 0)
                wprintw(statusbar, "You haven't selected any item");
            
        }
        if (key == ESCAPE || key == 'q')
        {
            if (check_quit() == 1)
                break;
        }
        touchwin(stdscr);
        refresh();    
    }
    endwin();
}
