#include "rogue.h"


int potionbag(Level *level){
    curs_set(0);
    clear();
    refresh();
    const char *potions[] = {"HEALTH POTION", "SPEED POTION", "DAMAGE POTION"};
    int heal = 0, Sp = 0, M = 0;
    for (int i = 0; i < level->user->potion_num; i++){
        switch (level->user->potion[i]->type){
            case 1:
                heal++;
                break;
            case 2:
                Sp++;
                break;
            case 3:
                M++;
                break;
                break;
        }
    }
    int nitem = sizeof(potions) / sizeof(potions[0]);
    int selected = 0;
    int key;
    WINDOW *inventory_win = newwin(30, 50, (MAX_HEIGHT - 30) / 2, (MAX_WIDTH - 50) / 2);
    mvwprintw(inventory_win, 8 + 0, 25, " ' \U00002623 ':    %d", heal);
    mvwprintw(inventory_win, 8 + 6, 25, " ' \U0000269B ':    %d", Sp);
    mvwprintw(inventory_win, 8 + 12, 25, " ' \U00002622 ':    %d", M);
    while (1){
        box(inventory_win, 0, 0);
        for (int i = 0; i < nitem; i++) {
            if (i == selected) {
                wattron(inventory_win, A_REVERSE);
                mvwprintw(inventory_win, 8 + 6 * i, 10, "%s", potions[i]);
                wattroff(inventory_win, A_REVERSE);
            } else {
                mvwprintw(inventory_win, 8 + 6 * i, 10, "%s", potions[i]);
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
                        if (heal > 0){
                            level->sabet = 1;
                            index = findpotioninven(level->user->potion, 1, level->user->potion_num);
                            for(int i = index; i < level->user->potion_num - 1; i++) {
                                level->user->potion[i] = level->user->potion[i + 1];
                            }
                            level->user->potion[level->user->potion_num - 1] = NULL;
                            level->user->potion_num--;
                            heal--;
                        }
                    case 1:
                        if (Sp > 0){
                            level->speedcounter = 2;
                            level->is_speed = 1;
                            index = findpotioninven(level->user->potion, 2, level->user->potion_num);
                            if (level->user->hunger < level->user->maxhunger){
                                level->user->hunger++;
                            }
                            if (level->user->health > level->user->maxhealth){
                                level->user->health = level->user->maxhealth;
                            }
                            for(int i = index; i < level->user->potion_num - 1; i++) {
                                level->user->potion[i] = level->user->potion[i + 1];
                            }
                            level->user->potion[level->user->potion_num - 1] = NULL;
                            level->user->potion_num--;
                            Sp--;
                        }
                    case 2:
                        if (M > 0){
                            level->countHfood = 2;
                            level->Hfood->is_there = 1;
                            level->user->attack = level->user->attack * 2;
                            index = findpotioninven(level->user->potion, 3, level->user->potion_num);
                            if (level->user->hunger < level->user->maxhunger){
                                level->user->hunger++;
                            }
                            if (level->user->health > level->user->maxhealth){
                                level->user->health = level->user->maxhealth;
                            }
                            for(int i = index; i < level->user->potion_num - 1; i++) {
                                level->user->potion[i] = level->user->potion[i + 1];
                            }
                            level->user->potion[level->user->potion_num - 1] = NULL;
                            level->user->potion_num--;
                            M--;
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