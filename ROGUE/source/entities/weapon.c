#include "rogue.h"

int addweapon(Level *level){
    level->weapons = malloc(2 * sizeof(Weapon*));
    level->weapons_num = 0;
    for (int x = 0; x < 2; x++){
        int i = rand() % level->roomnum;
        level->weapons[level->weapons_num] = selectweapon(i);
        weaponpos(level->weapons[level->weapons_num], level->rooms[i]);
        level->weapons_num++;
    }
}

Weapon *selectweapon(int i){
    wchar_t dagger[] = { L'\U0001F5E1', L'\0' };
    wchar_t staff[] = { L'\U00002020', L'\0' };
    wchar_t arrow[] = { L'\U000027B3', L'\0' };
    wchar_t sword[] = { L'\U00002694', L'\0' };
    int weapon;
    weapon = rand() % 4;
    switch (weapon)
    {
    case 0:   //Dagger 
        return createweapon(dagger, 12, 5, 0, 20, 2, i, 1);
        break;
    case 1:   //Magic staff
        return createweapon(staff, 15, 10, 0, 20, 3, i, 1);
        break;
    case 2:   //Arrow
        return createweapon(arrow, 5, 5, 0, 20, 4, i, 1);
        break;
    case 3:   //Sword
        return createweapon(sword, 10, 0, 0, 20, 5, i, 0);
        break; 
    default:
        break;
    }
}

Weapon *createweapon(wchar_t symbol[], int damage, int range, int ability, int durability, int type, int roomesh, int isthrowable){
    Weapon *weapon = malloc(sizeof(Weapon));
    wcsncpy(weapon->name, symbol, 10);
    weapon->damage = damage;
    weapon->durability = durability;
    weapon->ability = ability;
    weapon->is_there = 1;
    weapon->type = type;
    weapon->roomesh = roomesh;
    weapon->range = range;
    weapon->isthrowable = isthrowable;
    return weapon;
}

int grabweapon(Level *level, Weapon *weapon){
    mvprintw(weapon->pos->y, weapon->pos->x, ".");
    if (weapon->type == 2){
        for (int i = 0; i < 1; i++){
            level->user->weapons[level->user->weapons_num] = weapon;
            level->user->weapons_num++;
        }
    }
    else if (weapon->type == 3){
        for (int i = 0; i < 1; i++){
            level->user->weapons[level->user->weapons_num] = weapon;
            level->user->weapons_num++;
        }
    }
    else if (weapon->type == 4){
        for (int i = 0; i < 1; i++){
            level->user->weapons[level->user->weapons_num] = weapon;
            level->user->weapons_num++;
        }
    }
    else{
        level->user->weapons[level->user->weapons_num] = weapon;
        level->user->weapons_num++;
    }
    weapon->is_there = 0;
}

Weapon *findweapon(Position* pos, Weapon** weapons){
    for( int i = 0; i < 2; i++){
        if (pos->y == weapons[i]->pos->y && pos->x == weapons[i]->pos->x){
            return weapons[i];
        }
    }
    return NULL;
}

int findweaponinven(Weapon **weapon, int type, int weapon_num) {
    for (int i = 0; i < weapon_num; i++) {
        if (weapon[i] != NULL && weapon[i]->type == type) {
            return i;
        }
    }
}

void weaponpos(Weapon* weapon, Room* room){
    weapon->pos = malloc(sizeof(Position));
    weapon->pos->y = (rand() % (room->height - 2)) + room->pos.y + 1;
    weapon->pos->x = (rand() % (room->width - 2)) + room->pos.x + 1;
}

void Printweapon(Weapon *weapon){
    if (weapon->is_there == 1){
        mvaddwstr(weapon->pos->y, weapon->pos->x, weapon->name);
    }
}
