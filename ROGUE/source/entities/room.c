#include "rogue.h"
Room* createRoom(int y, int x, int height, int width){
    Room *nroom;
    nroom = malloc(sizeof(Room));
    for (int i = 0; i < 3; i++){
        nroom->pillar[i] = malloc(sizeof(Position));
        nroom->pillar[i]->is_there = rand() % 2;
    }
    nroom->pos.y = y;
    nroom->pos.x = x;
    nroom->height = height;
    nroom->width = width;
    nroom->is_there = 0;
    nroom->door = malloc(sizeof(Position) * 4);
    nroom->window = malloc(sizeof(Position) * 2);

    nroom->window[0] = (Position*)malloc(sizeof(Position));
    nroom->window[1] = (Position*)malloc(sizeof(Position));
    nroom->window[1]->y = rand() % (height - 2) + nroom->pos.y + 1;
    nroom->window[1]->x = nroom->pos.x;
    nroom->window[0]->y = nroom->pos.y;
    nroom->window[0]->x = rand() % (width - 2) + nroom->pos.x + 1;
    nroom->window[0]->is_there = rand() % 2;
    nroom->window[1]->is_there = rand() % 2;

    // left door
    nroom->door[1] = (Position*)malloc(sizeof(Position));
    nroom->door[1]->y = rand() % (height - 2) + nroom->pos.y + 1;
    nroom->door[1]->x = nroom->pos.x;
    //right door
    nroom->door[3] = (Position*)malloc(sizeof(Position));
    nroom->door[3]->y = rand() % (height - 2) + nroom->pos.y + 1;
    nroom->door[3]->x = nroom->pos.x + nroom->width - 1;
    // top door
    nroom->door[0] = (Position*)malloc(sizeof(Position));
    nroom->door[0]->y = nroom->pos.y;
    nroom->door[0]->x = rand() % (width - 2) + nroom->pos.x + 1;
    // bottom door
    nroom->door[2] = (Position*)malloc(sizeof(Position));
    nroom->door[2]->y = nroom->height + nroom->pos.y - 1;
    nroom->door[2]->x = rand() % (width - 2) + nroom->pos.x + 1;
    nroom->pillar[0]->x = rand() % (nroom->width - 4) + nroom->pos.x + 2;
    nroom->pillar[0]->y = rand() % (nroom->height - 4) + nroom->pos.y + 2;
    nroom->pillar[1]->x = rand() % (nroom->width - 4) + nroom->pos.x + 2;
    nroom->pillar[1]->y = rand() % (nroom->height - 4) + nroom->pos.y + 2;
    nroom->pillar[2]->x = rand() % (nroom->width - 4) + nroom->pos.x + 2;
    nroom->pillar[2]->y = rand() % (nroom->height - 4) + nroom->pos.y + 2;
    return nroom;
}

Room* createbattleroom(int y, int x, int height, int width){
    Room *nroom;
    nroom = malloc(sizeof(Room));
    nroom->pos.y = y;
    nroom->pos.x = x;
    nroom->height = height;
    nroom->width = width;
    nroom->is_there = 1;
    addmonsterBR(nroom);

    return nroom;
}

int treasureroom(Game *game){
    clear();
    refresh();
    game->levels[game->clevel]->treasure_room = createtreasureroom((MAX_HEIGHT - 20) / 2, (MAX_WIDTH - 30) / 2, 20, 30);
}

int potionroom(Game *game){
    clear();
    refresh();
    game->levels[game->clevel]->potion_room = createpotionroom((MAX_HEIGHT - 10) / 2, (MAX_WIDTH - 20) / 2, 10, 20);
}

Room* createpotionroom(int y, int x, int height, int width){
    Room *nroom;
    nroom = malloc(sizeof(Room));
    nroom->pos.y = y;
    nroom->pos.x = x;
    nroom->height = height;
    nroom->width = width;
    nroom->is_there = 1;
    addpotionBR(nroom);

    return nroom;
}

int battleroom(Game *game){
    clear();
    refresh();
    game->levels[game->clevel]->battle_room = createbattleroom((MAX_HEIGHT - 20) / 2, (MAX_WIDTH - 30) / 2, 20, 30);
}

Room* createtreasureroom(int y, int x, int height, int width){
    Room *nroom;
    nroom = malloc(sizeof(Room));
    nroom->pos.y = y;
    nroom->pos.x = x;
    nroom->height = height;
    nroom->width = width;
    nroom->is_there = 1;
    addgoldT(nroom);

    return nroom;
}

int PrintBroom(Room *room) {
    // Print top and bottom walls
    for (int x = room->pos.x; x < room->pos.x + room->width; x++) {
        mvprintw(room->pos.y, x, "-");  // Top wall
        mvprintw(room->pos.y + room->height - 1, x, "-");  // Bottom wall
    }

    // Print left and right walls
    for (int y = room->pos.y + 1; y < room->pos.y + room->height - 1; y++) {
        mvprintw(y, room->pos.x, "|");  // Left wall
        mvprintw(y, room->pos.x + room->width - 1, "|");  // Right wall
    }

    // Fill the inside of the room with dots
    for (int y = room->pos.y + 1; y < room->pos.y + room->height - 1; y++) {
        for (int x = room->pos.x + 1; x < room->pos.x + room->width - 1; x++) {
            mvprintw(y, x, ".");  // Fill with dots
        }
    }
}

int Printroom(Room *room) {
    // Print top and bottom walls
    for (int x = room->pos.x; x < room->pos.x + room->width; x++) {
        mvprintw(room->pos.y, x, "-");  // Top wall
        mvprintw(room->pos.y + room->height - 1, x, "-");  // Bottom wall
    }

    // Print left and right walls
    for (int y = room->pos.y + 1; y < room->pos.y + room->height - 1; y++) {
        mvprintw(y, room->pos.x, "|");  // Left wall
        mvprintw(y, room->pos.x + room->width - 1, "|");  // Right wall
    }

    // Fill the inside of the room with dots
    for (int y = room->pos.y + 1; y < room->pos.y + room->height - 1; y++) {
        for (int x = room->pos.x + 1; x < room->pos.x + room->width - 1; x++) {
            mvprintw(y, x, ".");  // Fill with dots
        }
    }
    for (int i = 0; i < 2; i++){
        if (room->window[i]->is_there)
            mvprintw(room->window[i]->y, room->window[i]->x, "=");
    }
    // doors
    for (int i = 0; i < 4; i++){
        mvprintw(room->door[i]->y, room->door[i]->x, "+");
    }
    for (int i = 0; i < 3; i++){
        if (room->pillar[i]->is_there)
            mvprintw(room->pillar[i]->y, room->pillar[i]->x, "O");
    }
    return 1;
}

int Printroomvisited(Room *room) {
    if (room->is_there == 1){
        // Print top and bottom walls
        for (int x = room->pos.x; x < room->pos.x + room->width; x++) {
            mvprintw(room->pos.y, x, "-");  // Top wall
            mvprintw(room->pos.y + room->height - 1, x, "-");  // Bottom wall
        }

        // Print left and right walls
        for (int y = room->pos.y + 1; y < room->pos.y + room->height - 1; y++) {
            mvprintw(y, room->pos.x, "|");  // Left wall
            mvprintw(y, room->pos.x + room->width - 1, "|");  // Right wall
        }

        // Fill the inside of the room with dots
        for (int y = room->pos.y + 1; y < room->pos.y + room->height - 1; y++) {
            for (int x = room->pos.x + 1; x < room->pos.x + room->width - 1; x++) {
                mvprintw(y, x, ".");  // Fill with dots
            }
        }
        for (int i = 0; i < 2; i++){
            if (room->window[i]->is_there)
                mvprintw(room->window[i]->y, room->window[i]->x, "=");
            }
        // doors
        for (int i = 0; i < 4; i++){
            mvprintw(room->door[i]->y, room->door[i]->x, "+");
        }
        for (int i = 0; i < 3; i++){
            if (room->pillar[i]->is_there)
                mvprintw(room->pillar[i]->y, room->pillar[i]->x, "O");
        }
        return 1;
    }
}


int findroom(Position* pos, Level *level){
    for (int i = 0; i < level->roomnum; i++){
        for (int j = 0; j < 4; j++){
            if ((pos->y - 1 == level->rooms[i]->door[j]->y) && (pos->x == level->rooms[i]->door[j]->x)){
                return i;
            }
            if ((pos->y + 1 == level->rooms[i]->door[j]->y) && (pos->x == level->rooms[i]->door[j]->x)){
                return i;
            }
            if ((pos->y == level->rooms[i]->door[j]->y) && (pos->x + 1 == level->rooms[i]->door[j]->x)){
                return i;
            }
            if ((pos->y == level->rooms[i]->door[j]->y) && (pos->x - 1 == level->rooms[i]->door[j]->x)){
                return i;
            }
        }
    }
    return 7;
}

int  get_room_for_position(Position *pos, Level *level) {
    for (int i = 0; i < 6; i++) {
        if (pos->x >= level->rooms[i]->pos.x &&
            pos->x < level->rooms[i]->pos.x + level->rooms[i]->width &&
            pos->y >= level->rooms[i]->pos.y &&
            pos->y < level->rooms[i]->pos.y + level->rooms[i]->height) {
            return i;
        }
    }
    return 6;
}

