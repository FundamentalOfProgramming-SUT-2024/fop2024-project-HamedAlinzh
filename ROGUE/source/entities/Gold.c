#include "rogue.h"


int addgold(Level *level){
    level->golds = malloc(level->gold_num * sizeof(Gold*));
    level->gold_num = 0;
    level->Taloysia = malloc(sizeof(Gold));
    level->Taloysia->pos = malloc(sizeof(Position));
    level->Taloysia->value = 100;
    if ((rand() % 4) == 0){
        int i = rand() % 6;
        level->Taloysia->is_there = 1;
        level->Taloysia->roomesh = i;
        level->Taloysia->pos->x = rand() % (level->rooms[i]->width - 4) + level->rooms[i]->pos.x + 2;
        level->Taloysia->pos->y = rand() % (level->rooms[i]->height - 4) + level->rooms[i]->pos.y + 2;        
    }
    for (int i = 0; i < level->roomnum; i++){
        if ((rand() % 2) == 0){
            level->golds[level->gold_num] = malloc(sizeof(Gold));
            level->golds[level->gold_num]->value = 5 * (rand() % 3 + 2);
            level->golds[level->gold_num]->is_there = 1;
            level->golds[level->gold_num]->roomesh = i;
            level->golds[level->gold_num]->pos = malloc(sizeof(Position));
            level->golds[level->gold_num]->pos->x = rand() % (level->rooms[i]->width - 4) + level->rooms[i]->pos.x + 2;
            level->golds[level->gold_num]->pos->y = rand() % (level->rooms[i]->height - 4) + level->rooms[i]->pos.y + 2;
            level->gold_num++;
        }
    }
}

int addgoldT(Room *Troom) {
    Troom->gold = malloc(40 * sizeof(Gold *));
    Troom->taloysia = malloc(30 * sizeof(Gold *));
    Troom->gold_num = 20;
    Troom->taloysia_num = 10;
    for (int i = 0; i < Troom->gold_num; i++){
        Troom->gold[i] = malloc(sizeof(Gold));
        Troom->gold[i]->value = 5 * (rand() % 3 + 2);
        Troom->gold[i]->pos = malloc(sizeof(Position));
        Troom->gold[i]->pos->y = rand() % (Troom->height - 4) + Troom->pos.y + 2;
        Troom->gold[i]->pos->x = rand() % (Troom->width - 4) + Troom->pos.x + 2;
        Troom->gold[i]->is_there = 1;
    }
    for (int i = 0; i < Troom->taloysia_num; i++){
        Troom->taloysia[i] = malloc(sizeof(Gold));
        Troom->taloysia[i]->value = 100;
        Troom->taloysia[i]->pos = malloc(sizeof(Position));
        Troom->taloysia[i]->pos->y = rand() % (Troom->height - 4) + Troom->pos.y + 2;
        Troom->taloysia[i]->pos->x = rand() % (Troom->width - 4) + Troom->pos.x + 2;
        Troom->taloysia[i]->is_there = 1;
    }

}

int consume_gold(Level *level, Gold *gold){
    mvprintw(gold->pos->y, gold->pos->x, ".");
    level->user->gold += gold->value;
    gold->is_there = 0;
}
int consume_taloysia(Level *level, Gold *gold){
    mvprintw(gold->pos->y, gold->pos->x, ".");
    level->user->gold += gold->value;
    gold->is_there = 0;
}

int consume_goldT(Level *level, Gold *gold, int* count){
    mvprintw(gold->pos->y, gold->pos->x, ".");
    level->user->gold += gold->value;
    gold->is_there = 0;
    *count -= 1;
}
int consume_taloysiaT(Level *level, Gold *gold, int* count){
    mvprintw(gold->pos->y, gold->pos->x, ".");
    level->user->gold += gold->value;
    gold->is_there = 0;
    *count -= 1;
}

void Printgold(Level *level){
    wchar_t gold[] = { L'\u269C', L'\0' };
    wchar_t taloysia[] = { L'\u269A', L'\0' };
    attron(COLOR_PAIR(14));
    for (int i = 0; i < level->gold_num; i++) {
        if (level->golds[i]->is_there && level->rooms[level->golds[i]->roomesh]->is_there == 1) {
            // Print the wide-character string
            mvaddwstr(level->golds[i]->pos->y, level->golds[i]->pos->x, gold);
        }
    }
    if (level->Taloysia->is_there == 1 && level->rooms[level->Taloysia->roomesh]->is_there == 1){
        mvaddwstr(level->Taloysia->pos->y, level->Taloysia->pos->x, taloysia);
    }
    attroff(COLOR_PAIR(14));
}

void PrintgoldT(Room *room){
    wchar_t gold[] = { L'\u269C', L'\0' };
    wchar_t taloysia[] = { L'\u269A', L'\0' };
    attron(COLOR_PAIR(14));
    for (int i = 0; i < room->gold_num; i++) {
        if (room->gold[i]->is_there == 1){
            mvaddwstr(room->gold[i]->pos->y, room->gold[i]->pos->x, gold);
        }
    }
    for (int i = 0; i < room->taloysia_num; i++) {
        if (room->taloysia[i]->is_there == 1){
            mvaddwstr(room->taloysia[i]->pos->y, room->taloysia[i]->pos->x, taloysia);
        }
    }
    attroff(COLOR_PAIR(14));
}

Gold* findgold(Position* pos, Gold** golds){
    for( int i = 0; i < 6; i++){
        if (pos->y == golds[i]->pos->y && pos->x == golds[i]->pos->x){
            return golds[i];
        }
    }
    return NULL;
}

Gold* findgoldT(Position* pos, Gold** golds, int treasure_num){
    for( int i = 0; i < treasure_num; i++){
        if (pos->y == golds[i]->pos->y && pos->x == golds[i]->pos->x){
            return golds[i];
        }
    }
    return NULL;
}

