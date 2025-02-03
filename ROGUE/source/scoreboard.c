#include <rogue.h>


int SCORE_BOARDV(int height, int width, Player players[], Game *game) {
    clear();
    refresh();
    FILE *scoreB = fopen("SCOREBOARD.txt", "r");
    if (!scoreB) {
        mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
        refresh();
        getch();
        return 1;
    }    
    char dummy[100];
    int player_count = 0;

    while (fscanf(scoreB, "%s %s %s %d %d", players[player_count].name, 
                  players[player_count].password, dummy, &players[player_count].score, &players[player_count].xp) == 5) {
        player_count++;
        if (player_count >= 100) {
            break;
        }
    }
    
    fclose(scoreB);
    int k = 0;
    while (k < player_count) {
        if (players[k].score == 0) {
            for (int j = k; j < player_count - 1; j++) {
                players[j] = players[j + 1];
            }
            player_count--;
        } else {
            k++;
        }
    }
    qsort(players, player_count, sizeof(Player), comparePlayers);
    WINDOW *score_win = newwin(40, 100, (height - 40) / 2, (width - 100) / 2);
    mvwprintw(score_win, 1, 2, "SCOREBOARD");
    wattron(score_win, COLOR_PAIR(11));
    box(score_win, 0, 0);
    mvwprintw(score_win, 5, 50, "                              ) ");  
    mvwprintw(score_win, 6, 50, "                           (\\/,\\");   
    mvwprintw(score_win, 7, 50, "                  ___,      )/(|");    
    mvwprintw(score_win, 8, 50, "                 /,===      \\\\//");    
    mvwprintw(score_win, 9, 50, "              ,==( \"|\"      (# )");    
    mvwprintw(score_win, 10, 50, "             ,==='\\_-/       :| ");    
    mvwprintw(score_win, 11, 50, "              ,---'  \\---.   || ");   
    mvwprintw(score_win, 12, 50, "             (     - -    )  |: ");    
    mvwprintw(score_win, 13, 50, "             |  \\_. '  _./\\ ,'/\\");      
    mvwprintw(score_win, 14, 50, "             |  )       / ,-||\\/");      
    mvwprintw(score_win, 15, 50, "   ___       ( < \\     (\\___/|| ");    
    mvwprintw(score_win, 16, 50, "  /   \\,----._\\ \\(   '  )    #; ");    
    mvwprintw(score_win, 17, 50, " (   /         \\|'',, ,'\\       ");   
    mvwprintw(score_win, 18, 50, " )   |          )\\   '   |      ");     
    mvwprintw(score_win, 19, 50, " (  (|     ,    \\_)      |      ");  
    mvwprintw(score_win, 20, 50, "  )  )\\     \\-.__\\   |_, /      ");   
    mvwprintw(score_win, 21, 50, "  ( (  \\    )  )  ]  |  (       ");  
    mvwprintw(score_win, 22, 50, "   ) ) _) _/ _/   /, )) /       ");   
    mvwprintw(score_win, 23, 50, "   (/  \\ <\\ \\      \\ |\\ |       ");   
    mvwprintw(score_win, 24, 50, "    ) ._) \\__\\_    ) | )(       ");  
    mvwprintw(score_win, 25, 50, "       )_,,\\ )_\\    )|<,_\\      ");   
    mvwprintw(score_win, 26, 50, "          )_\\      /_(  |_\\     ");   
    mvwprintw(score_win, 27, 50, "                    )_\\         ");      
    wattroff(score_win, COLOR_PAIR(11));
    wrefresh(score_win);
    int line = 3;
    wchar_t gaot[] = { L'\U0001F410', L'\0'};
    wchar_t crown[] = { L'\U0001F451', L'\0'};
    wchar_t ace[] = { L'\U0001F0A1', L'\0'};
    for (int i = 0; i < 3 && line < 18; i++) {
        wattron(score_win, COLOR_PAIR(14));
        wattron(score_win, A_BOLD);
        mvwprintw(score_win, line, 13, "%d  %-10s     %5d     %5d", ((line - 3) / 2) + 1, players[i].name, players[i].score, players[i].xp);
        wattroff(score_win, A_BOLD);
        wattroff(score_win, COLOR_PAIR(14));
        wrefresh(score_win);
        line += 2;
    }
    for (int i = 3; i < 7 && line < 18; i++) {
        mvwprintw(score_win, line, 13, "%-10s     %5d     %5d", players[i].name, players[i].score, players[i].xp);
        wrefresh(score_win);
        line += 2;
    }
    wrefresh(score_win);
    wattron(score_win, COLOR_PAIR(14));
    mvwprintw(score_win, 3, 2, "GOAT!");
    wattroff(score_win, COLOR_PAIR(14));
    wattron(score_win, COLOR_PAIR(13));
    mvwprintw(score_win, 5, 2, "KING!");
    wattron(score_win, COLOR_PAIR(13));
    wattron(score_win, COLOR_PAIR(11));
    mvwprintw(score_win, 7, 2, "LEGEND!");
    wattroff(score_win, COLOR_PAIR(11));
    mvwaddwstr(score_win, 3, 10, gaot);
    mvwaddwstr(score_win, 5, 10, crown);
    mvwaddwstr(score_win, 7, 10, ace);


    mvwprintw(score_win, 35, 10, "IF YOUR NAME IS MORE THAN ONE TIME ON THE BOARD, YOU HAVE PLAYED SEVERAL TIMES!");
    mvwprintw(score_win, 38, 39, "PRESS ESC TO EXIT...");
    mvwprintw(score_win, 38, 3, "PAGE 1");
    wrefresh(score_win);
    char ch;
    while (1){
        ch = getch();
        if (ch == 27){
            delwin(score_win);
            return 1;
        }
        if (ch == KEY_RIGHT){
            SCORE_BOARD(height, width, players, game);
        }
        else if (ch == KEY_LEFT){
            SCORE_BOARDL(height, width, players, game);
        }
    }
}

int SCORE_BOARD(int height, int width, Player players[], Game *game) {
    clear();
    refresh();
    FILE *scoreB = fopen("SCOREBOARD.txt", "r");
    if (!scoreB) {
        mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
        refresh();
        getch();
        return 1;
    }    
    char dummy[100];
    int player_count = 0;

    while (fscanf(scoreB, "%s %s %s %d %d", players[player_count].name, 
                  players[player_count].password, dummy, &players[player_count].score, &players[player_count].xp) == 5) {
        player_count++;
        if (player_count >= 100) break;
    }
    fclose(scoreB);

    int k = 0;
    while (k < player_count) {
        if (players[k].score == 0) {
            for (int j = k; j < player_count - 1; j++) players[j] = players[j + 1];
            player_count--;
        } else k++;
    }
    qsort(players, player_count, sizeof(Player), comparePlayers);

    WINDOW *score_win = newwin(40, 100, (height - 40) / 2, (width - 100) / 2);
    keypad(score_win, TRUE);
    int current_page = 0;
    const int players_per_page = 7;
    int max_page = (player_count + players_per_page - 1) / players_per_page - 1;

    char ch;
    do {
        werase(score_win);
        wattron(score_win, COLOR_PAIR(11));
        box(score_win, 0, 0);
        mvwprintw(score_win, 1, 2, "SCOREBOARD");
        wattron(score_win, COLOR_PAIR(11));
        box(score_win, 0, 0);
        mvwprintw(score_win, 5, 50, "                              ) ");  
        mvwprintw(score_win, 6, 50, "                           (\\/,\\");   
        mvwprintw(score_win, 7, 50, "                  ___,      )/(|");    
        mvwprintw(score_win, 8, 50, "                 /,===      \\\\//");    
        mvwprintw(score_win, 9, 50, "              ,==( \"|\"      (# )");    
        mvwprintw(score_win, 10, 50, "             ,==='\\_-/       :| ");    
        mvwprintw(score_win, 11, 50, "              ,---'  \\---.   || ");   
        mvwprintw(score_win, 12, 50, "             (     - -    )  |: ");    
        mvwprintw(score_win, 13, 50, "             |  \\_. '  _./\\ ,'/\\");      
        mvwprintw(score_win, 14, 50, "             |  )       / ,-||\\/");      
        mvwprintw(score_win, 15, 50, "   ___       ( < \\     (\\___/|| ");    
        mvwprintw(score_win, 16, 50, "  /   \\,----._\\ \\(   '  )    #; ");    
        mvwprintw(score_win, 17, 50, " (   /         \\|'',, ,'\\       ");   
        mvwprintw(score_win, 18, 50, " )   |          )\\   '   |      ");     
        mvwprintw(score_win, 19, 50, " (  (|     ,    \\_)      |      ");  
        mvwprintw(score_win, 20, 50, "  )  )\\     \\-.__\\   |_, /      ");   
        mvwprintw(score_win, 21, 50, "  ( (  \\    )  )  ]  |  (       ");  
        mvwprintw(score_win, 22, 50, "   ) ) _) _/ _/   /, )) /       ");   
        mvwprintw(score_win, 23, 50, "   (/  \\ <\\ \\      \\ |\\ |       ");   
        mvwprintw(score_win, 24, 50, "    ) ._) \\__\\_    ) | )(       ");  
        mvwprintw(score_win, 25, 50, "       )_,,\\ )_\\    )|<,_\\      ");   
        mvwprintw(score_win, 26, 50, "          )_\\      /_(  |_\\     ");   
        mvwprintw(score_win, 27, 50, "                    )_\\         ");      
        wattroff(score_win, COLOR_PAIR(11));
        wrefresh(score_win);
        int start = current_page * players_per_page;
        int line = 3;
        if (current_page == 0){
            wchar_t gaot[] = { L'\U0001F410', L'\0'};
            wchar_t crown[] = { L'\U0001F451', L'\0'};
            wchar_t ace[] = { L'\U0001F0A1', L'\0'};
            wrefresh(score_win);
            wattron(score_win, COLOR_PAIR(14));
            mvwprintw(score_win, 3, 2, "GOAT!");
            wattroff(score_win, COLOR_PAIR(14));
            wattron(score_win, COLOR_PAIR(13));
            mvwprintw(score_win, 5, 2, "KING!");
            wattron(score_win, COLOR_PAIR(13));
            wattron(score_win, COLOR_PAIR(11));
            mvwprintw(score_win, 7, 2, "LEGEND!");
            wattroff(score_win, COLOR_PAIR(11));
            mvwaddwstr(score_win, 3, 10, gaot);
            mvwaddwstr(score_win, 5, 10, crown);
            mvwaddwstr(score_win, 7, 10, ace);
        }

        for (int i = start; i < start + players_per_page && i < player_count; i++) {
            if (i < 3) { // Top 3 of the page
                wattron(score_win, COLOR_PAIR(14) | A_BOLD);
            } else {
                wattroff(score_win, COLOR_PAIR(14) | A_BOLD);
            }

            mvwprintw(score_win, line, 13, "%d  %-10s     %5d     %5d", 
                     i + 1, players[i].name, players[i].score, players[i].xp);
            line += 2;
        }

        mvwprintw(score_win, 38, 3, "PAGE %d/%d", current_page + 1, max_page + 1);
        mvwprintw(score_win, 38, 39, "PRESS ESC TO EXIT...");
        wrefresh(score_win);

        ch = wgetch(score_win);
        if (ch == 'd' && current_page < max_page) current_page++;
        else if (ch == 'a' && current_page > 0) current_page--;
    } while (ch != 27);

    delwin(score_win);
    return 1;
}

int comparePlayers(const void *a, const void *b) {
    Player *playerA = (Player *)a;
    Player *playerB = (Player *)b;
    if (playerA->score == 0){
        playerA->score = 0;
    }
    if (playerB->score == 0){
        playerB->score = 0;
    }
    return playerB->score - playerA->score;
}