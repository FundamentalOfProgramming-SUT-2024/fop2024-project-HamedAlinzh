#include "rogue.h"


int backpack(Level *level){
    curs_set(0);
    clear();
    refresh();
    const char *foods[] = {"REGULAR FOOD", "HIGH-QUALITY FOOD", "MAGICAL FOOD", "ROTTEN FOOD"};
    int reg = 0, H = 0, M = 0, rot = 0;
    for (int i = 0; i < level->user->food_num; i++){
        switch (level->user->food[i]->type){
            case 1:
                reg++;
                break;
            case 2:
                H++;
                break;
            case 3:
                M++;
                break;
            case 4:
                rot++;
                break;
        }
    }
    int nitem = sizeof(foods) / sizeof(foods[0]);
    int selected = 0;
    int key;
    WINDOW *inventory_win = newwin(35, 50, (MAX_HEIGHT - 35) / 2, (MAX_WIDTH - 50) / 2);
    mvwprintw(inventory_win, 8, 30, " \"B\":    %d", reg);
    mvwprintw(inventory_win, 8 + 6, 30, " \"H\":    %d", H);
    mvwprintw(inventory_win, 8 + 12, 30, " \"M\":    %d", M);
    mvwprintw(inventory_win, 8 + 18, 30, " \"R\":    %d", rot);
    while (1){
        box(inventory_win, 0, 0);
        for (int i = 0; i < nitem; i++) {
            if (i == selected) {
                wattron(inventory_win, A_REVERSE);
                mvwprintw(inventory_win, 8 + 6 * i, 10, "%s", foods[i]);
                wattroff(inventory_win, A_REVERSE);
            } else {
                mvwprintw(inventory_win, 8 + 6 * i, 10, "%s", foods[i]);
            }
        }
        wrefresh(inventory_win);
        key = getch();
        int index;
        switch (key) {
            case 'w':
                selected--;
                if (selected < 0) selected = nitem - 1;
                break;
            case 's':
                selected++;
                if (selected >= nitem) selected = 0;
                break;
            case '\n':
                switch (selected){
                    case 0:
                        if (reg > 0){
                            index = findfoodinven(level->user->food, 1, level->user->food_num);
                            level->user->health += level->user->food[index]->recoveryAmount;
                            if (level->user->hunger < level->user->maxhunger){
                                level->user->hunger++;
                            }
                            if (level->user->health > level->user->maxhealth){
                                level->user->health = level->user->maxhealth;
                            }
                            for(int i = index; i < level->user->food_num - 1; i++) {
                                level->user->food[i] = level->user->food[i + 1];
                            }
                            level->user->food[level->user->food_num - 1] = NULL;
                            level->user->food_num--;
                            reg--;
                        }
                    case 1:
                        if (H > 0){
                            level->countHfood = 2;
                            level->Hfood->is_there = 1;
                            level->user->attack = level->user->attack * 2;
                            index = findfoodinven(level->user->food, 2, level->user->food_num);
                            level->user->health += level->user->food[index]->recoveryAmount;
                            if (level->user->hunger < level->user->maxhunger){
                                level->user->hunger++;
                            }
                            if (level->user->health > level->user->maxhealth){
                                level->user->health = level->user->maxhealth;
                            }
                            for(int i = index; i < level->user->food_num - 1; i++) {
                                level->user->food[i] = level->user->food[i + 1];
                            }
                            level->user->food[level->user->food_num - 1] = NULL;
                            level->user->food_num--;
                            H--;
                        }
                    case 2:
                        if (M > 0){
                            level->speedcounter = 2;
                            level->is_speed = 1;
                            index = findfoodinven(level->user->food, 3, level->user->food_num);
                            level->user->health += level->user->food[index]->recoveryAmount;
                            if (level->user->hunger < level->user->maxhunger){
                                level->user->hunger++;
                            }
                            if (level->user->health > level->user->maxhealth){
                                level->user->health = level->user->maxhealth;
                            }
                            for(int i = index; i < level->user->food_num - 1; i++) {
                                level->user->food[i] = level->user->food[i + 1];
                            }
                            level->user->food[level->user->food_num - 1] = NULL;
                            level->user->food_num--;
                            M--;
                        }
                    case 3:
                        if (rot > 0){
                            index = findfoodinven(level->user->food, 4, level->user->food_num);
                            level->user->health += level->user->food[index]->recoveryAmount;
                            if (level->user->hunger < level->user->maxhunger){
                                level->user->hunger++;
                            }
                            for(int i = index; i < level->user->food_num - 1; i++) {
                                level->user->food[i] = level->user->food[i + 1];
                            }
                            level->user->food[level->user->food_num - 1] = NULL;
                            level->user->food_num--;
                            rot--;
                        }
                        
                }
                curs_set(1);
                return 0;
            case 27:
                curs_set(1);
                return 0;
        }
    }
    return 0;
}