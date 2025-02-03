#include "rogue.h"
Level *createlevel(int level, playerG *user, Game *game){
    Level *newlevel;
    newlevel = malloc(sizeof(Level));
    newlevel->stair = malloc(sizeof(Position));
    for (int i = 0; i < 8; i++) {
        newlevel->pathGrid[i] = malloc(MAX_HEIGHT * sizeof(Pathgrid *));
        for (int y = 0; y < MAX_HEIGHT; y++) {
            newlevel->pathGrid[i][y] = malloc(MAX_WIDTH * sizeof(Pathgrid));
            for (int x = 0; x < MAX_WIDTH; x++) {
                newlevel->pathGrid[i][y][x].visited = 0;
                newlevel->pathGrid[i][y][x].flag = 0;
                newlevel->pathGrid[i][y][x].tile = ' ';
            }
        }
    }
    newlevel->Hfood = malloc(sizeof(isthere));
    newlevel->Hfood->is_there = 0;
    newlevel->countHfood = 2;
    newlevel->countshaf = 0;
    newlevel->speedcounter = 0;
    newlevel->level = level;
    newlevel->roomnum = 6;
    newlevel->rooms = roomsetup(newlevel);
    newlevel->tiles = savelevel();
    newlevel->user = user;
    newlevel->user->pos->y = newlevel->rooms[0]->pos.y + 2;
    newlevel->user->pos->x = newlevel->rooms[0]->pos.x + 2;
    mvprintw(newlevel->user->pos->y, newlevel->user->pos->x, "%c", newlevel->user->symbol);
    move(newlevel->user->pos->y, newlevel->user->pos->x);
    addmonsters(newlevel, game);
    addgold(newlevel);
    addfood(newlevel);
    addweapon(newlevel);
    addpotion(newlevel);
    int i = rand() % 3 + 3;
    newlevel->stair->y = rand() % (newlevel->rooms[i]->height - 4) + newlevel->rooms[i]->pos.y + 2;
    newlevel->stair->x = rand() % (newlevel->rooms[i]->width - 4) + newlevel->rooms[i]->pos.x + 2;
    newlevel->stair->roomesh = i;
    newlevel->is_there = 1;
    newlevel->is_speed = 0;
    newlevel->sabet = 0;
    int v = rand() % 2 + 4;
    return newlevel;
}

Level *createnewlevel(int level, Level *newlevel, playerG *player, Game *game){
    clear();
    for (int i = 0; i < 8; i++) {
        newlevel->pathGrid[i] = malloc(MAX_HEIGHT * sizeof(Pathgrid *));
        for (int y = 0; y < MAX_HEIGHT; y++) {
            newlevel->pathGrid[i][y] = malloc(MAX_WIDTH * sizeof(Pathgrid));
            for (int x = 0; x < MAX_WIDTH; x++) {
                newlevel->pathGrid[i][y][x].visited = 0;
                newlevel->pathGrid[i][y][x].flag = 0;
                newlevel->pathGrid[i][y][x].tile = ' ';
            }
        }
    }
    newlevel->Hfood = malloc(sizeof(isthere));
    newlevel->Hfood->is_there = 0;
    newlevel->countshaf = 0;
    newlevel->countHfood = 2;
    newlevel->stair = malloc(sizeof(Position));
    newlevel->stairP = malloc(sizeof(Position));
    newlevel->trap = malloc(sizeof(Position));
    newlevel->Tdoor = malloc(sizeof(Position));
    newlevel->Pdoor = malloc(sizeof(Position));
    newlevel->key = malloc(sizeof(Position));
    newlevel->level = level;
    newlevel->roomnum = 6;
    newlevel->rooms = roomsetup(newlevel);
    newlevel->tiles = savelevel();
    newlevel->user = player;
    newlevel->user->pos->y = newlevel->rooms[0]->pos.y + 2;
    newlevel->user->pos->x = newlevel->rooms[0]->pos.x + 2;
    mvprintw(newlevel->user->pos->y, newlevel->user->pos->x, "%c", newlevel->user->symbol);
    move(newlevel->user->pos->y, newlevel->user->pos->x);
    addmonsters(newlevel, game);
    addgold(newlevel);
    addfood(newlevel);
    addweapon(newlevel);
    addpotion(newlevel);
    newlevel->is_there = 1;
    newlevel->is_speed = 0;
    newlevel->sabet = 0;
    int i = rand() % 3 + 3;
    newlevel->stair->y = rand() % (newlevel->rooms[i]->height - 4) + newlevel->rooms[i]->pos.y + 2;
    newlevel->stair->x = rand() % (newlevel->rooms[i]->width - 4) + newlevel->rooms[i]->pos.x + 2;
    newlevel->stair->roomesh = i;
    int j = rand() % 3;
    newlevel->stairP->y = rand() % (newlevel->rooms[j]->height - 4) + newlevel->rooms[j]->pos.y + 2;
    newlevel->stairP->x = rand() % (newlevel->rooms[j]->width - 4) + newlevel->rooms[j]->pos.x + 2;
    newlevel->stairP->roomesh = j;
    int k = rand() % 6;
    newlevel->trap->y = rand() % (newlevel->rooms[k]->height - 4) + newlevel->rooms[k]->pos.y + 2;
    newlevel->trap->x = rand() % (newlevel->rooms[k]->width - 4) + newlevel->rooms[k]->pos.x + 2;
    newlevel->trap->roomesh = k;
    newlevel->istrap = 1;
    newlevel->isPdoor = 1;
    int v = rand() % 2 + 4;
    newlevel->Tdoor->y = rand() % (newlevel->rooms[v]->height - 4) + newlevel->rooms[v]->pos.y + 2;
    newlevel->Tdoor->x = rand() % (newlevel->rooms[v]->width - 4) + newlevel->rooms[v]->pos.x + 2;
    newlevel->Tdoor->roomesh = v;

    int q = rand() % 6;
    newlevel->Pdoor->y = rand() % (newlevel->rooms[q]->height - 4) + newlevel->rooms[q]->pos.y + 2;
    newlevel->Pdoor->x = rand() % (newlevel->rooms[q]->width - 4) + newlevel->rooms[q]->pos.x + 2;
    newlevel->Pdoor->roomesh = q;
    if (level == 3){
        int w = rand() % 6;
        newlevel->key->y = rand() % (newlevel->rooms[w]->height - 4) + newlevel->rooms[w]->pos.y + 2;
        newlevel->key->x = rand() % (newlevel->rooms[w]->width - 4) + newlevel->rooms[w]->pos.x + 2;
        newlevel->key->roomesh = w;
        newlevel->key->is_there = 1;
    }
    return newlevel;
}

Room** roomsetup(Level *level) {
    Room **rooms;
    rooms = malloc(sizeof(Room) * 6);

    int starty[6];
    int startx[6];
    int heights[6];
    int widths[6];
    for (int i = 0; i < 3; i++){
        starty[2 * i] = rand() % 10 + 3;
        startx[2 * i] = rand() % 25 + 2 + (60 * i);
        heights[2 * i] = rand() % 8 + 6;
        widths[2 * i] = rand() % 30 + 6;
    }
    for (int i = 0; i < 3; i++){
        starty[2 * i + 1] = rand() % 12 + 1 + 24;
        startx[2 * i + 1] = rand() % 30 + 2 + (60 * i);
        heights[2 * i + 1] = rand() % 6 + 5;
        widths[2 * i + 1] = rand() % 20 + 6;
    }

    rooms[0] = createRoom(starty[0], startx[0], heights[0], widths[0]);
    rooms[0]->is_there = 1;
    rooms[1] = createRoom(starty[1], startx[1], heights[1], widths[1]);
    rooms[2] = createRoom(starty[2], startx[2], heights[2], widths[2]);
    rooms[3] = createRoom(starty[3], startx[3], heights[3], widths[3]);
    rooms[4] = createRoom(starty[4], startx[4], heights[4], widths[4]);
    rooms[5] = createRoom(starty[5], startx[5], heights[5], widths[5]);
    Printroom(rooms[0]);
    Printroom(rooms[1]);
    Printroom(rooms[2]);
    Printroom(rooms[3]);
    Printroom(rooms[4]);
    Printroom(rooms[5]);

    pathFind(rooms[0]->door[3], rooms[2]->door[1], level->pathGrid[0]);
    pathFind(rooms[0]->door[2], rooms[1]->door[0], level->pathGrid[1]);
    pathFind(rooms[2]->door[2], rooms[3]->door[0], level->pathGrid[2]);
    pathFind(rooms[1]->door[3], rooms[3]->door[1], level->pathGrid[3]);
    pathFind(rooms[3]->door[3], rooms[5]->door[1], level->pathGrid[4]);
    pathFind(rooms[4]->door[2], rooms[5]->door[0], level->pathGrid[5]);
    pathFind(rooms[2]->door[3], rooms[4]->door[1], level->pathGrid[6]);
    pathFind(rooms[0]->door[0], rooms[2]->door[0], level->pathGrid[7]);
    // pathFind(rooms[4]->door[0], rooms[5]->door[0], level->pathGrid[8]);
    clear();

    return rooms;
}

char ** savelevel(){
    int x, y;
    char ** positions;
    positions = malloc(sizeof(char*) * 49);
    for (y = 0; y < 49; y++){
        positions[y] = malloc(sizeof(char) * 190);
        for (x = 0; x < 190; x++){
            positions[y][x] = mvinch(y, x);
        }
    }

    return positions;
}

void Printlevel(Level *level){
    int x, y;
    Room **rooms = level->rooms;
    for (y = 0; y < MAX_HEIGHT; y++){
        for (x = 0; x < MAX_WIDTH; x++){
            mvprintw(y, x, "%c", level->tiles[y][x]);
        }
    }
    printpath(level->user->pos, level);
    printpathvisited(level);
    int i = findroom(level->user->pos, level);
    if (i < 7 && level->rooms[i]->is_there == 0){
        Printroom(level->rooms[i]);
        level->rooms[i]->is_there = 1;
    }
    for (int i = 0; i < level->roomnum; i++){
        Printroomvisited(level->rooms[i]);
    }
    for (int i = 0; i < level->monsternum; i++){
        if (level->rooms[level->monsters[i]->roomesh]->is_there == 1)
            Printmonster(level->monsters[i]);
    }
    for (int i = 0; i < level->food_num; i++){
        if (level->rooms[level->foods[i]->roomesh]->is_there == 1)
            Printfood(level->foods[i]);
    }
    Printgold(level);
    for (int i = 0; i < level->weapons_num; i++){  // !!!!!
        if (level->rooms[level->weapons[i]->roomesh]->is_there == 1){
            Printweapon(level->weapons[i]);
        }
    }
    for (int i = 0; i < level->potion_num; i++){ 
        if (level->rooms[level->potions[i]->roomesh]->is_there == 1){
            Printpotion(level->potions[i]);
        }
    }
    
    wchar_t Tdoor[] = {L'\U00002126', L'\0'};
    if (level->level > 0 && (level->istrap == 1) && (level->rooms[level->trap->roomesh]->is_there == 1)){
        mvprintw(level->trap->y, level->trap->x, "^");
    }
    if (level->level == 3 && (level->key->is_there == 1) && (level->rooms[level->key->roomesh]->is_there == 1)){
        mvprintw(level->key->y, level->key->x, "&");
    }
    if (level->level == 3 && level->rooms[level->Tdoor->roomesh]->is_there == 1)    //!!!!!
        mvaddwstr(level->Tdoor->y, level->Tdoor->x, Tdoor);
    if (level->level > 0){
        if (level->rooms[level->Pdoor->roomesh]->is_there == 1 && (level->isPdoor == 1))
            mvprintw(level->Pdoor->y, level->Pdoor->x, "?");
    }
    if (level->level > 0){
        if (level->rooms[level->stairP->roomesh]->is_there == 1)
            mvprintw(level->stairP->y, level->stairP->x, "<");
    }
    if (level->rooms[level->stair->roomesh]->is_there == 1 && level->level != 3)
        mvprintw(level->stair->y, level->stair->x, ">");
    Printplayer(level->user);
    if (level->Hfood->is_there == 1){
        attron(COLOR_PAIR(11));
        mvprintw(48, 135, "DAMAGE IMPROVEMENT ABILITY ENABLED!");
        attroff(COLOR_PAIR(11));
        move(level->user->pos->y, level->user->pos->x);
    }
    if (level->countHfood % 50 == 1){
        level->Hfood->is_there = 0;
        level->user->attack /= 2;
        level->countHfood = 2;
        attron(COLOR_PAIR(11));
        mvprintw(48, 135, "                                     ");
        attroff(COLOR_PAIR(11));
        move(level->user->pos->y, level->user->pos->x);
    }
    if (level->sabet == 1){
        mvprintw(47, 135, "HEALTH POTION ABILITY ENABLED!");
    }
    else {
        mvprintw(47, 135, "                                ");
    }
}

void Printlevelm(Level *level){
    int x, y;
    Room **rooms = level->rooms;
    for (y = 0; y < MAX_HEIGHT; y++){
        for (x = 0; x < MAX_WIDTH; x++){
            mvprintw(y, x, "%c", level->tiles[y][x]);
        }
    }
    // Printroom(level->rooms[0]);
    printpathvisitedM(level);
    for (int i = 0; i < 6; i++){
        Printroom(level->rooms[i]);
    }
    for (int i = 0; i < level->monsternum; i++){
        Printmonster(level->monsters[i]);
    }
    for (int i = 0; i < level->food_num; i++){
        Printfood(level->foods[i]);
    }
    Printgold(level);
    for (int i = 0; i < level->weapons_num; i++){
        Printweapon(level->weapons[i]);
    }
    for (int i = 0; i < level->potion_num; i++){
        Printpotion(level->potions[i]);
    }
    if (level->level > 0 && (level->isPdoor == 1)){
        mvprintw(level->Pdoor->y, level->Pdoor->x, "?");
    }
    wchar_t Tdoor[] = {L'\U00002126', L'\0'};
    if (level->level == 3){
        mvaddwstr(level->Tdoor->y, level->Tdoor->x, Tdoor);
    }
    if (level->level > 0 && level->istrap == 1)
        mvprintw(level->trap->y, level->trap->x, "^");
    Printplayer(level->user);
    if (level->level != 3)
        mvprintw(level->stair->y, level->stair->x, ">");
    if (level->level > 0){
        mvprintw(level->stairP->y, level->stairP->x, "<");
    }
    move(level->user->pos->y, level->user->pos->x);

    if (level->Hfood->is_there == 1){
        attron(COLOR_PAIR(11));
        mvprintw(48, 135, "HIGH QUALITY FOOD ABILITY ENABLED!");
        attroff(COLOR_PAIR(11));
        move(level->user->pos->y, level->user->pos->x);
    }
    if (level->countHfood % 50 == 1){
        level->Hfood->is_there = 0;
        level->user->attack /= 2;
        level->countHfood = 2;
        attron(COLOR_PAIR(11));
        mvprintw(48, 135, "                                     ");
        attroff(COLOR_PAIR(11));
        move(level->user->pos->y, level->user->pos->x);
    }
}

int gotonextlevel(Game *game, playerG *player){
    if (game->levels[game->clevel + 1]->is_there == 1){
        game->clevel++;
        player->pos->y = game->levels[game->clevel]->stairP->y;
        player->pos->x = game->levels[game->clevel]->stairP->x;
    }
    else {
        game->clevel++;
        game->levels[game->clevel] = createnewlevel(game->clevel, game->levels[game->clevel], player, game);
    }
}

int gotopreviouslevel(Game *game, playerG *player){
    game->clevel--;
    player->pos->y = game->levels[game->clevel]->stair->y;
    player->pos->x = game->levels[game->clevel]->stair->x;
    return 1;
}