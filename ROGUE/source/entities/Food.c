#include "rogue.h"

/* regular food:
recovery amount: 6
ability: -
probability in rooms: 50% */

/* high-quality food:
recovery amount: 10
ability: double the attack damage
probability in rooms: 10% */

/* magical food:
recovery amount: 8
ability: double the speed
probability in rooms: 10% */

/* rotten food:
recovery amount: -3
ability: -
probability: 20% */


int addfood(Level *level){
    level->foods = malloc(sizeof(Food *) * 6);
    level->food_num = 0;
    for (int x = 0; x < level->roomnum; x++){
        level->foods[level->food_num] = selectfood(x);
        foodpos(level->foods[level->food_num], level->rooms[x]);
        level->food_num++;
    }
    return 1;
}

Food *selectfood(int x){
    int food;
    food = rand() % 10;
    switch (food)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            return createfood('B', 6, 0, 1, x, 13);  //reg food
        case 6:
            return createfood('H', 10, 1, 2, x, 16); //high food
        case 7:
            return createfood('M', 8, 2, 3, x, 17); // magical food
        case 8:
        case 9:
            return createfood('B', -3, 0, 4, x, 13); // rotten food
        default:
            break;
    }
}

Food *createfood(char symbol, int recovery, int ability, int type, int roomesh, int color){
    Food *food;
    food = malloc(sizeof(Food));
    food->recoveryAmount = recovery;
    food->shape = symbol;
    food->type = type;
    food->roomesh = roomesh;
    food->is_there = 1;
    food->color = color;
    return food;
}

void foodpos(Food* food, Room* room){
    food->pos = malloc(sizeof(Position));
    food->pos->y = (rand() % (room->height - 2)) + room->pos.y + 1;
    food->pos->x = (rand() % (room->width - 2)) + room->pos.x + 1;
}

Food* findfood(Position* pos, Food** foods){
    for( int i = 0; i < 6; i++){
        if (pos->y == foods[i]->pos->y && pos->x == foods[i]->pos->x){
            return foods[i];
        }
    }
    return NULL;
}

int grabfood(Level *level, Food *food){
    if (level->user->food_num < 5){
        mvprintw(food->pos->y, food->pos->x, ".");
        level->user->food[level->user->food_num] = food;
        level->user->food_num++;
        food->is_there = 0;
    }
}

int findfoodinven(Food **food, int type, int food_num) {
    for (int i = 0; i < food_num; i++) {
        if (food[i] != NULL && food[i]->type == type) {
            return i;
        }
    }
    
}

void Printfood(Food *food){
    attron(COLOR_PAIR(food->color));
    if (food->is_there == 1){
        mvprintw(food->pos->y, food->pos->x, "%c", food->shape);
    }
    attroff(COLOR_PAIR(food->color));
}

