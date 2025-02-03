#include "rogue.h"

int addmonsters(Level *level, Game *game){
    level->monsters = malloc(sizeof(Monster *) * 6);
    level->monsternum = 0;
    for (int x = 0; x < level->roomnum; x++){
        if ((rand() % 3) >= (3 - game->dificulty)){
            level->monsters[level->monsternum] = selectMonster(level->level, x);
            SetStartPos(level->monsters[level->monsternum], level->rooms[x]);
            level->monsternum++;
        }
    }
}

int addmonsterBR(Room *room){
    room->monsters = malloc(sizeof(Monster *) * 20);
    // room->monsternum = rand() % 5 + 5;
    room->monsternum = 7; 
    for (int i = 0; i < room->monsternum; i++){
        room->monsters[i] = selectMonster(2, 10);
        SetStartPos(room->monsters[i], room);
    }
}

int movemonsterBR(Room *room, playerG * user){
    for (int x = 0; x < room->monsternum; x++){
        if (room->monsters[x]->health <= 0){
            continue;
        }
        mvprintw(room->monsters[x]->pos->y, room->monsters[x]->pos->x, ".");
        if (room->monsters[x]->pathfinding == 1){// random
            pathrand(room->monsters[x]->pos);
        } 
        else if (room->monsters[x]->pathfinding == 2) { //pathfind
            pathfinding(room->monsters[x]->pos, user->pos);
        }
        else {
            path5BR(room, room->monsters[x]->pos, user->pos);
        }
        mvprintw(room->monsters[x]->pos->y, room->monsters[x]->pos->x, "%s", room->monsters[x]->buff);
    }
}

int path5BR(Room *room, Position *posmonst, Position *posplayer) {
    Monster *monster = findmonstBR(posmonst, room->monsters, room->monsternum);
    if (monster->move_count >= 5) {
        monster->move_count = 0;
        pathrand(posmonst);
        return 1;
    }

    if ((abs(posmonst->y - posplayer->y) <= 2) && (abs(posmonst->x - posplayer->x) < 2)) {
        pathfinding(posmonst, posplayer);
        monster->move_count++;
    } else {
        pathrand(posmonst);
        monster->move_count = 0;
    }

    return 1;
}


Monster *selectMonster(int level, int x){
    int monster;
    monster = rand() % 13;
    switch (monster)
    {
        case 11:
        case 0:
        case 1:
        case 6:
            return createmonster('D', 5, 1, 1, 1, 1, x); // Demon
        case 7:
        case 2:
        case 8:
            return createmonster('F', 10, 3, 1, 1, 1, x); // Fire Breathing Monster
        case 9:
        case 3:
            return createmonster('G', 15, 5, 1, 1, 3, x);  // Giant //! pathfinding 3!!
        case 4:
        case 10:
            return createmonster('S', 20, 3, 1, 1, 2, x);
        case 5:
        case 12:
            return createmonster('U', 30, 1, 1, 1, 3, x);

    }
}

Monster *createmonster(char symbol, int health, int attack, int speed, int defence, int pathfinding, int roomesh){
    Monster *nmonster;
    nmonster = malloc(sizeof(Monster));
    nmonster->symbol = symbol;
    nmonster->health = health;
    nmonster->attack = attack;
    nmonster->speed = speed;
    nmonster->defence = defence;
    nmonster->move_count = 0;
    nmonster->roomesh = roomesh;
    sprintf(nmonster->buff, "%c", symbol);

    nmonster->pathfinding = pathfinding;

    return nmonster;
}

int SetStartPos(Monster *monster, Room *room){
    monster->pos = malloc(sizeof(Position));
    monster->pos->y = (rand() % (room->height - 4)) + room->pos.y + 2;
    monster->pos->x = (rand() % (room->width - 4)) + room->pos.x + 2;
    // mvprintw(monster->pos->y, monster->pos->x, "%s", monster->buff);
}

int movemonster(Level *level){
    for (int x = 0; x < level->monsternum; x++){
        if (level->monsters[x]->health <= 0){
            continue;
        }
        mvprintw(level->monsters[x]->pos->y, level->monsters[x]->pos->x, ".");
        if (level->monsters[x]->pathfinding == 1){// random
            pathrand(level->monsters[x]->pos);
        } 
        else if (level->monsters[x]->pathfinding == 2) { //pathfind
            pathfinding(level->monsters[x]->pos, level->user->pos);
        }
        else {
            path5(level, level->monsters[x]->pos, level->user->pos);
        }
        mvprintw(level->monsters[x]->pos->y, level->monsters[x]->pos->x, "%s", level->monsters[x]->buff);
    }
}

int pathfinding(Position *start, Position *end){
        /* step left */
    if ((abs((start->x - 1) - end->x) < abs(start->x - end->x)) && (mvinch(start->y, start->x - 1) == '.'))
    {
        start->x = start->x - 1;

    /* step right */
    } else if ((abs((start->x + 1) - end->x) < abs(start->x - end->x)) && (mvinch(start->y, start->x + 1) == '.'))
    {
        start->x = start->x + 1;
    
    /* step down */
    } else if ((abs((start->y + 1) - end->y) < abs(start->y - end->y)) && (mvinch(start->y + 1, start->x) == '.'))
    {
        start->y = start->y + 1;

    /* step up */
    } else if ((abs((start->y - 1) - end->y) < abs(start->y - end->y)) && (mvinch(start->y - 1, start->x) == '.'))
    {
        start->y = start->y - 1;
    }
    else {

    }

    return 1;
}

int path5(Level *level, Position *posmonst, Position *posplayer) {
    Monster *monster = findmonst(posmonst, level->monsters);
    if (monster->move_count >= 5) {
        monster->move_count = 0;
        pathrand(posmonst);
        return 1;
    }

    if ((abs(posmonst->y - posplayer->y) <= 2) && (abs(posmonst->x - posplayer->x) < 2)) {
        pathfinding(posmonst, posplayer);
        monster->move_count++;
    } else {
        pathrand(posmonst);
        monster->move_count = 0;
    }

    return 1;
}


int pathrand(Position *pos){
    int random = rand() % 5;
    switch (random)
    {
        //up
        case 0:
            if (mvinch(pos->y - 1, pos->x) == '.'){
                pos->y = pos->y - 1;
            }
            break;
            //down
        case 1:
            if (mvinch(pos->y + 1, pos->x) == '.'){
                pos->y = pos->y + 1;
            }
            break;
            //funk you up
        case 2:
            if (mvinch(pos->y, pos->x - 1) == '.'){
                pos->x = pos->x - 1;
            }
            break;
            //right
        case 3:
            if (mvinch(pos->y, pos->x + 1) == '.'){
                pos->x = pos->x + 1;
            }
            break;
            //nothing
        case 4:
            break;
    }
    return 1;
}

Monster* findmonst(Position* pos, Monster** monsters){
    for(int i = 0; i < 6; i++){
        if (pos->y == monsters[i]->pos->y && pos->x == monsters[i]->pos->x){
            return monsters[i];
        }
    }
    return NULL;
}

Monster* findmonstBR(Position* pos, Monster** monsters, int monsternum){
    for(int i = 0; i < monsternum; i++){
        if (pos->y == monsters[i]->pos->y && pos->x == monsters[i]->pos->x){
            return monsters[i];
        }
    }
    return NULL;
}

Monster* throwfindmonster(playerG *player,Monster** monsters, int direction){
    mvprintw(0,30, "x ");
    switch (direction)
        {
        case 0:
            for (int i = 0; i < 5; i++){
                if (mvinch(player->pos->y - i - 1, player->pos->x) == 'D' || mvinch(player->pos->y - i - 1, player->pos->x) == 'F' 
                    || mvinch(player->pos->y - i - 1, player->pos->x) == 'G' || mvinch(player->pos->y - i - 1, player->pos->x) == 'S'
                    || mvinch(player->pos->y - i - 1, player->pos->x) == 'U'){
                        Position *pos = malloc(sizeof(Position));
                        pos->y = player->pos->y - i - 1;
                        pos->x = player->pos->x;
                        for( int i = 0; i < 6; i++){
                            if (pos->y == monsters[i]->pos->y && pos->x == monsters[i]->pos->x){
                                mvprintw(0,0, "x = %c", monsters[i]->symbol);
                                return monsters[i];
                            }
                        }
                    }
            }
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        }
}

void Printmonster(Monster* monst){
    attron(COLOR_PAIR(11));
    if (monst->health > 0){
        mvprintw(monst->pos->y, monst->pos->x, "%c", monst->symbol);
    }
    // attroff(COLOR_PAIR(11));
}