#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <pthread.h>
#include <SDL2/SDL_mixer.h>
#include<time.h>
#include<regex.h>
typedef struct Player{
    char name[50];
    char password[40];
    char email[60];
    int score;
} Player;
int comparePlayers(const void *a, const void *b);
int loading_screen();
int main_menu(int height, int width);
int handle_input(int height, int width, Player players[]);
int OPTIONS(int height, int width);
int MUSIC_SELECTION(int height, int width);
void *play_music_background(void *arg);
pthread_t music_thread;
void start_music(const char *music_file);
void play_music(const char *file);
void stop_music();
int SCORE_BOARD(int height, int width, Player players[]);
int new_player(int height, int width, Player players[]);
int checkpass(char password[]);
int isValidEmail(const char *email);

int main(){
    Player players[100];
    initscr();
    int height, width;
    getmaxyx(stdscr, height, width);
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    start_color();
    bkgd(COLOR_BLACK);
    loading_screen();
    start_music("c418_-_aria_math.mp3");
    int running = 1;
    while (running) {
        running = handle_input(height, width, players);
    }
    endwin();
    return 0;
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

    getchar();
    return 1;
}
int main_menu(int ter_height, int ter_width) {
    clear();
    refresh();

    int height = ter_height * 3 / 5, width = ter_width * 3 / 5, starty = ter_height/5, startx = ter_width/5;
    WINDOW *menu_win = newwin(height, width, starty, startx);
    const char *menu_items[] = {"START THE GAME","NEW PLAYER", "OPTIONS", "SCORE BOARD", "EXIT"};
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
                mvwprintw(menu_win, 6 + 5 * i, (width - 12) / 2, "%s", menu_items[i]);
                wattroff(menu_win, A_REVERSE);
            } else {
                mvwprintw(menu_win, 6 + 5 * i, (width - 12) / 2, "%s", menu_items[i]);
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
int OPTIONS(int height, int width) {
    clear();
    refresh();
    const char *options[] = {
        "CHANGE MUSIC",
        "CHARACTER DESIGN",
        "ADJUST DIFFICULTY",
        "BACK"
    };
    int n_options = sizeof(options) / sizeof(options[0]);
    int selected = 0;
    int key;
    int current_music = 0;
    WINDOW *options_win = newwin(15, 40, (height - 15) / 2, (width - 40) / 2);
    box(options_win, 0, 0);

    while (1) {
        mvwprintw(options_win, 1, 2, "OPTIONS");
        for (int i = 0; i < n_options; i++) {
            if (i == selected) {
                wattron(options_win, A_REVERSE);
                mvwprintw(options_win, 5 + 2 * i, 2, "%s", options[i]);
                wattroff(options_win, A_REVERSE);
            } else {
                mvwprintw(options_win, 5 + 2 * i, 2, "%s", options[i]);
            }
        }
        wrefresh(options_win);

        key = getch();
        switch (key) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = n_options - 1;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= n_options) selected = 0;
                break;
            case '\n':
                if (selected == 0) {
                    int current_music = MUSIC_SELECTION(height, width);
                    if (current_music == 1) {
                        start_music("c418_-_aria_math.mp3");
                    } else if (current_music == 2) {
                        start_music("rymykhs_ahng_amng_as.mp3");
                    } else if (current_music == 3) {
                        start_music("bad-piggies-theme.mp3");
                    } else if (current_music == 4) {
                        stop_music("bad-piggies-theme.mp3");
                    }
                    clear();
                    refresh();
                    break;
                } 
                else if (selected == n_options - 1) {
                    delwin(options_win);
                    return 1;
                }
                break;
        }
    }
}
int MUSIC_SELECTION(int height, int width) {
    clear();
    refresh();

    const char *music_tracks[] = {
        "Track 1: ARIA MATH",
        "Track 2: AMONG US",
        "Track 3: BAD PIGGIES",
        "DISCONNECT"
    };
    int n_tracks = sizeof(music_tracks) / sizeof(music_tracks[0]);
    int selected = 0;
    int key;

    WINDOW *music_win = newwin(10, 40, (height - 10) / 2, (width - 40) / 2);
    box(music_win, 0, 0);

    while (1) {
        mvwprintw(music_win, 1, 2, "MUSIC SELECTION");
        for (int i = 0; i < n_tracks; i++) {
            if (i == selected) {
                wattron(music_win, A_REVERSE);
                mvwprintw(music_win, 3 + i, 2, "%s", music_tracks[i]);
                wattroff(music_win, A_REVERSE);
            } else {
                mvwprintw(music_win, 3 + i, 2, "%s", music_tracks[i]);
            }
        }
        wrefresh(music_win);

        key = getch();
        switch (key) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = n_tracks - 1;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= n_tracks) selected = 0;
                break;
            case '\n':
                return selected + 1; 
        }
    }
}
int SCORE_BOARD(int height, int width, Player players[]) {
    clear();
    refresh();
    FILE *scoreB = fopen("SCOREBOARD.txt", "r");
    if (!scoreB) {
        mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
        refresh();
        getch();
        return 1;
    }    
    int player_count = 0;

    while (fscanf(scoreB, "%s %s %d", players[player_count].name, 
                  players[player_count].password, &players[player_count].score) == 3) {
        player_count++;
        if (player_count >= 100) {
            break;
        }
    }
    fclose(scoreB);
    qsort(players, player_count, sizeof(Player), comparePlayers);
    WINDOW *score_win = newwin(20, 60, (height - 20) / 2, (width - 60) / 2);
    box(score_win, 0, 0);
    mvwprintw(score_win, 1, 2, "SCOREBOARD");
    wrefresh(score_win);

    int line = 2;
    for (int i = 0; i < player_count && line < 18; i++) {
        mvwprintw(score_win, ++line, 2, "%-10s %15s %15d", players[i].name, players[i].password, players[i].score);
        wrefresh(score_win);
    }

    mvwprintw(score_win, 17, 19, "Press Esc to return...");
    wrefresh(score_win);
    char ch;
    while (1){
        ch = getchar();
        if (ch == 27){
            delwin(score_win);
            return 1;
        }
    }
}
int comparePlayers(const void *a, const void *b) {
    Player *playerA = (Player *)a;
    Player *playerB = (Player *)b;
    return playerB->score - playerA->score;
}
int handle_input(int height, int width, Player players[]) {
    while (1) {
        int selected_option = main_menu(height, width);

        switch (selected_option) {
            case 1:
                break;
            case 2:
                new_player(height, width, players);
                break;
            case 3:
                while (1) {
                    int selected = OPTIONS(height, width);
                    if (selected == 1) {
                        break;
                    }
                }
                break;

            case 4:
                clear();
                SCORE_BOARD(height, width, players);
                break;

            case 5: {
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
void *play_music_background(void *arg) {
    const char *music_file = (const char *)arg;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Music *music = Mix_LoadMUS(music_file);
    if (!music) {
        printf("Error loading music: %s\n", Mix_GetError());
        return NULL;
    }

    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Error playing music: %s\n", Mix_GetError());
    }
    while (Mix_PlayingMusic()) {
        SDL_Delay(100); 
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    return NULL;
}
void play_music(const char *file) {
    Mix_Music *music = Mix_LoadMUS(file);
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(music, -1);
}
void stop_music() {
    Mix_HaltMusic();          
    pthread_cancel(music_thread);
    pthread_join(music_thread, NULL); 
}
void start_music(const char *music_file) {
    if (pthread_create(&music_thread, NULL, play_music_background, (void *)music_file) != 0) {
        printf("Failed to create music thread\n");
    }
}
int new_player(int height, int width, Player players[]) {
    clear();
    refresh();
    FILE *player_data = fopen("SCOREBOARD.txt", "a+");
    if (!player_data) {
        mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
        refresh();
        getch();
        return 1;
    }

    int player_count = 0;
    while (fscanf(player_data, "%s", players[player_count].name) == 1) {
        player_count++;
        if (player_count >= 100) {
            break;
        }
    }

    WINDOW *new_player_win = newwin(30, 80, (height - 30) / 2, (width - 80) / 2);
    box(new_player_win, 0, 0);

    char *info[] = {"USER NAME:", "PASSWORD:", "EMAIL:"};
    int n_options = sizeof(info) / sizeof(info[0]);
    int selected = 0;
    int key;

    char USERNAME[50] = {0};
    char PASSWORD[50] = {0};
    char EMAIL[60] = {0};

    while (1) {
        mvwprintw(new_player_win, 1, 2, "FILL OUT THE INFORMATION:");
        mvwprintw(new_player_win, 25, 40, "(PRESS R TO GENERATE RANDOM PASSWORD) ");
        mvwprintw(new_player_win, 1, 44, "PRESS S TO SAVE!");
        mvwprintw(new_player_win, 28, 30, "PRESS ESC TO RETURN...");
        for (int i = 0; i < n_options; i++) {
            if (i == selected) {
                wattron(new_player_win, A_REVERSE);
                mvwprintw(new_player_win, 5 + 7 * i, 2, "%s", info[i]);
                wattroff(new_player_win, A_REVERSE);
            } else {
                mvwprintw(new_player_win, 5 + 7 * i, 2, "%s", info[i]);
            }
        }
        wrefresh(new_player_win);

        key = getch();
        switch (key) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = n_options - 1;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= n_options) selected = 0;
                break;
            case '\n': 
                echo();
                if (selected == 0) {
                    
                    curs_set(1);
                    wmove(new_player_win, 5, 14);
                    wrefresh(new_player_win);

                    while (1) {
                        wgetnstr(new_player_win, USERNAME, sizeof(USERNAME) - 1);
                        int username_exists = 0;

                        for (int i = 0; i < player_count; i++) {
                            if (strcmp(players[i].name, USERNAME) == 0) {
                                username_exists = 1;
                                break;
                            }
                        }

                        if (username_exists) {
                            mvwprintw(new_player_win, 5, 14, "                 ");
                            mvwprintw(new_player_win, 7, 14, "USERNAME NOT AVAILABLE!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 5, 14); 
                            continue;
                        } else {
                            mvwprintw(new_player_win, 7, 14, "                           ");
                            wrefresh(new_player_win);
                            break;
                        }
                    }
                    curs_set(0);
                } else if (selected == 1) { 
                    mvwprintw(new_player_win, 12, 14, "                              "); 
                    curs_set(1);
                    while (1){
                        wmove(new_player_win, 12, 14); 
                        wrefresh(new_player_win);
                        wgetnstr(new_player_win, PASSWORD, sizeof(PASSWORD) - 1);
                        if (strlen(PASSWORD) < 7){
                            mvwprintw(new_player_win, 12, 14, "                       ");
                            mvwprintw(new_player_win, 14, 14, "PASSWORD MUST HAVE AT LEAST 7 CHARACTERS!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 12, 14);
                            continue;
                        }
                        else if (checkpass(PASSWORD) == 0){
                            mvwprintw(new_player_win, 12, 14, "                 ");
                            mvwprintw(new_player_win, 16, 14, "YOU HAVE TO USE AT LEAST 1 UPPERCASE AND 1 LOWERCASE!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 12, 14);
                            continue;
                        }
                        else {
                                mvwprintw(new_player_win, 16, 14, "                                                     ");
                                mvwprintw(new_player_win, 14, 14, "                                                 ");
                                wrefresh(new_player_win);
                                break; 
                        }
                    }
                    curs_set(0);
                } else if (selected == 2) { 
                    mvwprintw(new_player_win, 19, 14, "                                                ");
                    curs_set(1);
                    while (1){
                        wmove(new_player_win, 19, 14); 
                        wrefresh(new_player_win);
                        wgetnstr(new_player_win, EMAIL, sizeof(EMAIL) - 1);
                        if (isValidEmail(EMAIL) == 0){
                            mvwprintw(new_player_win, 19, 14, "                 ");
                            mvwprintw(new_player_win, 21, 14, "INVALID EMAIL FORMAT!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 19, 14);
                            continue;
                        }
                        else{
                            mvwprintw(new_player_win, 21, 14, "                                        ");
                            wrefresh(new_player_win);
                            break; 
                        }
                    }
                    curs_set(0);
                }
                noecho();
                break;
            case 'r':
                if (selected == 1) {
                    snprintf(PASSWORD, sizeof(PASSWORD), "Random%d", rand() % 10000);
                    mvwprintw(new_player_win, 10, 14, "                              ");
                    mvwprintw(new_player_win, 10, 14, "%s", PASSWORD);
                    wrefresh(new_player_win);
                }
                break;
            case 'S':
            case 's':
                if (strlen(USERNAME) > 0 && strlen(PASSWORD) > 0 && strlen(EMAIL) > 0) {
                    fprintf(player_data, "%s    %s    %s\n", USERNAME, PASSWORD, EMAIL);
                    fclose(player_data);
                    delwin(new_player_win);
                    return 0;
                } else {
                    mvwprintw(new_player_win, 25, 2, "ALL FIELDS MUST BE FILLED!");
                    wrefresh(new_player_win);
                }
                break;
            case 27:
                return 0;
                break;
        }
    }
}
int checkpass(char password[]){
    int hasU  = 0;
    int hasL = 0;
    int passlen = strlen(password);
    for (int i = 0; i < passlen; i++){
        if (password[i] >= 'A' && password[i] <= 'Z'){
            hasU = 1;
        }
    }
    for (int i = 0; i < passlen; i++){
        if (password[i] >= 'a' && password[i] <= 'z'){
            hasL = 1;
        }
    }
    if (hasU && hasL){
        return 1;
    }
    return 0;
}
int isValidEmail(const char *email) {
    const char *pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }
    result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    if (result == 0) {
        return 1;  // Valid email
    } else {
        return 0;  // Invalid email
    }
}


