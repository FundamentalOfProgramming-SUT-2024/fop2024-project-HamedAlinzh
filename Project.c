#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <pthread.h>
#include <SDL2/SDL_mixer.h>
typedef struct Player{
    char name[50];
    int age;
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
        "CHARACTER COLOR",
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
                        start_music("track3.mp3");
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
        "Exit"
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

    while (fscanf(scoreB, "%s %d %d", players[player_count].name, 
                  &players[player_count].age, &players[player_count].score) == 3) {
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
        mvwprintw(score_win, ++line, 2, "%-10s %15d %15d", players[i].name, players[i].age, players[i].score);
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
int new_player(int height, int width, Player players[]){
    clear();
    refresh();
    FILE *player_data = fopen("SCOREBOARD.txt", "a");
    if (!player_data){
        mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
        refresh();
        getch();
        return 1;
    }
    WINDOW *new_player_win = newwin(30, 80, (height - 30) / 2, (width - 80) / 2);
    box(new_player_win, 0, 0);
    char* info[] = {"USER NAME:", "PASSWORD:", "EMAIL:"};
    int n_options = sizeof(info) / sizeof(info[0]);
    int selected = 0;
    int key;
    int current_music = 0;
    char *USERNAME = (char*)malloc(40 * sizeof(char));
    char *PASSWORD = (char*)malloc(40 * sizeof(char));
    char *EMAIL = (char*)malloc(60 * sizeof(char));
    while (1) {
        mvwprintw(new_player_win, 1, 2, "FILL OUT THE INFORMATION:");
        mvwprintw(new_player_win, 10, 30, "(PRESS R TO GENERATE RANDOM PASSWORD) ");
        mvwprintw(new_player_win, 27, 30, "Press Esc to return...");
        for (int i = 0; i < n_options; i++) {
            if (i == selected) {
                wattron(new_player_win, A_REVERSE);
                mvwprintw(new_player_win, 5 + 5 * i, 2, "%s", info[i]);
                wattroff(new_player_win, A_REVERSE);
            } else {
                mvwprintw(new_player_win, 5 + 5 * i, 2, "%s", info[i]);
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
            case 27:
                delwin(new_player_win);
                return 1;
                break;
            case '\n':
                if (selected == 0) {
                    wmove(new_player_win, 5 , 14);
                    echo();
                    wrefresh(new_player_win);
                    wscanw(new_player_win, "%s", USERNAME);
                    wrefresh(new_player_win);
                    key = getch();
                    if (key == '\n'){
                        if (PASSWORD != NULL && USERNAME != NULL && EMAIL != NULL){
                            fprintf(player_data, "%s    %s    %s\n", USERNAME, PASSWORD, EMAIL);
                        }
                        fclose(player_data);
                        break;
                    }
                    break;
                } 
                else if (selected == 1){
                    wmove(new_player_win, 10 , 14);
                    echo();
                    wrefresh(new_player_win);
                    wscanw(new_player_win, "%s", PASSWORD);
                    wrefresh(new_player_win);
                    key = getch();
                    if (key == '\n'){
                        break;
                    }
                }
                else if (selected == 2) {
                    wmove(new_player_win, 15 , 14);
                    echo();
                    wrefresh(new_player_win);
                    wscanw(new_player_win, "%s", EMAIL);
                    wrefresh(new_player_win);
                    key = getch();
                    if (key == '\n'){
                        break;
                    }
                }
                break;
        }
    }
}



