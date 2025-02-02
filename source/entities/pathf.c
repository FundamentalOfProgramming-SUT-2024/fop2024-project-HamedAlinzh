#include "rogue.h"

void shuffleDirections(int directions[4][2]) {
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int tempY = directions[i][0];
        int tempX = directions[i][1];
        directions[i][0] = directions[j][0];
        directions[i][1] = directions[j][1];
        directions[j][0] = tempY;
        directions[j][1] = tempX;
    }
}

int checkpos(int y, int x) {
    char temp = mvinch(y, x);
    if (temp == '.' || temp == '|' || temp == '-') {
        return 0;
    } else {
        return 1;
    }
}

void pathFind(Position *start, Position *end, Pathgrid **pathGrid) {
    int cameFrom[MAX_HEIGHT][MAX_WIDTH];
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    QueueNode queue[MAX_HEIGHT * MAX_WIDTH];
    int front = 0, back = 0;

    // Initialize cameFrom and mark cells as unvisited
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            cameFrom[i][j] = -1;
            pathGrid[i][j].visited = 0;  // Changed to .visited
        }
    }

    // Start BFS
    queue[back++] = (QueueNode){start->y, start->x};
    pathGrid[start->y][start->x].visited = 1;  // Changed to .visited
    // cameFrom[start->y][start->x] = -9;

    while (front < back) {
        QueueNode current = queue[front++];
        int y = current.y;
        int x = current.x;

        if (y == end->y && x == end->x) break;

        shuffleDirections(directions);  // Optional: shuffle directions

        for (int i = 0; i < 4; i++) {
            int ny = y + directions[i][0];
            int nx = x + directions[i][1];

            if (ny >= 0 && ny < MAX_HEIGHT && nx >= 0 && nx < MAX_WIDTH && 
                !pathGrid[ny][nx].visited && checkpos(ny, nx)) {  // Changed to .visited
                queue[back++] = (QueueNode){ny, nx};
                pathGrid[ny][nx].visited = 1;  // Changed to .visited
                cameFrom[ny][nx] = y * MAX_WIDTH + x;
            }
        }
    }

    // Trace back and mark path
    int y = end->y;
    int x = end->x;

    while (cameFrom[y][x] != -1) {
        int parent = cameFrom[y][x];
        y = parent / MAX_WIDTH;
        x = parent % MAX_WIDTH;

        if ((y != start->y || x != start->x) && (y != end->y || x != end->x)) {
            pathGrid[y][x].tile = '#';  // Changed to .tile
        }
    }
    refresh();
}

void printpath(Position *pos, Level *level){
    for (int i = 0; i < 8; i++){
        if (level->pathGrid[i][pos->y][pos->x + 1].tile == '#'){
            mvprintw(pos->y, pos->x + 1, "#");
            level->pathGrid[i][pos->y][pos->x + 1].flag = 1;
        }
        if (level->pathGrid[i][pos->y][pos->x - 1].tile == '#'){
            mvprintw(pos->y, pos->x - 1, "#");
            level->pathGrid[i][pos->y][pos->x - 1].flag = 1;
        }
        if (level->pathGrid[i][pos->y + 1][pos->x].tile == '#'){
            mvprintw(pos->y + 1, pos->x, "#");
            level->pathGrid[i][pos->y + 1][pos->x].flag = 1;
        }
        if (level->pathGrid[i][pos->y - 1][pos->x].tile == '#'){
            mvprintw(pos->y - 1, pos->x, "#");
            level->pathGrid[i][pos->y - 1][pos->x].flag = 1;
        }
    }
}

void printpathvisited(Level *level) {
    for (int i = 0; i < 8; i++) {
        for (int y = 0; y < MAX_HEIGHT; y++) {
            for (int x = 0; x < MAX_WIDTH; x++) {
                if (level->pathGrid[i][y][x].tile == '#' && level->pathGrid[i][y][x].flag == 1) {
                    mvprintw(y, x, "#");
                }
            }
        }
    }
}

void printpathvisitedM(Level *level) {
    for (int i = 0; i < 8; i++) {
        for (int y = 0; y < MAX_HEIGHT; y++) {
            for (int x = 0; x < MAX_WIDTH; x++) {
                if (level->pathGrid[i][y][x].tile == '#') {
                    mvprintw(y, x, "#");
                }
            }
        }
    }
}