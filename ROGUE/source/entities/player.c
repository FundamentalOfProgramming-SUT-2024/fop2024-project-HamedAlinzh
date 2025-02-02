#include "rogue.h"
playerG *playersetup(){
    playerG *newplayer;
    newplayer = (playerG*)malloc(sizeof(playerG));
    newplayer->pos = malloc(sizeof(Position));
    newplayer->selected_weapon = malloc(sizeof(Weapon));
    for (int i = 0; i < 5; i++){
        newplayer->food[i] = NULL;
    }
    wchar_t macei[] = { L'\U00002692', L'\0' };
    newplayer->weapons[0] = malloc(sizeof(Weapon));
    newplayer->weapons[0]->damage = 5;
    newplayer->weapons[0]->type = 1;
    newplayer->gold = 0;
    newplayer->xp = 0;
    newplayer->maxhealth = 25;
    newplayer->health = 25;
    newplayer->attack = 5;
    newplayer->food_num = 0;
    newplayer->weapons_num = 1;
    newplayer->hunger = 10;
    newplayer->maxhunger = 10;
    newplayer->symbol = '$';
    newplayer->color = 15;
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
            int x = newPosition->x;
            int y = newPosition->y;            
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
            int direction;
            direction = getch();
            switch (direction){
                case KEY_UP:
                    throwweapon(level->user, throwfindmonster(level->user, level->monsters, 0), level->user->selected_weapon, 0);
                    break;
                // case KEY_RIGHT:
                //     throwweapon(level->user, level->monsters, level->user->selected_weapon, 1);
                //     break;
                // case KEY_DOWN:
                //     throwweapon(level->user, level->monsters, level->user->selected_weapon, 2);
                //     break;
                // case KEY_LEFT:
                //     throwweapon(level->user, level->monsters, level->user->selected_weapon, 3);
                //     break;
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
    // attron(COLOR_PAIR(13));
    mvprintw(player->pos->y, player->pos->x, "%c", player->symbol);
    // attroff(COLOR_PAIR(13));
    move(player->pos->y, player->pos->x);
}

int checkposition(Position *newposition, Level *level, Game *game, playerG *player) {
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
                level->countshaf = 0;
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
            start_music("66. The Final Battle.mp3");
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
                
                checkpositionBR(position, game->levels[game->clevel], game, player, x, x);
            }
            stop_music("66. The Final Battle.mp3");
            start_music("01. Main Menu.mp3");
            player->pos->y = game->levels[game->clevel]->trap->y;
            player->pos->x = game->levels[game->clevel]->trap->x;
            game->levels[game->clevel]->istrap = 0;
            break;
        case L'\U00002126':
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
                    && cht != 27 && ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '6' && ch != '7' && ch != '8' && ch != '9' && ch != 'p' && ch != 'P' && ch != 'f' 
                    && ch != 'F'){
                    continue;
                }
                positionP = user_input(cht, game->levels[game->clevel]);
                
                checkpositionBR(positionP, game->levels[game->clevel], game, player, x, y);
            }
            stop_music("Apex_Legends_Main_Theme.mp3");
            start_music("01. Main Menu.mp3");
            return 4;
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
                mvprintw(48, 110, "                              ");
            }
            break;
        case '<':
            playermove(newposition, user);
            Printlevel(level);
            gamestats(level);
            attron(COLOR_PAIR(1));
            mvprintw(48, 110, "PRESS < TO COLLECT ");
            attroff(COLOR_PAIR(1));
            move(level->user->pos->y, level->user->pos->x);
            int chr = getch();
            if (chr == '<'){
                gotopreviouslevel(game, player);    
                mvprintw(48, 110, "                              ");
            }
            else {
                mvprintw(48, 110, "                              ");
            }
            break;
            break;
        default:
            break;
    }
}

bool is_traversable(char tile) {
    return (tile == '#' || tile == '.' || tile == '+');
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
        default: return;           // Invalid direction
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