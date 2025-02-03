#include <rogue.h>


int start_menu(int height, int width, Player players[], Game *game){
    clear();
    refresh();
    char *options[] = {" PLAY AS A GUEST ", "    NEW PLAYER    ", "      LOGIN      ", "BACK TO MAIN MENU"};
    int num = sizeof(options) / sizeof(options[0]);
    int selected = 0;
    int key;
    WINDOW *start_menu = newwin(40, 120, (height - 40) / 2, (width - 120) / 2);
    mvwprintw(start_menu, 2, 52, "  ### START MENU ###  ");
    wattron(start_menu, COLOR_PAIR(13));
    mvwprintw(start_menu, 4, 40, "                            ==(W{==========-      /===-                        ");
    mvwprintw(start_menu, 5, 40, "                              ||  (.--.)         /===-_---~~~~~~~~~------____  ");
    mvwprintw(start_menu, 6, 40, "                              | \\_,|**|,__      |===-~___                _,-' `");
    mvwprintw(start_menu, 7, 40, "                 -==\\\\        `\\ ' `--'   ),    `//~\\\\   ~~~~`---.___.-~~      ");
    mvwprintw(start_menu, 8, 40, "             ______-==|        /`\\_. .__/\\ \\    | |  \\\\           _-~`         ");
    mvwprintw(start_menu, 9, 40, "       __--~~~  ,-/-==\\\\      (   | .  |~~~~|   | |   `\\        ,'             ");
    mvwprintw(start_menu, 10, 40, "    _-~       /'    |  \\\\     )__/==0==-\\<>/   / /      \\      /               ");
    mvwprintw(start_menu, 11, 40, "  .'        /       |   \\\\      /~\\___/~~\\/  /' /        \\   /'                ");
    mvwprintw(start_menu, 12, 40, " /  ____  /         |    \\`\\.__/-~~   \\  |_/'  /          \\/'                  ");
    mvwprintw(start_menu, 13, 40, "/-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~`                   ");
    mvwprintw(start_menu, 14, 40, "                  \\_|      /        _) | ;  ),   __--~~                        ");
    mvwprintw(start_menu, 15, 40, "                    '~~--_/      _-~/- |/ \\   '-~ \\                            ");
    mvwprintw(start_menu, 16, 40, "                   {\\__--_/}    / \\\\_>-|)<__\\      \\                           ");
    mvwprintw(start_menu, 17, 40, "                   /'   (_/  _-~  | |__>--<__|      |                          ");
    mvwprintw(start_menu, 18, 40, "                  |o-o /) )-~     | |__>--<__|      |                          ");
    mvwprintw(start_menu, 19, 40, "                  / /~ ,_/       / /__>---<__/      |                          ");
    mvwprintw(start_menu, 19, 40, "                  (- _//)       /-~_>---<__-~      /                           ");
    mvwprintw(start_menu, 20, 40, "                 (^(~          /~_>---<__-      _-~                            ");
    mvwprintw(start_menu, 21, 40, "                ,/|           /__>--<__/     _-~                               ");
    mvwprintw(start_menu, 22, 40, "             ,//('(          |__>--<__|     /  -               .----_          ");
    mvwprintw(start_menu, 23, 40, "            ( ( '))          |__>--<__|    |                 /' _---_~\\        ");
    mvwprintw(start_menu, 24, 40, "         `-)) )) (           |__>--<__|    |               /'  /     ~\\`\\      ");
    mvwprintw(start_menu, 25, 40, "        ,/,'//( (             \\__>--<__\\    \\            /'  //        ||      ");
    mvwprintw(start_menu, 26, 40, "      ,( ( ((, ))              ~-__>--<_~-_  ~--____---~' _/'/        /'       ");
    mvwprintw(start_menu, 27, 40, "    `~/  )` ) ,/|                 ~-_~>--<_/-__       __-~ _/                  ");
    mvwprintw(start_menu, 28, 40, "  ._-~//( )/ )) `                    ~~-'_/_/ /~~~~~~~__--~                    ");
    mvwprintw(start_menu, 29, 40, "   ;'( ')/ ,)(                              ~~~~~~~~~~                         ");
    mvwprintw(start_menu, 30, 40, "  ' ') '( (/                                                                   ");
    mvwprintw(start_menu, 31, 40, "    '   '  `                                                                   ");
    wattroff(start_menu, COLOR_PAIR(13));
    while (1){
        wrefresh(start_menu);
        box(start_menu, 0, 0);
        for (int i = 0; i < num; i++) {
            if (i == selected) {
                wattron(start_menu, A_REVERSE);
                mvwprintw(start_menu, 8 + 7 * i, 10, "%s", options[i]);
                wattroff(start_menu, A_REVERSE);
            } else {
                mvwprintw(start_menu, 8 + 7 * i, 10, "%s", options[i]);
            }
        }
        wrefresh(start_menu);
        key = getch();
        switch (key) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = num - 1;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= num) selected = 0;
                break;
            case '\n': 
                if (selected == 0){ //! FILL!!!!
                    curs_set(1);
                    game->guest = 1;
                    start(game, game->player);
                    clear();
                    curs_set(0);
                    refresh();
                }
                else if (selected == 1){
                    new_player(height, width, players, game);
                    continue;
                    // wrefresh(start_menu);
                }
                else if (selected == 2){
                    login(height, width, players, game);
                    continue;
                }
                else if (selected == 3){
                    return 0;
                    break;
                }
        }
    }
}
// int login(int height, int width, Player players[], Game *game) {
//     clear();
//     refresh();
//     FILE *player_data = fopen("SCOREBOARD.txt", "r"); // Open file in read mode
//     if (!player_data) {
//         mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
//         refresh();
//         getch();
//         return 1;
//     }

//     int player_count = 0;
//     while (fscanf(player_data, " %s %s", players[player_count].name, players[player_count].password) == 2) {
//         player_count++;
//         if (player_count >= 100) {
//             break;
//         }
//     }
//     fclose(player_data);

//     char *options[] = {"ENTER THE GAME", "USERNAME:", "PASSWORD:", "BACK"};
//     int num = sizeof(options) / sizeof(options[0]);
//     int selected = 0;
//     int key;
//     char pass[40] = {0};
//     char user[40] = {0};
//     int user_index = -1;
//     int canpass = 0;

//     WINDOW *login_win = newwin(30, 80, (height - 30) / 2, (width - 80) / 2);
//     while (1) {
//         wrefresh(login_win);
//         box(login_win, 0, 0);
//         for (int i = 0; i < num; i++) {
//             if (i == selected) {
//                 wattron(login_win, A_REVERSE);
//                 mvwprintw(login_win, 3 + 7 * i, 12, "%s", options[i]);
//                 wattroff(login_win, A_REVERSE);
//             } else {
//                 mvwprintw(login_win, 3 + 7 * i, 12, "%s", options[i]);
//             }
//         }
//         wrefresh(login_win);
//         key = getch();
//         switch (key) {
//             case KEY_UP:
//                 selected--;
//                 if (selected < 0) selected = num - 1;
//                 break;
//             case KEY_DOWN:
//                 selected++;
//                 if (selected >= num) selected = 0;
//                 break;
//             case '\n':
//                 if (selected == 1) {
//                     mvwprintw(login_win, 10, 22, "                     ");
//                     curs_set(1);
//                     echo();
//                     wmove(login_win, 10, 22);
//                     wrefresh(login_win);
//                     wgetnstr(login_win, user, sizeof(user) - 1);

//                     user_index = -1;
//                     for (int i = 0; i < player_count; i++) {
//                         if (strcmp(players[i].name, user) == 0) {
//                             user_index = i;
//                             break;
//                         }
//                     }

//                     if (user_index == -1) {
//                         mvwprintw(login_win, 12, 22, "USERNAME NOT FOUND");
//                         mvwprintw(login_win, 10, 22, "                     ");
//                         wrefresh(login_win);
//                     } else {
//                         mvwprintw(login_win, 12, 22, "                             ");
//                         wrefresh(login_win);
//                         strcpy(game->player->name, user);
//                     }
//                     curs_set(0);
//                     noecho();
//                 } else if (selected == 2) {
//                     if (user_index == -1) {
//                         mvwprintw(login_win, 20, 22, "ENTER A VALID USERNAME FIRST!");
//                         wrefresh(login_win);
//                         continue;
//                     }

//                     mvwprintw(login_win, 17, 22, "                     ");
//                     curs_set(1);
//                     echo();
//                     wmove(login_win, 17, 22);
//                     wrefresh(login_win);
//                     wgetnstr(login_win, pass, sizeof(pass) - 1);

//                     if (strcmp(players[user_index].password, pass) == 0) {
//                         mvwprintw(login_win, 20, 22, "                                     ");
//                         wrefresh(login_win);
//                         strcpy(game->player->password, pass);
//                         canpass = 1;
//                     } else {
//                         mvwprintw(login_win, 20, 22, "PASSWORD IS WRONG! TRY AGAIN");
//                         wrefresh(login_win);
//                     }
//                     curs_set(0);
//                     noecho();
//                 } else if (selected == 3) {
//                     delwin(login_win);
//                     return 0; // Back to previous menu
//                 } else if (selected == 0){
//                     if (canpass){
//                         curs_set(1);
//                         start(game, game->player);
//                         clear();
//                         curs_set(0);
//                         refresh();
//                     }
//                 }
//                 break;
//         }
//     }
// }

int login(int height, int width, Player players[], Game *game) {
    clear();
    refresh();
    FILE *player_data = fopen("SCOREBOARD.txt", "r"); // Open file in read mode
    if (!player_data) {
        mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
        refresh();
        getch();
        return 1;
    }

    int player_count = 0;
    while (fscanf(player_data, " %s %s %s %d %d", 
                  players[player_count].name, 
                  players[player_count].password, 
                  players[player_count].email, 
                  &players[player_count].score, 
                  &players[player_count].xp) == 5) {
        player_count++;
        if (player_count >= 100) {
            break;
        }
    }
    fclose(player_data);

    // Now the login code works as expected.
    char *options[] = {"ENTER THE GAME", "USERNAME:", "PASSWORD:", "BACK"};
    int num = sizeof(options) / sizeof(options[0]);
    int selected = 0;
    int key;
    char pass[40] = {0};
    char user[40] = {0};
    int user_index = -1;
    int canpass = 0;

    WINDOW *login_win = newwin(30, 80, (height - 30) / 2, (width - 80) / 2);
    mvwprintw(login_win, 28, 40, "PRESS F IF YOU FORGET YOUR PASSWORD!");
    while (1) {
        wrefresh(login_win);
        box(login_win, 0, 0);
        for (int i = 0; i < num; i++) {
            if (i == selected) {
                wattron(login_win, A_REVERSE);
                mvwprintw(login_win, 3 + 7 * i, 12, "%s", options[i]);
                wattroff(login_win, A_REVERSE);
            } else {
                mvwprintw(login_win, 3 + 7 * i, 12, "%s", options[i]);
            }
        }
        wrefresh(login_win);
        key = getch();
        switch (key) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = num - 1;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= num) selected = 0;
                break;
            case '\n':
                if (selected == 1) {
                    mvwprintw(login_win, 10, 22, "                     ");
                    curs_set(1);
                    echo();
                    wmove(login_win, 10, 22);
                    wrefresh(login_win);
                    wgetnstr(login_win, user, sizeof(user) - 1);

                    user_index = -1;
                    for (int i = 0; i < player_count; i++) {
                        if (strcmp(players[i].name, user) == 0) {
                            user_index = i;
                            break;
                        }
                    }

                    if (user_index == -1) {
                        mvwprintw(login_win, 12, 22, "USERNAME NOT FOUND");
                        mvwprintw(login_win, 10, 22, "                     ");
                        wrefresh(login_win);
                    } else {
                        mvwprintw(login_win, 12, 22, "                             ");
                        wrefresh(login_win);
                        strcpy(game->player->name, user);
                        mvwprintw(login_win, 26, 40, "                                    ");
                    }
                    curs_set(0);
                    noecho();
                } else if (selected == 2) {
                    if (user_index == -1) {
                        mvwprintw(login_win, 20, 22, "ENTER A VALID USERNAME FIRST!");
                        wrefresh(login_win);
                        continue;
                    }

                    mvwprintw(login_win, 17, 22, "                     ");
                    curs_set(1);
                    echo();
                    wmove(login_win, 17, 22);
                    wrefresh(login_win);
                    wgetnstr(login_win, pass, sizeof(pass) - 1);

                    if (strcmp(players[user_index].password, pass) == 0) {
                        mvwprintw(login_win, 20, 22, "                                     ");
                        wrefresh(login_win);
                        strcpy(game->player->password, pass);
                        canpass = 1;
                    } else {
                        mvwprintw(login_win, 20, 22, "PASSWORD IS WRONG! TRY AGAIN");
                        wrefresh(login_win);
                    }
                    curs_set(0);
                    noecho();
                } else if (selected == 3) {
                    delwin(login_win);
                    return 0;
                } else if (selected == 0){
                    if (canpass){
                        curs_set(1);
                        game->guest = 0;
                        start(game, game->player);
                        clear();
                        curs_set(0);
                        refresh();
                    }
                }
                break;
            case 'f':
            case 'F':
                if (user_index != -1){
                    mvwprintw(login_win, 26, 40, "YOUR PASSWORD IS: %s", players[user_index].password);
                }

        }
    }
}


int load_players(Player players[], const char *filename, Game* game) {
    FILE *file = fopen("SCOREBOARD.txt", "r");
    if (!file) {
        printf("Error: Could not open file %s.\n", filename);
        return 0; 
    }

    int count = 0;
    while (count < 20 && fscanf(file, "%s %s %s %d %d %c", 
            players[count].name, 
            players[count].password, 
            players[count].email, 
            &players[count].score, 
            &players[count].color, 
            &players[count].character) == 6) {
        count++;
    }

    fclose(file);
    return count;
}

int new_player(int height, int width, Player players[], Game *game) {
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
        mvwprintw(new_player_win, 16, 14, "PASSWORD MUST HAVE AT LEAST 7 CHARACTERS!");
        mvwprintw(new_player_win, 18, 14, "YOU HAVE TO USE AT LEAST 1 UPPERCASE AND 1 LOWERCASE!");
        mvwprintw(new_player_win, 20, 14, "(PRESS R TO GENERATE RANDOM PASSWORD) ");
        mvwprintw(new_player_win, 1, 52, "PRESS S TO SAVE!");
        mvwprintw(new_player_win, 28, 30, "PRESS ESC TO RETURN...");
        for (int i = 0; i < n_options; i++) {
            if (i == selected) {
                wattron(new_player_win, A_REVERSE);
                mvwprintw(new_player_win, 5 + 9 * i, 2, "%s", info[i]);
                wattroff(new_player_win, A_REVERSE);
            } else {
                mvwprintw(new_player_win, 5 + 9 * i, 2, "%s", info[i]);
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
                    mvwprintw(new_player_win, 5, 14, "                 ");
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
                    mvwprintw(new_player_win, 14, 14, "                              "); 
                    curs_set(1);
                    while (1){
                        wmove(new_player_win, 14, 14); 
                        wrefresh(new_player_win);
                        wgetnstr(new_player_win, PASSWORD, sizeof(PASSWORD) - 1);
                        if (strlen(PASSWORD) < 7){
                            mvwprintw(new_player_win, 14, 14, "                         ");
                            mvwprintw(new_player_win, 12, 14, "INVALID PASSWORD!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 12, 14);
                            break;
                        }
                        else if (checkpass(PASSWORD) == 0){
                            mvwprintw(new_player_win, 14, 14, "                        ");
                            mvwprintw(new_player_win, 12, 14, "INVALID PASSWORD!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 14, 14);
                            break;
                        }
                        else {
                                mvwprintw(new_player_win, 12, 14, "                                                     ");
                                wrefresh(new_player_win);
                                break; 
                        }
                    }
                    curs_set(0);
                } else if (selected == 2) { 
                    mvwprintw(new_player_win, 23, 14, "                                                ");
                    curs_set(1);
                    while (1){
                        wmove(new_player_win, 23, 14); 
                        wrefresh(new_player_win);
                        wgetnstr(new_player_win, EMAIL, sizeof(EMAIL) - 1);
                        if (isValidEmail(EMAIL) == 0){
                            mvwprintw(new_player_win, 23, 14, "                     ");
                            mvwprintw(new_player_win, 25, 14, "INVALID EMAIL FORMAT!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 23, 14);
                            break;
                        }
                        else{
                            // mvwprintw(new_player_win, 23, 14, "                                        ");
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
                    char *random_pass = (char*)malloc(20 * sizeof(char));
                    random_pass = randompass();
                    strcpy(PASSWORD, random_pass);
                    mvwprintw(new_player_win, 14, 14, "                              ");
                    mvwprintw(new_player_win, 14, 14, "%s", PASSWORD);
                    wrefresh(new_player_win);
                }
                break;
            case 'S':
            case 's':
                if (strlen(USERNAME) > 0 && strlen(PASSWORD) > 0 && strlen(EMAIL) > 0 && isValidEmail(EMAIL) == 1 && checkpass(PASSWORD) == 1 && strlen(PASSWORD) > 6) {
                    fprintf(player_data, "%s %s %s 0 0", USERNAME, PASSWORD, EMAIL);
                    fflush(player_data);
                    fclose(player_data);
                    delwin(new_player_win);
                    return 0;
                } else {
                    mvwprintw(new_player_win, 25, 2, "ALL FIELDS MUST BE FILLED CORRECTLY!");
                    wrefresh(new_player_win);
                }
                break;
            case 27:
                delwin(new_player_win);
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
char *randompass(){
    srand(time(0));
    int a = rand() % 5 + 7;
    char *password = (char*)malloc(a * sizeof(char));
    char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    int hasU = 0, hasL = 0;
    for (int i = 0; i < a; i++){
        int choice = rand() % 3;  // Choose character category
        switch (choice) {
            case 0:
                password[i] = lower[rand() % strlen(lower)];
                hasL = 1;
                break;
            case 1:
                password[i] = upper[rand() % strlen(upper)];
                hasU = 1;
                break;
            case 2:
                password[i] = digits[rand() % strlen(digits)];
                break;
        }
    }
    int x = rand() % a;
    int y = rand() % a;
    if (x == y){
        x--;
    }
    if (hasL == 0){
        password[x] = lower[rand() % strlen(lower)];
        hasL = 1;
    }
    if (hasU == 0){
        password[y] = upper[rand() % strlen(upper)];
        hasU = 1;
    }
    password[a] = '\0';
    return password;
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
