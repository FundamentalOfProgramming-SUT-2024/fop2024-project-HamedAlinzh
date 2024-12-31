#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<stdlib.h>

int loading_screen();
int main_menu(int height, int width);
int handle_input(char ch);
int OPTIONS(int height, int width);



int main(){
    char ch;
    initscr();
    int height, width;
    getmaxyx(stdscr, height, width);
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    start_color();
    bkgd(COLOR_BLACK);
    loading_screen();
    
    while (1) {
        int selected_option = main_menu(height, width);

        switch (selected_option) {
            case 1:
                mvprintw(1, 1, "Start Game Selected");
                refresh();
                getch();
                break;
            case 2:
                while (1) {
                    int selected = OPTIONS(height, width);
                    if (selected == 3) {
                        break;      
                    }
                }
                break;
            case 3:
                SCORE_BOARD();
                return 0;
            case 4:
                clear();
                mvprintw(height / 2, width / 2 - 4, "EXITING...");
                refresh();
                napms(3000); 
                endwin();   
                return 0; 
            default:
                break;
        }
    }


    // Clear screen and display the result
    
    // while ((ch = getchar()) != 27) {  // 27 is the ESC key
    //     handle_input(ch);
    // }
    endwin();


}

int loading_screen(){
    mvprintw(14, 45, "                                                                                                       ");
    mvprintw(15, 45, "RRRRRRRRRRRRRRRRR        OOOOOOOOO             GGGGGGGGGGGGGUUUUUUUU     UUUUUUUUEEEEEEEEEEEEEEEEEEEE");
    mvprintw(16, 45, "R::::::::::::::::R     OO:::::::::OO        GGG::::::::::::GU::::::U     U::::::UE::::::::::::::::::::E");
    mvprintw(17, 45, "R::::::RRRRRR:::::R  OO:::::::::::::OO    GG:::::::::::::::GU::::::U     U::::::UE::::::::::::::::::::E");
    mvprintw(18, 45, "RR:::::R     R:::::RO:::::::OOO:::::::O  G:::::GGGGGGGG::::GUU:::::U     U:::::UUEE::::::EEEEEEEEE::::E");
    mvprintw(19, 45, "  R::::R     R:::::RO::::::O   O::::::O G:::::G       GGGGGG U:::::U     U:::::U   E:::::E       EEEEEE");
    mvprintw(20, 45, "  R::::R     R:::::RO:::::O     O:::::OG:::::G               U:::::D     D:::::U   E:::::E             ");
    mvprintw(21, 45, "  R::::RRRRRR:::::R O:::::O     O:::::OG:::::G               U:::::D     D:::::U   E::::::EEEEEEEEEE   ");
    mvprintw(22, 45, "  R:::::::::::::RR  O:::::O     O:::::OG:::::G    GGGGGGGGGG U:::::D     D:::::U   E:::::::::::::::E   ");
    mvprintw(23, 45, "  R::::RRRRRR:::::R O:::::O     O:::::OG:::::G    G::::::::G U:::::D     D:::::U   E:::::::::::::::E   ");
    mvprintw(24, 45, "  R::::R     R:::::RO:::::O     O:::::OG:::::G    GGGGG::::G U:::::D     D:::::U   E::::::EEEEEEEEEE   ");
    mvprintw(25, 45, "  R::::R     R:::::RO:::::O     O:::::OG:::::G        G::::G U:::::D     D:::::U   E:::::E             ");
    mvprintw(26, 45, "  R::::R     R:::::RO::::::O   O::::::O G:::::G       G::::G U::::::U   U::::::U   E:::::E       EEEEEE");
    mvprintw(27, 45, "RR:::::R     R:::::RO:::::::OOO:::::::O  G:::::GGGGGGGG::::G U:::::::UUU:::::::U EE::::::EEEEEEEE:::::E");
    mvprintw(28, 45, "R::::::R     R:::::R OO:::::::::::::OO    GG:::::::::::::::G  UU:::::::::::::UU  E::::::::::::::::::::E");
    mvprintw(29, 45, "R::::::R     R:::::R   OO:::::::::OO        GGG::::::GGG:::G    UU:::::::::UU    E::::::::::::::::::::E");
    mvprintw(30, 45, "RRRRRRRR     RRRRRRR     OOOOOOOOO             GGGGGG   GGGG      UUUUUUUUU      EEEEEEEEEEEEEEEEEEEEEE");
    mvprintw(40, 61, "___________");
    mvprintw(41, 61, "|__________| 10%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "__________________");
    mvprintw(41, 61, "|________________| 20%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "________________________");
    mvprintw(41, 61, "|______________________| 30%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "______________________________");
    mvprintw(41, 61, "|____________________________| 40%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "____________________________________");
    mvprintw(41, 61, "|__________________________________| 50%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "__________________________________________");
    mvprintw(41, 61, "|________________________________________| 60%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "________________________________________________");
    mvprintw(41, 61, "|______________________________________________| 70%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "______________________________________________________");
    mvprintw(41, 61, "|____________________________________________________| 80%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "____________________________________________________________");
    mvprintw(41, 61, "|__________________________________________________________| 90%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "__________________________________________________________________");
    mvprintw(41, 61, "|________________________________________________________________| 100%%");
    refresh();
    napms(50);
    init_pair(1, COLOR_WHITE, COLOR_RED);
    mvprintw(40, 60, "                                                                      ");
    mvprintw(41, 60, "                                                                      \n");
    // attron(COLOR_PAIR(1));
    // attron(A_BLINK);
    mvprintw(41, 71, "WELCOME TO THE ROGUE! PRESS ANY KEY TO CONTINUE...");
    // attroff(COLOR_PAIR(1));
    refresh();

    // int key_pressed = 0; // Flag to check if a key is pressed
    // char ch = 0;
    // nodelay(stdscr, TRUE);
    // while (1) {
    //     // Top side of the rectangle
    //     for (int i = 0; i < 67 && !key_pressed; i++) {
    //         mvprintw(39, 63 + i, "@");
    //         napms(50); // Adjust speed
    //         refresh();
    //         mvprintw(39, 63 + i, " ");
    //         ch = getchar();
    //         if (ch != 0){
    //             break;
    //         }
    //     }
    //     for (int i = 0; i < 5 && !key_pressed; i++) {
    //         mvprintw(39 + i, 129, "@");
    //         napms(50);
    //         refresh();
    //         mvprintw(39 + i, 129, " ");
    //         ch = getchar();
    //         if (ch != 0){
    //             break;
    //         }
    //     }
    //     for (int i = 67; i > 0 && !key_pressed; i--) {
    //         mvprintw(43, 62 + i, "@");
    //         napms(50);
    //         refresh();
    //         mvprintw(43, 62 + i, " ");
    //         ch = getchar();
    //         if (ch != 0){
    //             break;
    //         }
    //     }
    //     for (int i = 5; i > 0 && !key_pressed; i--) {
    //         mvprintw(38 + i, 63, "@");
    //         napms(50);
    //         refresh();
    //         mvprintw(38 + i, 63, " ");
    //         ch = getchar();
    //         if (ch != 0){
    //             break;
    //         }
    //     }
    // }

    getchar();
    return 1;
}
int main_menu(int ter_height, int ter_width) {
    clear();
    refresh();

    int height = ter_height * 3 / 5, width = ter_width * 3 / 5, starty = ter_height/5, startx = ter_width/5;
    WINDOW *menu_win = newwin(height, width, starty, startx);
    const char *menu_items[] = {"START THE GAME", "OPTIONS", "SCORE BOARD", "EXIT"};
    int n_items = sizeof(menu_items) / sizeof(menu_items[0]);
    int choice = 0;
    int key;

    box(menu_win, 0, 0);

    while (1) {
        werase(menu_win);
        box(menu_win, 0, 0); 

        mvwprintw(menu_win, 1, (width - 20) / 2, "#### ROGUE MAIN MENU ####");
        mvwprintw(menu_win, 2, 3, "        _   ,_,   _");                                                
        mvwprintw(menu_win, 3, 3, "       / `'=) (='` \\");
        mvwprintw(menu_win, 4, 3, "      /.-.-.\\ /.-.-.\\ ");
        mvwprintw(menu_win, 5, 3, "      `      \"      `");            
        mvwprintw(menu_win, height - 5, 70, "      /| ________________");       
        mvwprintw(menu_win, height - 4, 70, "O|===|* >________________>");
        mvwprintw(menu_win, height - 3, 70, "      \\|");
        mvwprintw(menu_win, 9, 70, "        _   ,_,   _");                                                
        mvwprintw(menu_win, 10, 70, "       / `'=) (='` \\");
        mvwprintw(menu_win, 11, 70, "      /.-.-.\\ /.-.-.\\ ");
        mvwprintw(menu_win, 12, 70, "      `      \"      `"); 
        mvwprintw(menu_win, 20 - 12, 2, "          4$$-.                    ");                                                
        mvwprintw(menu_win, 21 - 12, 2, "           4   \".                 ");
        mvwprintw(menu_win, 22 - 12, 2, "           4    ^.                 ");
        mvwprintw(menu_win, 23 - 12, 2, "           4     $                 "); 
        mvwprintw(menu_win, 24 - 12, 2, "           4     'b                ");                                                
        mvwprintw(menu_win, 25 - 12, 2, "           4      \"b.             ");
        mvwprintw(menu_win, 26 - 12, 2, "           4        $              ");
        mvwprintw(menu_win, 27 - 12, 2, "           4        $r             "); 
        mvwprintw(menu_win, 28 - 12, 2, "           4        $F             ");                                                
        mvwprintw(menu_win, 29 - 12, 2, "-$b========4========$b====*P=>     ");
        mvwprintw(menu_win, 30 - 12, 2, "           4       *$$F            ");
        mvwprintw(menu_win, 31 - 12, 2, "           4        $$             "); 
        mvwprintw(menu_win, 32 - 12, 2, "           4       .$F             ");                                                
        mvwprintw(menu_win, 33 - 12, 2, "           4       dP              ");
        mvwprintw(menu_win, 34 - 12, 2, "           4      F                ");
        mvwprintw(menu_win, 35 - 12, 2, "           4     @                 ");
        mvwprintw(menu_win, 36 - 12, 2, "           4    D                  ");
        mvwprintw(menu_win, 37 - 12, 2, "           J.  \".                  ");
        mvwprintw(menu_win, 38 - 12, 2, "          '$$                      ");

        for (int i = 0; i < n_items; i++) {
            if (i == choice) {
                wattron(menu_win, A_REVERSE);
                mvwprintw(menu_win, 6 + 6 * i, (width - 12) / 2, "%s", menu_items[i]);
                wattroff(menu_win, A_REVERSE);
            } else {
                mvwprintw(menu_win, 6 + 6 * i, (width - 12) / 2, "%s", menu_items[i]);
            }
        }
        wrefresh(menu_win);
        key = getch();
        switch (key) {
            case KEY_UP:
                choice--;
                if (choice < 0)
                    choice = n_items - 1;
                break;
            case KEY_DOWN:
                choice++;
                if (choice >= n_items)
                    choice = 0;
                break;
            case '\n':
                delwin(menu_win);
                return choice + 1;
        }
    }
    return 1;
}
int OPTIONS(int ter_height, int ter_width){
    clear();
    refresh();

    int height = ter_height * 2 / 5, width = ter_width * 2 / 5, starty = ter_height * 3 / 10, startx = ter_width * 3 / 10;
    WINDOW *options_win = newwin(height, width, starty, startx);
    const char *options_items[] = {"DIFFICULTY", "CHARACTER COLOR", "BACK"};
    int n_items = sizeof(options_items) / sizeof(options_items[0]);
    int choice = 0;
    int key;
    box(options_win, 0, 0);
    while (1) {
        werase(options_win);
        box(options_win, 0, 0); 
        for (int i = 0; i < n_items; i++) {
            if (i == choice) {
                wattron(options_win, A_REVERSE);
                mvwprintw(options_win, 6 + 4 * i, (width - 12) / 2, "%s", options_items[i]);
                wattroff(options_win, A_REVERSE);
            } else {
                mvwprintw(options_win, 6 + 4 * i, (width - 12) / 2, "%s", options_items[i]);
            }
        }
        wrefresh(options_win);
        key = getch();

        switch (key) {
            case KEY_UP:
                choice--;
                if (choice < 0)
                    choice = n_items - 1;
                break;
            case KEY_DOWN:
                choice++;
                if (choice >= n_items)
                    choice = 0; 
                break;
            case '\n':
                delwin(options_win); 
                return choice + 1; 
        }
    }
    return 1;

}
int handle_input(char ch){
    
}