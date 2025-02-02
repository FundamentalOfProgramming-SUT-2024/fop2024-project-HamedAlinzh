#include "rogue.h"


int addgold(Level *level){
    for (int i = 0; i < level->roomnum; i++){
        level->rooms[i]->gold = malloc(3 * sizeof(Gold*));
        for (int j = 0; j < 3; j++){
            level->rooms[i]->gold[j] = malloc(sizeof(Gold));
            level->rooms[i]->gold[j]->pos = malloc(sizeof(Position));
            level->rooms[i]->gold[j]->pos->x = rand() % (level->rooms[i]->width - 4) + level->rooms[i]->pos.x + 2;
            level->rooms[i]->gold[j]->pos->x = rand() % (level->rooms[i]->height - 4) + level->rooms[i]->pos.y + 2;
            level->rooms[i]->gold[j]->value = 5 * (rand() % 3 + 2); 
        }
    }
    // level->rooms[0]->gold[0]->pos->x =
    // level->rooms[0]->gold[0]->pos->y =
    return 1;
}
// Gold *creategold(char symbol, int value, )

void drawgold(Level *level){
    for (int i = 0; i < level->roomnum; i++){
        for (int j = 0; j < 3; j++){
            mvprintw(level->rooms[i]->gold[j]->pos->y, level->rooms[i]->gold[j]->pos->x, "M");
        }
    }
}