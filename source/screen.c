#include "rogue.h"


int setupscreen(){
    initscr();
    start_color();
    init_pair(0xFF, COLOR_BLACK, COLOR_WHITE);
    bkgd(COLOR_BLACK);
    refresh();
    noecho();
    return 1;
}

int gamestats(Level *level){
    mvprintw(48, 5, "LEVEL: %d", level->level + 1);
    mvprintw(48, 20,"GOLD: %d", level->user->gold);
    mvprintw(48, 35, "XP: %d", level->user->xp);
    mvprintw(48, 47,"HP: %d(%d)     ", level->user->health, level->user->maxhealth);
    mvprintw(48, 65, "HUNGER: %d", level->user->hunger);
    mvprintw(48, 82, "ATTACK DAMAGE: %d", level->user->attack);
    return 1;
}