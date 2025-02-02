#include "rogue.h"

int inventory(Level *level){
    curs_set(0);
    clear();
    refresh();
    const char *weapons[] = { "MACE", "SWORD", "DAGGER", "MAGIC STAFF", "BOW AND ARROW"};
    int mace = 0, dagger = 0, magic = 0, bow = 0, sword = 0;
    for (int i = 0; i < level->user->weapons_num; i++){
        switch (level->user->weapons[i]->type){
            case 1:
                mace++;
                break;
            case 2:
                dagger++;
                break;
            case 3:
                magic++;
                break;
            case 4:
                bow++;
                break;
            case 5:
                sword++;
                break;
        }
    }
    int nitem = sizeof(weapons) / sizeof(weapons[0]);
    int selected = 0;
    int key;
    wchar_t macei[] = { L'\U00002692', L'\0' };
    wchar_t daggeri[] = { L'\U0001F5E1', L'\0' };
    wchar_t staffi[] = { L'\U00002020', L'\0' };
    wchar_t arrowi[] = { L'\U000027B3', L'\0' };
    wchar_t swordi[] = { L'\U00002694', L'\0' };
    WINDOW *inventory_win = newwin(40, 85, (MAX_HEIGHT - 40) / 2, (MAX_WIDTH - 85) / 2);
    mvwprintw(inventory_win, 4,  3, "< WEAPON TYPE >");
    mvwprintw(inventory_win, 4,  21, "< WEAPON ICON >");
    mvwprintw(inventory_win, 4,  38, "< NUMBER >");
    mvwprintw(inventory_win, 4,  51, "< DAMAGE >");
    mvwprintw(inventory_win, 4,  64, "< BOARD >");
    wattron(inventory_win, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(inventory_win, 6,  3, "< MELEE WEAPONS >");
    mvwprintw(inventory_win, 17,  3, "< RANGED WEAPONS >");
    wattroff(inventory_win, COLOR_PAIR(1) | A_BOLD);


    mvwprintw(inventory_win, 8 + 0, 25, " ' \U00002692 '");
    mvwprintw(inventory_win, 8 + 6, 25, " ' \U00002694 '");
    mvwprintw(inventory_win, 8 + 12, 25, " ' \U0001F5E1 '");
    mvwprintw(inventory_win, 8 + 18, 25, " ' \U00002020 '");
    mvwprintw(inventory_win, 8 + 24, 25, " ' \U000027B3 '");

    mvwprintw(inventory_win, 8 + 0, 42, "%d", mace);
    mvwprintw(inventory_win, 8 + 6, 42, "%d", sword);
    mvwprintw(inventory_win, 8 + 12, 42, "%d", dagger);
    mvwprintw(inventory_win, 8 + 18, 42, "%d", magic);
    mvwprintw(inventory_win, 8 + 24, 42, "%d", bow);

    mvwprintw(inventory_win, 8 + 0, 54, "-5-");
    mvwprintw(inventory_win, 8 + 6, 54, "-10-");
    mvwprintw(inventory_win, 8 + 12, 54, "-12-");
    mvwprintw(inventory_win, 8 + 18, 54, "-15-");
    mvwprintw(inventory_win, 8 + 24, 54, "-5-");

    mvwprintw(inventory_win, 8 + 0, 68, "-");
    mvwprintw(inventory_win, 8 + 6, 68, "-");
    mvwprintw(inventory_win, 8 + 12, 67, "-5-");
    mvwprintw(inventory_win, 8 + 18, 67, "-10-");
    mvwprintw(inventory_win, 8 + 24, 67, "-5-");

    while (1){
        box(inventory_win, 0, 0);
        for (int i = 0; i < nitem; i++) {
            if (i == selected) {
                wattron(inventory_win, A_REVERSE);
                mvwprintw(inventory_win, 8 + 6 * i, 7, "%s", weapons[i]);
                wattroff(inventory_win, A_REVERSE);
            } else {
                mvwprintw(inventory_win, 8 + 6 * i, 7, "%s", weapons[i]);
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
                        if (mace > 0){
                            level->user->attack = 5;
                            index = findweaponinven(level->user->weapons, 1, level->user->weapons_num);
                            level->user->selected_weapon = level->user->weapons[index];

                            // for(int i = index; i < level->user->food_num - 1; i++) {
                            //     level->user->food[i] = level->user->food[i + 1];
                            // }
                            // level->user->food[level->user->food_num - 1] = NULL;
                            // level->user->food_num--;
                            
                        }
                        break;
                    case 2:
                        if (dagger > 0){
                            // level->user->selected_weapon = NULL;
                            index = findweaponinven(level->user->weapons, 2, level->user->weapons_num);
                            level->user->selected_weapon = level->user->weapons[index];
                            level->user->attack = level->user->weapons[index]->damage;
                            // level->user->attack = 0;
                            // level->user->attack = level->user->weapons[index]->damage;

                            // for(int i = index; i < level->user->food_num - 1; i++) {
                            //     level->user->food[i] = level->user->food[i + 1];
                            // }
                            // level->user->food[level->user->food_num - 1] = NULL;
                            // level->user->food_num--;
                        }
                        else {
                            level->user->attack = 5;
                            index = findweaponinven(level->user->weapons, 1, level->user->weapons_num);
                            level->user->selected_weapon = level->user->weapons[index];
                        }
                        break;
                    case 3:
                        if (magic > 0){
                            // level->user->selected_weapon = NULL;
                            index = findweaponinven(level->user->weapons, 3, level->user->weapons_num);
                            level->user->selected_weapon = level->user->weapons[index];
                            level->user->attack = level->user->weapons[index]->damage;
                            // level->user->attack = level->user->weapons[index]->damage;

                            // for(int i = index; i < level->user->food_num - 1; i++) {
                            //     level->user->food[i] = level->user->food[i + 1];
                            // }
                            // level->user->food[level->user->food_num - 1] = NULL;
                            // level->user->food_num--;
                        }
                        else {
                            level->user->attack = 5;
                            index = findweaponinven(level->user->weapons, 1, level->user->weapons_num);
                            level->user->selected_weapon = level->user->weapons[index];
                        }
                        break;
                    case 4:
                        if (bow > 0){
                            // level->user->selected_weapon = NULL;
                            index = findweaponinven(level->user->weapons, 4, level->user->weapons_num);
                            level->user->selected_weapon = level->user->weapons[index];
                            level->user->attack = level->user->weapons[index]->damage;
                            // level->user->attack = level->user->weapons[index]->damage;
                            // for(int i = index; i < level->user->food_num - 1; i++) {
                            //     level->user->food[i] = level->user->food[i + 1];
                            // }
                            // level->user->food[level->user->food_num - 1] = NULL;
                            // level->user->food_num--;
                        }
                        else {
                            level->user->attack = 5;
                            index = findweaponinven(level->user->weapons, 1, level->user->weapons_num);
                            level->user->selected_weapon = level->user->weapons[index];
                        }
                        break;
                    case 1:
                        if (sword > 0){
                            // level->user->selected_weapon = NULL;
                            index = findweaponinven(level->user->weapons, 5, level->user->weapons_num);
                            level->user->selected_weapon = level->user->weapons[index];
                            level->user->attack = level->user->weapons[index]->damage;
                            // for(int i = index; i < level->user->food_num - 1; i++) {
                            //     level->user->food[i] = level->user->food[i + 1];
                            // }
                            // level->user->food[level->user->food_num - 1] = NULL;
                            // level->user->food_num--;
                        }
                        else {
                            level->user->attack = 5;
                            index = findweaponinven(level->user->weapons, 1, level->user->weapons_num);
                            level->user->selected_weapon = level->user->weapons[index];
                        }
                        break;
                        
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

