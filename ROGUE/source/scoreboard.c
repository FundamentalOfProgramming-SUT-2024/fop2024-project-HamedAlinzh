#include <rogue.h>


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

    while (fscanf(scoreB, "%s %s %s %d", players[player_count].name, 
                  players[player_count].password, dummy, &players[player_count].score) == 4) {
        player_count++;
        if (player_count >= 100) {
            break;
        }
    }
    fclose(scoreB);
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
        mvwprintw(score_win, line, 13, "%-10s     %15d", players[i].name, players[i].score);
        wattroff(score_win, A_BOLD);
        wattroff(score_win, COLOR_PAIR(14));
        wrefresh(score_win);
        line += 2;
    }
    for (int i = 3; i < player_count && line < 18; i++) {
        mvwprintw(score_win, line, 13, "%-10s     %15d", players[i].name, players[i].score);
        wrefresh(score_win);
        line += 2;
    }
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


    mvwprintw(score_win, 38, 39, "Press Esc to return...");
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