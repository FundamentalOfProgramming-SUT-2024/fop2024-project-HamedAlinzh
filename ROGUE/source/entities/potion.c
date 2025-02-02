#include "rogue.h"

/* regular potion:
recovery amount: 6
ability: -
probability in rooms: 50% */

/* high-quality potion:
recovery amount: 10
ability: double the attack damage
probability in rooms: 10% */

/* magical potion:
recovery amount: 8
ability: double the speed
probability in rooms: 10% */

/* rotten potion:
recovery amount: -3
ability: -
probability: 20% */


int addpotion(Level *level){
    level->potions = malloc(sizeof(Potion *) * 6);
    level->potion_num = 0;
    for (int x = 0; x < level->roomnum; x++){
        level->potions[level->potion_num] = selectpotion(x);
        potionpos(level->potions[level->potion_num], level->rooms[x]);
        level->potion_num++;
    }
    return 1;
}

Potion *selectpotion(int x){
    wchar_t health[] = { L'\U00002623', L'\0' }; // Biohazard sign
    wchar_t speed[] = { L'\U0000269B', L'\0' };
    wchar_t damage[] = { L'\U00002622', L'\0' };
    int potion;
    potion = rand() % 3;
    switch (potion)
    {
        case 0:
            return createpotion(health, 0, 1, x, 13);  //health potion
        case 1:
            return createpotion(speed, 1, 2, x, 16); //speed potion
        case 2:
            return createpotion(damage, 2, 3, x, 17); // damage potion
        default:
            break;
    }
}

Potion *createpotion(wchar_t symbol[], int ability, int type, int roomesh, int color){
    Potion *potion;
    potion = malloc(sizeof(Potion));
    wcsncpy(potion->name, symbol, 10);
    potion->type = type;
    potion->roomesh = roomesh;
    potion->is_there = rand() % 2;
    potion->color = color;
    potion->ability = ability;
    return potion;
}

void potionpos(Potion* potion, Room* room){
    potion->pos = malloc(sizeof(Position));
    potion->pos->y = (rand() % (room->height - 2)) + room->pos.y + 1;
    potion->pos->x = (rand() % (room->width - 2)) + room->pos.x + 1;
}

Potion* findpotion(Position* pos, Potion** potions){
    for( int i = 0; i < 6; i++){
        if (pos->y == potions[i]->pos->y && pos->x == potions[i]->pos->x){
            return potions[i];
        }
    }
    return NULL;
}

int grabpotion(Level *level, Potion *potion){
    if (level->user->potion_num < 5){
        mvprintw(potion->pos->y, potion->pos->x, ".");
        level->user->potion[level->user->potion_num] = potion;
        level->user->potion_num++;
        potion->is_there = 0;
    }
}

int findpotioninven(Potion **potion, int type, int potion_num) {
    for (int i = 0; i < potion_num; i++) {
        if (potion[i] != NULL && potion[i]->type == type) {
            return i;
        }
    }
    
}

void Printpotion(Potion *potion){
    if (potion->is_there == 1){
        mvaddwstr(potion->pos->y, potion->pos->x, potion->name);
    }
}

