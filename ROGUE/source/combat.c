#include <rogue.h>


int combat(playerG* player, Monster* monster, int ord){
    if (ord == 1){
        int a = rand() % 3;
        if (a != 0){
        monster->health -= player->attack;
        // attron(COLOR_PAIR(21));
        mvprintw(48, 95, "YOU DAMAGED THE MONSTER!");
        move(player->pos->y, player->pos->x);
        // attroff(COLOR_PAIR(21));
        // getch();
        }
        if (monster->health > 0){
            int b = rand() % 2;
            if (b == 0){
                player->health -= monster->attack;
                // attron(COLOR_PAIR(21));
                mvprintw(48, 95, "PLAYER WAS DAMAGED!");
                move(player->pos->y, player->pos->x);
                // attroff(COLOR_PAIR(21));
                // getch();
            }
        }
        else {
            mvprintw(monster->pos->y, monster->pos->x, ".");
            player->xp += 1;
            player->hunger--;
            // attron(COLOR_PAIR(21));
            mvprintw(48, 95, "MONSTER KILLED!");
            move(player->pos->y, player->pos->x);
            // attroff(COLOR_PAIR(21));
            // getch();
            return 1;
        }
    }
    else {
        player->health -= monster->attack;
        if (player->health > 0){
            monster->health -= player->attack;
        }
        else 
            mvprintw(1, 1,"%d", player->health);
    }
    return 1;
}

int combatBR(playerG* player, Monster* monster, int ord, int* x){
    if (ord == 1){
        monster->health -= player->attack;
        if (monster->health > 0){
            player->health -= monster->attack;
        }
        else {
            mvprintw(monster->pos->y, monster->pos->x, ".");
            *x -= 1;
            player->xp += 1;
            player->hunger--;
        }
    }
    else {
        player->health -= monster->attack;
        if (player->health > 0){
            monster->health -= player->attack;
        }
        else 
            mvprintw(1, 1,"%d", player->health);
    }
    return 1;
}

int throwweapon(playerG* player, Monster* monster, Weapon *weapon, int direction){
    switch (weapon->type)
    {
    case 2:  // Dagger
        monster->health -= weapon->damage;
        break;
    case 3: // Magic staff
        break;
    case 4: // Arrow
        break;
    case 1:
        break;
    case 0:
        break;
    }
}



int checkpositionBR(Position *newposition, Level *level, Game *game, playerG *player, int *x, int *y) {
    cchar_t wc;
    playerG* user;
    user = level->user;
    if (mvwin_wch(stdscr, newposition->y, newposition->x, &wc) == ERR) {
        return -1;  // Invalid position
    }

    switch (wc.chars[0]) {
        case '.':
        case '#':
        case '+':
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
        case L'\u269C': // GOLD
            consume_goldT(level, findgoldT(newposition, level->treasure_room->gold, level->treasure_room->gold_num), y);
            playermove(newposition, user);
            break;
        case L'\u269A':
            consume_taloysiaT(level, findgoldT(newposition, level->treasure_room->taloysia, level->treasure_room->taloysia_num), y);
            playermove(newposition, user);
            break;
        case 'S':
        case 'G':
        case 'D':
        case 'U':
        case 'F':
            combatBR(user, findmonstBR(newposition, level->battle_room->monsters, level->battle_room->monsternum), 1, x);
            break;
        default:
            break;
    }
}