#include "rogue.h"
playerG *playersetup(playerG *newplayer){
    // playerG *newplayer;
    // newplayer = (playerG*)malloc(sizeof(playerG));
    newplayer->pos = malloc(sizeof(Position));
    newplayer->selected_weapon = malloc(sizeof(Weapon));
    newplayer->selected_weapon->isthrowable = 0;
    for (int i = 0; i < 5; i++){
        newplayer->food[i] = NULL;
    }
    wchar_t macei[] = { L'\U00002692', L'\0' };
    newplayer->weapons[0] = malloc(sizeof(Weapon));
    newplayer->weapons[0]->damage = 5;
    newplayer->weapons[0]->type = 1;
    newplayer->weapons[0]->isthrowable = 0;
    newplayer->gold = 0;
    newplayer->xp = 0;
    newplayer->maxhealth = 25;
    newplayer->health = 25;
    newplayer->attack = 5;
    newplayer->food_num = 0;
    newplayer->weapons_num = 1;
    newplayer->hunger = 10;
    newplayer->maxhunger = 10;
    if(newplayer->symbol == '\0')
        newplayer->symbol = '@';
    
    return newplayer;
}

Position* user_input(int ch, Level* level){
    Position *newPosition = malloc(sizeof(Position));
    playerG *user = level->user;
    switch (ch){
            //up
        case 'W':
        case 'w':
        case '8':
            newPosition->y = user->pos->y - 1;
            newPosition->x = user->pos->x;
            break;
            //left
        case 'A':
        case 'a':
        case '4':
            newPosition->y = user->pos->y;
            newPosition->x = user->pos->x - 1;
            break;
            //down
        case 'S':
        case 's':
        case '2':
            newPosition->y = user->pos->y + 1;
            newPosition->x = user->pos->x;
            break;
            //right
        case 'D':
        case 'd':
        case '6':
            newPosition->y = user->pos->y;
            newPosition->x = user->pos->x + 1;
            break;
        case '7':
            newPosition->y = user->pos->y - 1;
            newPosition->x = user->pos->x - 1;
            break;
        case '9':
            newPosition->y = user->pos->y - 1;
            newPosition->x = user->pos->x + 1;
            break;
        case '1':
            newPosition->y = user->pos->y + 1;
            newPosition->x = user->pos->x - 1;
            break;
        case '3':
            newPosition->y = user->pos->y + 1;
            newPosition->x = user->pos->x + 1;
            break;
        case 'f':
        case 'F':
            int x = user->pos->x;
            int y = user->pos->y;            
            Position *pos = malloc(sizeof(Position));
            char chd = getch();
            if (chd == 'w' || chd == 'a' || chd == 's' || chd == 'd')
                fmovement(pos, x ,y, chd);
            newPosition->y = pos->y;
            newPosition->x = pos->x;
            break;
        case 'e':
        case 'E':
            backpack(level);
            clear();
            break;
        case 'i':
        case 'I':
            inventory(level);
            clear();
            break;
        case 'p':
        case 'P':
            potionbag(level);
            clear();
            break;
        case 'q':
        case 'Q':
            if (level->user->selected_weapon->isthrowable){
                int xw = user->pos->x;
                int yw = user->pos->y;   
                int ismonster = 0;         
                Position *posi = malloc(sizeof(Position));
                char chl = getch();
                if (chl != 'w' && chl != 'a' && chl != 's' && chl != 'd'){
                    break;
                }
                if (chl == 'w' || chl == 'a' || chl == 's' || chl == 'd' && chl != 'q'){
                    movementthrow(posi, xw ,yw, chl, level->user->selected_weapon->range, &ismonster);
                }
                if (ismonster){
                    combat(level->user, findmonst(posi, level->monsters), 2);
                    level->user->selected_weapon = level->user->weapons[0];
                    break;
                }
                level->user->selected_weapon->pos->y = posi->y;
                level->user->selected_weapon->pos->x = posi->x;
                level->user->selected_weapon->is_there = 1;
                level->user->selected_weapon = level->user->weapons[0];
            }
            
            break;
        case 'm':
        case 'M':
            Printlevelm(level);
            getch();
            clear();
            break;
        default:
            break;
    }
    return newPosition;
}

int playermove(Position *newpos, playerG *user){
    user->pos->y = newpos->y;
    user->pos->x = newpos->x;
}

void Printplayer(playerG *player){
    attron(COLOR_PAIR(player->color));
    mvprintw(player->pos->y, player->pos->x, "%c", player->symbol);
    attroff(COLOR_PAIR(player->color));
    move(player->pos->y, player->pos->x);
}

int checkposition(Position *newposition, Level *level, Game *game, playerG *player, char charrr) {
    cchar_t wc;
    playerG* user;
    user = level->user;
    if (mvwin_wch(stdscr, newposition->y, newposition->x, &wc) == ERR) {
        return -1;
    }

    switch (wc.chars[0]) {
        case L'.':
        case L'#':
        case L'+':
            if (level->countshaf %  20 == 0){
                if(user->hunger == 10){
                    if (user->health < user->maxhealth)
                        if (level->sabet == 1){
                            user->health += 2;
                            level->sabet = 0;
                        }
                        else {
                            user->health += 1;
                        }
                }
                level->countshaf = 1;
            }
            
            if (level->countHfood % 50 == 2){
                level->Hfood->is_there = 0;
                attron(COLOR_PAIR(11));
                mvprintw(48, 120, "                                     ");
                attroff(COLOR_PAIR(11));
                move(level->user->pos->y, level->user->pos->x);
            }
            if (level->speedcounter % 20 == 0){
                level->is_speed = 0;
                level->speedcounter = 0;
            }
            playermove(newposition, level->user);
            break;
        case L'\u269C':  // GOLD (⚜)
            consume_gold(level, findgold(newposition, level->golds));
            playermove(newposition, level->user);
            break;
        case L'\u269A':  // TALOYSIA (⚚)
            consume_taloysia(level, level->Taloysia);
            playermove(newposition, level->user);
            break;
        case 'B':
        case 'H':
        case 'R':
        case 'M':
            playermove(newposition, user);
            Printlevel(level);
            gamestats(level);
            attron(COLOR_PAIR(11));
            mvprintw(48, 110, "PRESS SPACE TO COLLECT");
            attroff(COLOR_PAIR(11));
            move(level->user->pos->y, level->user->pos->x);
            int c = getch();
            if (c == ' '){
                grabfood(level, findfood(newposition, level->foods));
                mvprintw(48, 110, "                              ");
                break;
            }
            else{
                mvprintw(48, 110, "                              ");
                break;
            }
        case L'\U0001F5E1':
        case L'\U00002020':
        case L'\U000027B3':
        case L'\U00002694':
            playermove(newposition, user);
            Printlevel(level);
            gamestats(level);
            attron(COLOR_PAIR(11));
            mvprintw(48, 110, "PRESS SPACE TO COLLECT ");
            attroff(COLOR_PAIR(11));
            move(level->user->pos->y, level->user->pos->x);
            int cha = getch();
            if (cha == ' '){
                grabweapon(level, findweapon(newposition, level->weapons));
                playermove(newposition, user);
                break;
            }
            else{
                mvprintw(48, 110, "                              ");
                break;
            }
        case L'\U00002623':
        case L'\U0000269B':
        case L'\U00002622':
            playermove(newposition, user);
            Printlevel(level);
            gamestats(level);
            attron(COLOR_PAIR(11));
            mvprintw(48, 110, "PRESS SPACE TO COLLECT");
            attroff(COLOR_PAIR(11));
            move(level->user->pos->y, level->user->pos->x);
            int chp = getch();
            if (chp == ' '){
                grabpotion(level, findpotion(newposition, level->potions));
                mvprintw(48, 110, "                              ");
                break;
            }
            else{
                mvprintw(48, 110, "                              ");
                break;
            }
        case '^':
            start_music("Apex_Legends_Main_Theme.mp3");
            battleroom(game);
            int ch = 'w';
            Position *position = player->pos;
            player->pos->y = game->levels[game->clevel]->battle_room->pos.y + 1;
            player->pos->x = game->levels[game->clevel]->battle_room->pos.x + 1;
            int a = game->levels[game->clevel]->battle_room->monsternum;
            int *x = &a;
            clear();
            while(player->health > 0 && *x > 0){
                gamestats(game->levels[game->clevel]);
                PrintBroom(game->levels[game->clevel]->battle_room);
                for (int i = 0; i < game->levels[game->clevel]->battle_room->monsternum; i++){
                    Printmonster(game->levels[game->clevel]->battle_room->monsters[i]);
                }
                Printplayer(player);
                ch = getch();
                if (ch != 'W' && ch != 'w' && ch != 'a' && ch != 'A' && ch != 'd' && ch != 'D' && ch != 's' && ch != 'S' && ch != 'e'
                    && ch != 'E' && ch != 'i' && ch != 'I' && ch != 'Q'&& ch != 'q' && ch != KEY_UP && ch != KEY_DOWN && ch != KEY_LEFT && ch != KEY_RIGHT && ch != '>' 
                    && ch != 27 && ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '6' && ch != '7' && ch != '8' && ch != '9' && ch != 'p' && ch != 'P' && ch != 'f' 
                    && ch != 'F'){
                    continue;
                }
                position = user_input(ch, game->levels[game->clevel]);
                
                movemonsterBR(game->levels[game->clevel]->battle_room, player);
                
                checkpositionBR(position, game->levels[game->clevel], game, player, x, x, x);
            }
            stop_music("Apex_Legends_Main_Theme.mp3");
            start_music("01. Main Menu.mp3");
            player->pos->y = game->levels[game->clevel]->trap->y;
            player->pos->x = game->levels[game->clevel]->trap->x;
            game->levels[game->clevel]->istrap = 0;
            break;
        case L'\U00002126':
            curs_set(0);
            mvprintw(48, 110, "Enter Treasure Room Password: ");
            refresh();

            char pass_input[20] = {0};
            int pass_idx = 0;
            int chpas;
            while ((chpas = getch()) != '\n' && chpas != '\r' && pass_idx < 19) {
                if (isdigit(chpas)) {
                    pass_input[pass_idx++] = chpas;
                    addch(chpas);
                    refresh();
                } else if (chpas == KEY_BACKSPACE || chpas == 127) {
                    if (pass_idx > 0) {
                        pass_idx--;
                        refresh();
                    }
                }
            }
            pass_input[pass_idx] = '\0';

            curs_set(1);
            int entered_pass = atoi(pass_input);
            if (entered_pass != game->levels[game->clevel]->password) {
                mvprintw(47, 110, "ACCESS DENIED!");
                refresh();
                getch();
                break;
            }
            curs_set(1);
            start_music("Apex_Legends_Main_Theme.mp3");
            treasureroom(game);
            int cht = 'w';
            Position *positionP = player->pos;
            player->pos->y = game->levels[game->clevel]->treasure_room->pos.y + 10;
            player->pos->x = game->levels[game->clevel]->treasure_room->pos.x + 10;
            int b = game->levels[game->clevel]->treasure_room->gold_num + game->levels[game->clevel]->treasure_room->taloysia_num;
            int *y = &b;
            clear();

            
            while(*y > 0){
                gamestats(game->levels[game->clevel]);
                PrintBroom(game->levels[game->clevel]->treasure_room);
                PrintgoldT(game->levels[game->clevel]->treasure_room);
                Printplayer(player);
                cht = getch();
                if (cht != 'W' && cht != 'w' && cht != 'a' && cht != 'A' && cht != 'd' && cht != 'D' && cht != 's' && cht != 'S' && cht != 'e'
                    && cht != 'E' && cht != 'i' && cht != 'I' && cht != 'Q'&& cht != 'q' && cht != KEY_UP && cht != KEY_DOWN && cht != KEY_LEFT && cht != KEY_RIGHT && cht != '>' 
                    && cht != 27 && cht != '1' && cht != '2' && cht != '3' && cht != '4' && cht != '6' && cht != '7' && cht != '8' && cht != '9' && cht != 'p' && cht != 'P' && cht != 'f' 
                    && cht != 'F'){
                    continue;
                }
                positionP = user_input(cht, game->levels[game->clevel]);
                
                checkpositionBR(positionP, game->levels[game->clevel], game, player, x, y, x);
            }

            stop_music("Apex_Legends_Main_Theme.mp3");
            start_music("01. Main Menu.mp3");
            return 4;
            break;
        case '?':
            potionroom(game);
            int chX = 'w';
            Position *positionPT = player->pos;
            player->pos->y = game->levels[game->clevel]->potion_room->pos.y + 2;
            player->pos->x = game->levels[game->clevel]->potion_room->pos.x + 2;
            int d = 3;
            int *z = &d;
            clear();
            while(*z > 0 && chX != 27){
                gamestats(game->levels[game->clevel]);
                PrintBroom(game->levels[game->clevel]->potion_room);
                PrintPotionT(game->levels[game->clevel]->potion_room);
                Printplayer(player);
                chX = getch();
                if (chX != 'W' && chX != 'w' && chX != 'a' && chX != 'A' && chX != 'd' && chX != 'D' && chX != 's' && chX != 'S' && chX != 'e'
                    && chX != 'E' && chX != 'i' && chX != 'I' && chX != 'Q'&& chX != 'q' && chX != KEY_UP && chX != KEY_DOWN && chX != KEY_LEFT && chX != KEY_RIGHT && chX != '>' 
                    && chX != 27 && chX != '1' && chX != '2' && chX != '3' && chX != '4' && chX != '6' && chX != '7' && chX != '8' && chX != '9' && chX != 'p' && chX != 'P' && chX != 'f' 
                    && chX != 'F'){
                    continue;
                }
                positionPT = user_input(chX, game->levels[game->clevel]);
                
                checkpositionBR(positionPT, game->levels[game->clevel], game, player, x, y, z);
            }
            player->pos->y = game->levels[game->clevel]->Pdoor->y;
            player->pos->x = game->levels[game->clevel]->Pdoor->x;
            game->levels[game->clevel]->isPdoor = 0;
            break;
        case 'S':
        case 'G':
        case 'D':
        case 'U':
        case 'F':
            combat(user, findmonst(newposition, level->monsters), 1);
            break;
        case '>':
            playermove(newposition, user);
            Printlevel(level);
            gamestats(level);
            attron(COLOR_PAIR(11));
            mvprintw(48, 110, "PRESS > TO GO TO THE NEXT LEVEL ");
            attroff(COLOR_PAIR(11));
            move(level->user->pos->y, level->user->pos->x);
            int chn = getch();
            if (chn == '>'){
                gotonextlevel(game, player);
                mvprintw(48, 110, "                                   ");
            }
            else {
                mvprintw(48, 110, "                                 ");
            }
            break;
        case '<':
            playermove(newposition, user);
            Printlevel(level);
            gamestats(level);
            attron(COLOR_PAIR(11));
            mvprintw(48, 110, "PRESS < TO GO TO THE PREVIOUS LEVEL ");
            attroff(COLOR_PAIR(11));
            move(level->user->pos->y, level->user->pos->x);
            int chr = getch();
            if (chr == '<'){
                gotopreviouslevel(game, player);    
                mvprintw(48, 110, "                                     ");
            }
            else {
                mvprintw(48, 110, "                                       ");
            }
            break;
        case '=':
            Position *pes = malloc(sizeof(Position));
            int yy = player->pos->y;
            int xx = player->pos->x;
            Printlevelm(level);
            int isthere = check_barriers_along_path(pes, newposition->x, newposition->y, charrr);

            if (isthere  == 1){
                int n = get_room_for_position(pes, level) ;
                level->rooms[n]->is_there = 1;
            }
            break;
        case '&':
            playermove(newposition, user);
            int randompass = rand() % 9000 + 1000;
            level->password = randompass;
            level->key->is_there = 0;
            attron(COLOR_PAIR(17));
            mvprintw(47, 110, "PASSWORD TO THE TREASURE ROOM IS %d", level->password);
            mvprintw(48, 110, "BE CAREFUL! YOU WILL SEE THE PASSWORD ONLY ONCE!");
            attroff(COLOR_PAIR(17));
            getch();

        default:
            break;
    }
}

bool is_traversable(char tile) {
    return (tile == '#' || tile == '.' || tile == '+');
}

bool is_traversablethrow(char tile) {
    return (tile == '.');
}

bool is_monster(char tile) {
    return (tile == 'D' || tile == 'F' || tile == 'G' || tile == 'U' || tile == 'S');
}


void fmovement(Position *pos, int x, int y, char dir) {
    pos->x = x;
    pos->y = y;

    int dx = 0, dy = 0;

    switch (dir) {
        case 'w': dy = -1; break;  // Up
        case 's': dy = 1; break;   // Down
        case 'a': dx = -1; break;  // Left
        case 'd': dx = 1; break;   // Right
        default: return;
    }
    int last_x = pos->x;
    int last_y = pos->y;
    while (true) {
        int new_x = pos->x + dx;
        int new_y = pos->y + dy;
        char tile = (char)mvwinch(stdscr, new_y, new_x) & A_CHARTEXT;
        if (!is_traversable(tile)) break;
        last_x = new_x;
        last_y = new_y;
        pos->x = new_x;
        pos->y = new_y;
    }
    pos->x = last_x;
    pos->y = last_y;
}

void movementthrow(Position *pos, int x, int y, char dir, int range, int* ismonster) {
    pos->x = x;
    pos->y = y;

    int dx = 0, dy = 0;

    switch (dir) {
        case 'w': dy = -1; break;  // Up
        case 's': dy = 1; break;   // Down
        case 'a': dx = -1; break;  // Left
        case 'd': dx = 1; break;   // Right
        default: return;
    }
    int last_x = pos->x;
    int last_y = pos->y;
    int count = range;
    while (count--) {
        int new_x = pos->x + dx;
        int new_y = pos->y + dy;
        char tile = (char)mvwinch(stdscr, new_y, new_x) & A_CHARTEXT;
        if (is_monster(tile)) {
            *ismonster = 1;
            return;
        }
        if (!is_traversablethrow(tile)) break;
        last_x = new_x;
        last_y = new_y;
        pos->x = new_x;
        pos->y = new_y;
    }
    pos->x = last_x;
    pos->y = last_y;
}

int check_barriers_along_path(Position *pos, int x, int y, char dir) {
    int dx = 0, dy = 0;
    switch(dir) {
        case 'a': dx = -1; break;
        case 'd': dx = 1; break;
        case 'w': dy = -1; break;
        case 's': dy = 1; break;
        default: return 0;
    }

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int current_x = x;
    int current_y = y;
    int found = 0;

    while (1) {
        current_x += dx;
        current_y += dy;
        if (current_x < 0 || current_x >= max_x || current_y < 0 || current_y >= max_y) {
            break;
        }
        char ch = mvinch(current_y, current_x);

        if (ch == '|' || ch == '-' || ch == '+') {
            pos->x = current_x;
            pos->y = current_y;
            found = 1;
            break;
        }
    }

    return found;
}
