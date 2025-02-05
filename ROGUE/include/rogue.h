#ifndef ROGUE_H
#define ROGUE_H

// ! Macroes ! //
#define _XOPEN_SOURCE_EXTENDED
#define MAX_HEIGHT 49
#define MAX_WIDTH 190
#define CHAR_MASK 0xFF
#define _GNU_SOURCE

// ! Libraries ! //
#include<stdio.h>
#include <locale.h>
#include <curses.h>
#include <ncursesw/ncurses.h>
#include <wchar.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <pthread.h>
#include <SDL2/SDL_mixer.h>
#include<time.h>
#include<regex.h>
#include "rogue.h"


// ! Structs ! //
typedef struct Position{
    int x;
    int y;
    int is_there;
    int roomesh;
} Position;

typedef struct isthere{
    int is_there;
} isthere;

typedef struct Food{
    char shape;
    Position *pos;
    int type;
    int recoveryAmount;
    int is_there;
    int roomesh;
    int color;
} Food;


typedef struct Weapon{
    Position *pos;
    int damage;
    int durability;
    int range;
    int ability;
    wchar_t name[10];
    int is_there;
    int type; // 1 for mace ....  5 for sword
    int roomesh;
    int isthrowable;
} Weapon;

typedef struct Potion{
    char shape;
    Position *pos;
    int type;
    int ability;
    int is_there;
    int roomesh;
    int color;
    wchar_t name[10];
} Potion;

typedef struct Gold{
    Position *pos;
    int value;
    int is_there;
    int roomesh;
} Gold;

typedef struct Player{
    char name[50];
    char password[40];
    char email[60];
    int score;
    int color;
    char character;
    int gold;
    int xp;
} Player;

typedef struct playerG{
    Position *pos;
    int health;
    int attack;
    int gold;
    int maxhealth;
    int xp;
    char symbol;
    struct Room *room;
    Food *food[5];
    int food_num;
    struct Potion *potion[50];
    int potion_num;
    struct Weapon *weapons[200];
    struct Weapon *selected_weapon;
    int weapons_num;
    int hunger;
    int maxhunger;
    int distance;
    char name[50];
    char password[40];
    char email[60];
    int color;
    char character;
} playerG;

typedef struct Game{
    struct Level *levels[4];
    int clevel;
    int dificulty;
    int guest;
    int password;
    playerG *player;
} Game;

typedef struct Pathgrid{
    int visited;
    char tile;
    int flag;
} Pathgrid;

typedef struct QueueNode{
    int y, x;
} QueueNode;



typedef struct Monster{
    char buff[2];
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    Position *pos;
    int pathfinding;
    int move_count;
    int roomesh;
} Monster;

typedef struct Level
{
    char **tiles;
    int level;
    struct Room ** rooms;
    struct Room * treasure_room;
    struct Room * battle_room;
    struct Room * potion_room;
    Position *trap;
    int roomnum;
    struct Monster **monsters;
    int monsternum;
    struct Gold **golds;
    struct Gold *Taloysia;
    Position *Tdoor;
    int gold_num;
    struct Food **foods;
    int food_num;
    struct Potion **potions;
    int potion_num;
    struct Weapon **weapons;
    int weapons_num;
    struct playerG *user;
    int count;
    Position *stair;
    Position *stairP;
    int is_there;
    int istrap;
    Pathgrid **pathGrid[8];
    int countshaf;
    int countHfood;
    isthere *Hfood;
    int sabet;
    int is_speed;
    int isPdoor;
    int speedcounter;
    Position *key;
    Position *Pdoor;
    int password;
} Level;

typedef struct Room{
    Monster **monsters;
    int monsternum;
    Potion **potions;
    int potionnum;
    Position pos;
    int height;
    int width;
    Gold **gold;
    Gold **taloysia;
    int taloysia_num;
    int gold_num;
    Position *pillar[3];
    Position **door;
    Position **window;
    int is_there;
}Room;

// ! Desplay Functions ! //

int start(Game *game, playerG *players);
int setupscreen();
Position* user_input(int ch, Level *level);
int checkposition(Position *newposition, Level *level,  Game *game, playerG *player, char charrr);
int gamestats(Level *level);
void display(Game *game);
void gameover(playerG* player);
void win(playerG *player);
void credits();

// ! Player Functions ! //

playerG *playersetup(playerG *newplayer);
int playermove(Position *newpos, playerG *user);
void Printplayer(playerG *player);
void fmovement(Position *pos, int x, int y, char dir);
bool is_traversable(char tile);
bool is_traversablethrow(char tile);

// ! Room Functions ! //

Room** roomsetup(Level *level);
Room* createRoom(int y, int x, int height, int width);
int findroom(Position* pos, Level *level);
int Printroom(Room *room);
int Printroomvisited(Room *room);
int battleroom(Game *game);
Room* createbattleroom(int y, int x, int height, int width);
int PrintBroom(Room *room);
int treasureroom(Game *game);
Room* createtreasureroom(int y, int x, int height, int width);
int  get_room_for_position(Position *pos, Level *level);
int check_barriers_along_path(Position *pos, int x, int y, char dir);

// ! Level Functions ! //

char ** savelevel();
Level *createlevel(int level, playerG *user, Game *game);
Level *createnewlevel(int level, Level *newlevel, playerG *player, Game *game);
int gotonextlevel(Game *game, playerG *player);
int gotopreviouslevel(Game *game, playerG *player);
void Printlevel(Level *level);
void Printlevelm(Level *level);

// ! Gold Functions ! //

void PrintgoldT(Room *room);
int addgoldT(Room *Troom);
int consume_goldT(Level *level, Gold *gold, int* count);
int consume_taloysiaT(Level *level, Gold *gold, int* count);
int addgold(Level *level);
Position *randompos(Room* room);
void Printgold(Level *level);
Gold* findgold(Position* pos, Gold** golds);
Gold* findgoldT(Position* pos, Gold** golds, int treasure_num);
int consume_gold(Level *level, Gold *gold);
int consume_taloysia(Level *level, Gold *gold);

// ! Monster Functions ! //

int addmonsters(Level *level, Game *game);
Monster *selectMonster(int level, int x);
Monster *createmonster(char symbol, int health, int attack, int speed, int defence, int pathfinding, int roomesh);
int addmonsterBR(Room *room);
int movemonsterBR(Room *room, playerG * user);
int path5BR(Room *room, Position *posmonst, Position *posplayer);
int checkpositionBR(Position *newposition, Level *level, Game *game, playerG *player, int *x, int *y, int *z);
Monster* findmonstBR(Position* pos, Monster** monsters, int monsternum);
int combatBR(playerG* player, Monster* monster, int ord, int *x);
int combat(playerG* player, Monster* monster, int ord);
void Printmonster(Monster* monst);
int SetStartPos(Monster *monster, Room *room);
int movemonster(Level *level);
int pathfinding(Position *start, Position *end);
int pathrand(Position *pos);
int path5(Level *level, Position *posmonst, Position *posplayer);
Monster* findmonst(Position* pos, Monster** monsters);

// ! Hallway Functions ! //

void pathFind(Position *start, Position *end, Pathgrid** pathGrid);
void printpath(Position *pos, Level *level);
void printpathvisited(Level *level);
void printpathvisitedM(Level *level);
void shuffleDirections(int directions[4][2]);

// ! Food Functions ! //

int addfood(Level *level);
Food *selectfood(int x);
Food *createfood(char symbol, int recovery, int ability, int type, int roomesh, int color);
void foodpos(Food* food, Room* room);
void Printfood(Food *food);
Food* findfood(Position* pos, Food** foods);
int grabfood(Level *level, Food *food);
int findfoodinven(Food **food, int type, int food_num);
int backpack(Level *level);

// ! Potion Functions ! //

int addpotion(Level *level);
Potion *selectpotion(int x);
Potion *createpotion(wchar_t symbol[], int ability, int type, int roomesh, int color);
void potionpos(Potion* potion, Room* room);
void Printpotion(Potion *potion);
Potion* findpotion(Position* pos, Potion** potions);
int grabpotion(Level *level, Potion *potion);
int findpotioninven(Potion **potion, int type, int potion_num);
int potionbag(Level *level);
int potionroom(Game *game);
void PrintPotionT(Room *room);
int grab_potionT(Level *level, Potion *potion, int* count);

// ! Weapon Functions ! //

int addweapon(Level *level);
Weapon *selectweapon(int i);
Weapon *createweapon(wchar_t symbol[], int damage, int range, int ability, int durability, int type, int roomesh, int isthrowable);
void weaponpos(Weapon* weapon, Room* room);
void Printweapon(Weapon *weapon);
Weapon *findweapon(Position* pos, Weapon** weapons);
int grabweapon(Level *level, Weapon *weapon);
int inventory(Level *level);
int findweaponinven(Weapon **weapon, int type, int weapon_num);
Monster* throwfindmonster(playerG *player,Monster** monsters, int direction);
int throwweapon(playerG* player, Monster* monster, Weapon *weapon, int direction);
Room* createpotionroom(int y, int x, int height, int width);
int addpotionBR(Room *room);
Potion* findpotionBR(Position* pos, Potion** potions, int potionnum);
void movementthrow(Position *pos, int x, int y, char dir, int range, int* ismonster);


// ! Menu Functions ! //
int SCORE_BOARDV(int height, int width, Player players[], Game *game);
int SCORE_BOARDL(int height, int width, Player players[], Game *game);
int load_players(Player players[], const char *filename, Game* game);
int comparePlayers(const void *a, const void *b);
int loading_screen();
int main_menu(int height, int width, Player player, Game* game);
int handle_inputs(int height, int width, Player players[], Game *game);
int OPTIONS(int height, int width, Player players, Game* game);
int MUSIC_SELECTION(int height, int width);
int dificulty(int height, int width, Game *game);
void *play_music_background(void *arg);
// pthread_t music_thread;
void start_music(const char *music_file);
void play_music(const char *file);
void stop_music();
int SCORE_BOARD(int height, int width, Player players[], Game* game);
int new_player(int height, int width, Player players[], Game* game);
int checkpass(char password[]);
char *randompass();
int isValidEmail(const char *email);
int CHAR_DESIGN(int height, int width, Player players, Game* game);
int start_menu(int height, int width, Player players[], Game *game);
int login(int height, int width, Player players[], Game* game);
int profilemenu(int height, int width, char user[], char pass[], Game *game);


#endif