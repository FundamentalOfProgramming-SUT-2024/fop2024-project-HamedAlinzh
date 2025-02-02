#include"rogue.h"


int main(){
    // playerG *player = playersetup();
    Player players[100];
    Game *game = malloc(sizeof(Game));
    // game->player = player;
    game->clevel = 0;
    int player_num = load_players(players, "SCOREBOARD.txt", game);
    setlocale(LC_ALL, "");
    initscr();
    int height, width;
    getmaxyx(stdscr, height, width);
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    start_color();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(11, COLOR_RED, COLOR_BLACK); 
    init_pair(12, COLOR_BLUE, COLOR_BLACK); 
    init_pair(13, COLOR_GREEN, COLOR_BLACK); 
    init_pair(14, COLOR_YELLOW, COLOR_BLACK); 
    init_pair(15, COLOR_WHITE, COLOR_BLACK);  
    init_pair(16, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(17, COLOR_CYAN, COLOR_BLACK);
    init_pair(21, COLOR_RED, COLOR_BLACK); 
    init_pair(0xFF, COLOR_BLACK, COLOR_WHITE);
    bkgd(COLOR_BLACK);
    loading_screen();
    start_music("01. Main Menu.mp3");
    int running = 1;
    
    while (running) {
        running = handle_inputs(height, width, players, game);
    }
    endwin();
    return 0;
}

int loading_screen(){
    attron(COLOR_PAIR(17));
    mvprintw(24, 45, "                                  COPYRIGHT © HAMED ALINEZHAD FOP2024                                ");
    attroff(COLOR_PAIR(17));
    refresh();
    napms(2000);
    clear();
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
    napms(200);
    mvprintw(40, 61, "__________________");
    mvprintw(41, 61, "|________________| 20%%");
    refresh();
    napms(200);
    mvprintw(40, 61, "________________________");
    mvprintw(41, 61, "|______________________| 30%%");
    refresh();
    napms(200);
    mvprintw(40, 61, "______________________________");
    mvprintw(41, 61, "|____________________________| 40%%");
    refresh();
    napms(200);
    mvprintw(40, 61, "____________________________________");
    mvprintw(41, 61, "|__________________________________| 50%%");
    refresh();
    napms(200);
    mvprintw(40, 61, "__________________________________________");
    mvprintw(41, 61, "|________________________________________| 60%%");
    refresh();
    napms(200);
    mvprintw(40, 61, "________________________________________________");
    mvprintw(41, 61, "|______________________________________________| 70%%");
    refresh();
    napms(200);
    mvprintw(40, 61, "______________________________________________________");
    mvprintw(41, 61, "|____________________________________________________| 80%%");
    refresh();
    napms(200);
    mvprintw(40, 61, "____________________________________________________________");
    mvprintw(41, 61, "|__________________________________________________________| 90%%");
    refresh();
    napms(200);
    mvprintw(40, 61, "__________________________________________________________________");
    mvprintw(41, 61, "|________________________________________________________________| 100%%");
    refresh();
    napms(200);
    mvprintw(40, 60, "                                                                      ");
    mvprintw(41, 60, "                                                                      \n");
    mvprintw(41, 71, "WELCOME TO THE ROGUE! PRESS ANY KEY TO CONTINUE...");
    refresh();

    getchar();
    return 1;
}
int main_menu(int ter_height, int ter_width, Player player, Game *game) {
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

        mvwprintw(menu_win, 0, (width - 30) / 2, "  #### ROGUE MAIN MENU ####  ");
        mvwprintw(menu_win, 2, 3, "        _   ,_,   _");                                                
        mvwprintw(menu_win, 3, 3, "       / `'=) (='` \\");
        mvwprintw(menu_win, 4, 3, "      /.-.-.\\ /.-.-.\\ ");
        mvwprintw(menu_win, 5, 3, "      `      \"      `");            
        mvwprintw(menu_win, height - 7, 70, "      /| ________________");       
        mvwprintw(menu_win, height - 6, 70, "O|===|* >________________>");
        mvwprintw(menu_win, height - 5, 70, "      \\|");
        mvwprintw(menu_win, 3, 75, "                      ____    ");   
        mvwprintw(menu_win, 4, 75, "                     / ___`\\  ");  
        mvwprintw(menu_win, 5, 75, "         /|         ( (   \\ \\ ");  
        mvwprintw(menu_win, 6, 75, "    |^v^v  V|        \\ \\/) ) )");
        mvwprintw(menu_win, 7, 75, "    \\  ____ /         \\_/ / / ");  
        mvwprintw(menu_win, 8, 75, "    ,Y`    `,            / /  "); 
        mvwprintw(menu_win, 9, 75, "    ||  -  -)           { }   ");
        mvwprintw(menu_win, 10, 75, "    \\\\   _\\ |           | |   "); 
        mvwprintw(menu_win, 11, 75, "     \\\\ / _`\\_         / /    "); 
        mvwprintw(menu_win, 12, 75, "     / |  ~ | ``\\     _|_|    "); 
        mvwprintw(menu_win, 13, 75, "  ,-`  \\    |  \\ \\  ,//(_}    "); 
        mvwprintw(menu_win, 14, 75, " /      |   |   | \\/  \\| |    ");   
        mvwprintw(menu_win, 15, 75, "|       |   |   | '   ,\\ \\    ");
        mvwprintw(menu_win, 16, 75, "|     | \\   /  /\\  _/`  | |   "); 
        mvwprintw(menu_win, 17, 75, "\\     |  | |   | ``     | |   "); 
        mvwprintw(menu_win, 18, 75, " |    \\  \\ |   |        | |   "); 
        mvwprintw(menu_win, 19, 75, " |    |   |/   |        / /   ");
        mvwprintw(menu_win, 20, 75, " |    |        |        | |   "); 
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
        mvwprintw(menu_win, 33 - 12, 2, "           4       do              ");
        mvwprintw(menu_win, 34 - 12, 2, "           4      P                ");
        mvwprintw(menu_win, 35 - 12, 2, "           4     2                 ");
        mvwprintw(menu_win, 36 - 12, 2, "           4    0                  ");
        mvwprintw(menu_win, 37 - 12, 2, "           J.  2                  ");
        mvwprintw(menu_win, 38 - 12, 2, "          '$$ 4                     ");

        for (int i = 0; i < n_items; i++) {
            if (i == choice) {
                wattron(menu_win, A_REVERSE);
                mvwprintw(menu_win, 6 + 5 * i, (width - 16) / 2, "%s", menu_items[i]);
                wattroff(menu_win, A_REVERSE);
            } else {
                mvwprintw(menu_win, 6 + 5 * i, (width - 16) / 2, "%s", menu_items[i]);
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

int handle_inputs(int height, int width, Player players[], Game *game) {
    while (1) {
        int selected_option = main_menu(height, width, players[0], game);

        switch (selected_option) {
            case 1:
                start_menu(height, width, players, game);
                break;
            case 2:
                while (1) {
                    int selected = OPTIONS(height, width, players[0], game);
                    if (selected == 1) {
                        break;
                    }
                }
                break;

            case 3:
                clear();
                SCORE_BOARD(height, width, players, game);
                break;

            case 4: {
                int confirm_selected = 0;
                int key;

                while (1) {
                    clear();
                    mvprintw(height / 2, width / 2 - 6, "ARE YOU SURE?");
                    
                    if (confirm_selected == 0) {
                        attron(A_BOLD | A_REVERSE);
                        mvprintw(height / 2 + 2, width / 2 - 6, "YES");
                        attroff(A_BOLD | A_REVERSE);
                        mvprintw(height / 2 + 2, width / 2 + 6, "NO");
                    } else {
                        mvprintw(height / 2 + 2, width / 2 - 6, "YES");
                        attron(A_BOLD | A_REVERSE);
                        mvprintw(height / 2 + 2, width / 2 + 6, "NO");
                        attroff(A_BOLD | A_REVERSE);
                    }

                    refresh();
                    key = getch();
                    switch (key) {
                        case KEY_LEFT:
                            confirm_selected = 0;
                            break;
                        case KEY_RIGHT:
                            confirm_selected = 1;
                            break;
                        case '\n':
                            if (confirm_selected == 0) {
                                clear();
                                mvprintw(height / 2, width / 2 - 4, "EXITING...");
                                refresh();
                                napms(2000);
                                endwin();
                                return 0;
                            } else if (confirm_selected == 1) {
                                return 1;
                            }
                            break;
                    }
                }
                break;
            }

            default:
                break;
        }
    }
}

