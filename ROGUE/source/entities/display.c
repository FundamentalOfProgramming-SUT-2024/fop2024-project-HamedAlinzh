#include <rogue.h>



void gameover(playerG *player){
    curs_set(0);
    WINDOW *gameoverwin = newwin(35, 50, (MAX_HEIGHT - 35) / 2, (MAX_WIDTH - 50) / 2);
    wattron(gameoverwin ,COLOR_PAIR(11));
    box(gameoverwin, 0, 0);
    wattroff(gameoverwin ,COLOR_PAIR(11));
    mvwprintw(gameoverwin, 4, 16, "### GAME OVER! ###");
    mvwprintw(gameoverwin, 9, 4, "STATS:");
    mvwprintw(gameoverwin, 13, 6, "PLAYER NAME: %s", player->name);
    mvwprintw(gameoverwin, 17, 6, "GOLDS COLLECTED: %d", player->gold);
    mvwprintw(gameoverwin, 21, 6, "MONSTERS SLAYED: %d", player->xp);
    mvwprintw(gameoverwin, 25, 6, "DISTANCE TRAVELLED: %d", player->distance);
    mvwprintw(gameoverwin, 29, 6, "XP: %d", player->xp);
    wrefresh(gameoverwin);
    wgetch(gameoverwin);
    delwin(gameoverwin);
}

void win(playerG *player){
    curs_set(0);
    WINDOW *gameoverwin = newwin(35, 50, (MAX_HEIGHT - 35) / 2, (MAX_WIDTH - 50) / 2);
    wattron(gameoverwin ,COLOR_PAIR(14));
    box(gameoverwin, 0, 0);
    mvwprintw(gameoverwin, 4, 17, "### YOU WIN! ###");
    mvwprintw(gameoverwin, 9, 4, "STATS:");
    mvwprintw(gameoverwin, 13, 6, "PLAYER NAME: %s", player->name);
    mvwprintw(gameoverwin, 17, 6, "GOLDS COLLECTED: %d", player->gold);
    mvwprintw(gameoverwin, 21, 6, "MONSTERS SLAYED: %d", player->xp);
    mvwprintw(gameoverwin, 25, 6, "DISTANCE TRAVELLED: %d", player->distance);
    mvwprintw(gameoverwin, 29, 6, "XP: %d", player->xp);
    wrefresh(gameoverwin);
    wgetch(gameoverwin);
    delwin(gameoverwin);
}

void credits(){
    curs_set(0);
    WINDOW *gameoverwin = newwin(13, 50, (MAX_HEIGHT - 13) / 2, (MAX_WIDTH - 50) / 2);
    box(gameoverwin, 0, 0);
    mvwprintw(gameoverwin, 4, 17, "#### CREDITS ####");
    mvwprintw(gameoverwin, 6, 8, "COPYRIGHT © HAMED ALINEZHAD FOP2024");
    mvwprintw(gameoverwin, 8, 16, "ALL RIGHTS RESERVED");
    wrefresh(gameoverwin);
    wgetch(gameoverwin);
    delwin(gameoverwin);
}