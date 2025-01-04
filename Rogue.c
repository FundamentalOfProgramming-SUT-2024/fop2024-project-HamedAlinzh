#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
typedef struct Position{
    int x;
    int y;
} Position;
typedef struct playerG{
    
    Position pos;
    int health;
    struct Room *room;
} playerG;

typedef struct Room{
    Position pos;
    int height;
    int width;
}Room;
playerG *playersetup();
int setupscreen();
int handle_input(int ch, playerG*user);
int playermove(int y, int x, playerG *user);
int checkposition(int Y, int X, playerG * user);
Room** mapsetup();
// Room functions
Room* createRoom(int y, int x, int height, int width);
int drawroom(Room *room);



int main(){
    srand(time(0));
    playerG *user;
    setupscreen();
    mapsetup();
    user = playersetup();
    int ch;
    while ((ch = getch()) != 27){
        handle_input(ch, user);
    }
    endwin();
    return 0;
}



playerG *playersetup(){
    playerG *newplayer;
    newplayer = (playerG*)malloc(sizeof(playerG));
    newplayer->pos.x = 4;
    newplayer->pos.y = 4;
    playermove(4, 4, newplayer);
    return newplayer;
}
int setupscreen(){
    initscr();
    noecho();
    return 1;
}
int handle_input(int ch, playerG *user){
    int Y;
    int X;
    switch (ch){
            //up
        case 'W':
        case 'w':
            Y = user->pos.y - 1;
            X = user->pos.x;
            break;
            //left
        case 'A':
        case 'a':
            Y = user->pos.y;
            X = user->pos.x - 1;
            break;
            //down
        case 'S':
        case 's':
            Y = user->pos.y + 1;
            X = user->pos.x;
            break;
            //right
        case 'D':
        case 'd':
            Y = user->pos.y;
            X = user->pos.x + 1;
            break;
    }
    checkposition(Y, X, user);
}

int playermove(int y, int x, playerG *user){
    mvprintw(user->pos.y, user->pos.x, ".");
    user->pos.y = y;
    user->pos.x = x;
    mvprintw(user->pos.y, user->pos.x, "@");
    move(user->pos.y, user->pos.x);
}
int checkposition(int Y, int X, playerG * user){
    int space;
    switch(mvinch(Y, X)){
        case '.':
            playermove(Y, X, user);
            break;
        default:
            move(user->pos.y, user->pos.x);
            break;
    }
}
Room** mapsetup(){
    Room **rooms;
    rooms = malloc(sizeof(Room) * 6);
    rooms[0] = createRoom(2, 2, 6, 8);
    drawroom(rooms[0]);
    rooms[1] = createRoom(8, 21, 6, 8);
    drawroom(rooms[1]);
    rooms[2] = createRoom(21, 70, 6, 8);
    drawroom(rooms[2]);
    rooms[3] = createRoom(5, 50, 6, 8);
    drawroom(rooms[3]);

    return rooms;
}
Room* createRoom(int y, int x, int height, int width){
    Room *nroom;
    nroom = malloc(sizeof(Room));
    nroom->pos.y = y;
    nroom->pos.x = x;
    nroom->height = height;
    nroom->width = width;
    return nroom;
}
int drawroom(Room *room) {
    // Draw top and bottom walls
    for (int x = room->pos.x; x < room->pos.x + room->width; x++) {
        mvprintw(room->pos.y, x, "-");  // Top wall
        mvprintw(room->pos.y + room->height - 1, x, "-");  // Bottom wall
    }

    // Draw left and right walls
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

    return 1;
}

