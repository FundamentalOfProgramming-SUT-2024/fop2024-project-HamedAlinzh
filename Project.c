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
int handle_input(int height, int width);
int OPTIONS(int height, int width);
int MUSIC_SELECTION(int height, int width);
void init_audio();
void play_music(const char *file);
void stop_music();
int SCORE_BOARD(int height, int width);


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
    handle_input(height, width);
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
    int current_music = 0; // Variable to store the selected music track

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
            case '\n': // ENTER key
                if (selected == 0) { // Change Music
                    current_music = MUSIC_SELECTION(height, width);
                    if (current_music == 4){
                        clear();
                        refresh();
                        break;
                    }
                    else if (current_music == 1){
                        init_audio();
                        play_music("c418_-_aria_math.mp3");
                        SDL_Delay(20000);
                        stop_music();
                        clear();
                        refresh();
                    }
                    else if (current_music != -1) {
                        clear();
                        refresh();
                    }
                } else if (selected == n_options - 1) { // Back
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
        "Track 1: Adventure",
        "Track 2: Battle Theme",
        "Track 3: Calm Forest",
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
            case '\n': // ENTER key
                return selected + 1; // Return the index of the selected track
        }
    }
}

int SCORE_BOARD(int height, int width) {
    clear();
    refresh();

    FILE *scoreB = fopen("SCOREBOARD.txt", "r");
    if (!scoreB) {
        mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
        refresh();
        getch();
        return 1;
    }

    Player players[100];
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
    for (int i = 0; i < player_count && line < 18; i++) { // Prevent overflow
        mvwprintw(score_win, ++line, 2, "%-10s %5d %5d", players[i].name, players[i].age, players[i].score);
        wrefresh(score_win);
    }

    mvwprintw(score_win, line + 2, 2, "Press any key to return...");
    wrefresh(score_win);

    getch();
    delwin(score_win);
    return 1;
}
int comparePlayers(const void *a, const void *b) {
    Player *playerA = (Player *)a;
    Player *playerB = (Player *)b;
    return playerB->score - playerA->score;
}
int handle_input(int height, int width){
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
                    if (selected == 1) {
                        break;      
                    }
                }
                break;
            case 3:
                SCORE_BOARD(height, width);
                break;
            case 4:
                clear();
                mvprintw(height / 2, width / 2 - 4, "EXITING...");
                refresh();
                napms(300); 
                endwin();   
                return 0; 
            default:
                break;
        }
    }
}
void init_audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printw("Failed to initialize SDL audio: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printw("SDL_Mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
}
void play_music(const char *file) {
    Mix_Music *music = Mix_LoadMUS(file);
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(music, -1); // Play the music in a loop
}
void stop_music() {
    Mix_HaltMusic();
    Mix_CloseAudio();
}

