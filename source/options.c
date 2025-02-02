#include <rogue.h>


int OPTIONS(int height, int width, Player players, Game *game) {
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
    WINDOW *options_win = newwin(35, 100, (height - 35) / 2, (width - 100) / 2);
    // box(options_win, 0, 0);

    while (1) {
        mvwprintw(options_win, 2, 40, "    ###OPTIONS###    ");
        wattron(options_win, COLOR_PAIR(14));
        mvwprintw(options_win, 3, 40,   "                        @@@@                          ");                     
        mvwprintw(options_win, 4, 40,   "                       @@@@@@                         ");             
        mvwprintw(options_win, 5, 40,   "             @@@@    #@@@@@@@@@:   @@@@%%              ");             
        mvwprintw(options_win, 6, 40,   "           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             ");             
        mvwprintw(options_win, 7, 40,   "            @@@@@@@@@@@@@@@@@@@@@@@@@@@@              ");             
        mvwprintw(options_win, 8, 40,   "           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             ");             
        mvwprintw(options_win, 9, 40,   "       @@%%@@@@@@@@@@@*        +@@@@@@@@@@@@@@         ");             
        mvwprintw(options_win, 10, 40,   "    @@@@@@@@@@@@@%%                #@@@@@@@@@@@@@.     ");             
        mvwprintw(options_win, 11, 40,   "   @@@@@@@@@@@@=                    :@@@@@@@@@@@@:    ");             
        mvwprintw(options_win, 12, 40,   "    #@@@@@@@@@                        @@@@@@@@@@      ");             
        mvwprintw(options_win, 13, 40,   "     %%@@@@@@@                          #@@@@@@@       ");             
        mvwprintw(options_win, 14, 40,   "     @@@@@@@                            %%@@@@@@-      ");             
        mvwprintw(options_win, 15, 40,   "    @@@@@@@                              @@@@@@@      ");             
        mvwprintw(options_win, 16, 40,   "#@@@@@@@@@@                              @@@@@@@@@@*  ");             
        mvwprintw(options_win, 17, 40,   "+@@@@@@@@@@                              %%@@@@@@@@@*  ");             
        mvwprintw(options_win, 18, 40,   "+@@@@@@@@@@                              @@@@@@@@@@*  ");             
        mvwprintw(options_win, 19, 40,   "    @@@@@@@                              @@@@@@@      ");             
        mvwprintw(options_win, 20, 40,   "     @@@@@@@                            %%@@@@@@-      ");             
        mvwprintw(options_win, 21, 40,   "     %%@@@@@@@                          @@@@@@@@       ");             
        mvwprintw(options_win, 22, 40,   "    @@@@@@@@@@                        @@@@@@@@@@      ");             
        mvwprintw(options_win, 23, 40,   "   @@@@@@@@@@@@*                    =@@@@@@@@@@@@     ");             
        mvwprintw(options_win, 24, 40,   "    @@@@@@@@@@@@@@                %%@@@@@@@@@@@@@      ");             
        mvwprintw(options_win, 25, 40,   "     @#  #@@@@@@@@@@@%%        %%@@@@@@@@@@@@  =@       ");             
        mvwprintw(options_win, 26, 40,   "           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             ");             
        mvwprintw(options_win, 27, 40,   "            @@@@@@@@@@@@@@@@@@@@@@@@@@@@              ");             
        mvwprintw(options_win, 28, 40,   "           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             ");             
        mvwprintw(options_win, 29, 40,   "             @@@@    =@@@@@@@@*    @@@@=              ");             
        mvwprintw(options_win, 30, 40,   "                       @@@@@@                         ");             
        mvwprintw(options_win, 31, 40,   "                       -@@@@#                         ");   
        wattroff(options_win, COLOR_PAIR(14));         
        box(options_win, 0, 0);
        for (int i = 0; i < n_options; i++) {
            if (i == selected) {
                wattron(options_win, A_REVERSE);
                mvwprintw(options_win, 8 + 6 * i, 7, "%s", options[i]);
                wattroff(options_win, A_REVERSE);
            } else {
                mvwprintw(options_win, 8 + 6 * i, 7, "%s", options[i]);
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
                    if (current_music == 1){
                        start_music("01. Main Menu.mp3");
                    } else if (current_music == 2) {
                        start_music("c418_-_aria_math.mp3");
                    } else if (current_music == 3) {
                        start_music("rymykhs_ahng_amng_as.mp3");
                    } else if (current_music == 4) {
                        start_music("bad-piggies-theme.mp3");
                    } else if (current_music == 5) {
                        stop_music("bad-piggies-theme.mp3");
                    }
                    clear();
                    refresh();
                    break;
                } 
                else if (selected == 1){
                    int character_setup = CHAR_DESIGN(height, width, players, game);
                    wrefresh(options_win);
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
        "TRACK 1: MAIN MENU THEME",
        "TRACK 2: ARIA MATH",
        "TRACK 3: AMONG US",
        "TRACK 4: BAD PIGGIES",
        "DISCONNECT"
    };
    int n_tracks = sizeof(music_tracks) / sizeof(music_tracks[0]);
    int selected = 0;
    int key;

    WINDOW *music_win = newwin(15, 40, (height - 15) / 2, (width - 40) / 2);
    box(music_win, 0, 0);

    while (1) {
        mvwprintw(music_win, 1, 8, "### MUSIC SELECTION ###");
        for (int i = 0; i < n_tracks; i++) {
            if (i == selected) {
                wattron(music_win, A_REVERSE);
                mvwprintw(music_win, 3 + 2 * i, 2, "%s", music_tracks[i]);
                wattroff(music_win, A_REVERSE);
            } else {
                mvwprintw(music_win, 3 + 2 * i, 2, "%s", music_tracks[i]);
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
            case 27:
                return 0;
        }
    }
}

int CHAR_DESIGN(int height, int width, Player player, Game *game){
    clear();
    refresh();
    WINDOW *ch_des = newwin(25, 60, (height - 25) / 2, (width - 60) / 2);
    char *colors[] = {"RED", "BLUE", "GREEN", "YELLOW", "WHITE", "CHARACTER:"};
    int num = sizeof(colors) / sizeof(colors[0]);
    int selected = 0;
    int key;

    box(ch_des, 0, 0);
    char character;
    while (1) {
        mvwprintw(ch_des, 1, 2, "CHARACTER DESIGN");
        for (int i = 0; i < num; i++) {
            if (i == selected) {
                wattron(ch_des, COLOR_PAIR(i + 1) | A_UNDERLINE); 
            } else {
                wattron(ch_des, COLOR_PAIR(i + 1));
            }
            mvwprintw(ch_des, 10, 2 + i * 8, "%s", colors[i]);
            wattroff(ch_des, COLOR_PAIR(i + 1) | A_UNDERLINE);
        }
        mvwprintw(ch_des, 21, 2, "PRESS ESC TO EXIT");
        wrefresh(ch_des);
        key = getch();
        switch (key) {
            case KEY_LEFT:
                selected--;
                if (selected < 0) {
                    selected = num - 1;
                }
                break;
            case KEY_RIGHT:
                selected++;
                if (selected >= num) {
                    selected = 0;
                }
                break;
            case '\n':          
                if (selected == 5){
                    echo();
                    while (1){
                        mvwprintw(ch_des, 10, 53, "   ");
                        wmove(ch_des, 10, 53);
                        curs_set(1);
                        character = wgetch(ch_des);
                        mvwprintw(ch_des, 12, 35, "CHARACTER CHOSEN: %c  ", character);
                        wrefresh(ch_des);
                        break;
                    }
                    noecho();
                    curs_set(0);
                }
                else if (selected == 0){
                    player.color = 11;
                }
                break;
            case 27: // ESC key
                werase(ch_des); // Erase window contents
                wrefresh(ch_des); // Refresh to reflect changes
                delwin(ch_des);   // Delete the window
                clear();          // Clear the main screen
                refresh(); 
                return 0;
                break;
        }
    }
}