#include "rogue.h"

void display(Game *game){
    Printlevel(game->levels[game->clevel]);
    gamestats(game->levels[game->clevel]);
    move(game->levels[game->clevel]->user->pos->y, game->levels[game->clevel]->user->pos->x);
}

int start(Game *game, playerG *players){
    // playerr = malloc(sizeof(playerG));
    playerG *player = game->player;
    player = playersetup(player);
    srand(time(0));
    setlocale(LC_ALL, "");
    Position *newposition;
    Level *level;
    game->player->distance = 0;
    setupscreen();
    if (game->clevel == 0){
        game->levels[game->clevel] = createlevel(game->clevel, player, game);
    }
    for (int i = 1; i < 4; i++){
        game->levels[i] = malloc(sizeof(Level));
        game->levels[i]->is_there = 0;
    }
    level = game->levels[game->clevel];
    gamestats(game->levels[game->clevel]);
    char ch = 'w';
    int counter = 0;
    while (ch != 27){
        if (level->Hfood->is_there == 1){
            level->countHfood++;
        }
        level->countshaf++;
        level->speedcounter++;
        player = game->levels[game->clevel]->user;
        display(game);
        ch = getch();
        if (ch != 'W' && ch != 'w' && ch != 'a' && ch != 'A' && ch != 'd' && ch != 'D' && ch != 's' && ch != 'S' && ch != 'e'
            && ch != 'E' && ch != 'i' && ch != 'I' && ch != 'Q'&& ch != 'q' && ch != KEY_UP && ch != KEY_DOWN && ch != KEY_LEFT && ch != KEY_RIGHT 
            && ch != '>' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '6' && ch != '7' && ch != '8' 
            && ch != '9' && ch != 'p' && ch != 'P' && ch != 'f' && ch != 'F'){
            continue;
        }
        game->player->distance++;
        newposition = user_input(ch, game->levels[game->clevel]);
        if (game->levels[game->clevel]->is_speed == 0){
            movemonster(game->levels[game->clevel]);
        }
        else {
            if (counter % 2 == 0){
                movemonster(game->levels[game->clevel]);
            }
            counter++;
        }
        int a = checkposition(newposition, game->levels[game->clevel], game, player);
        move(game->levels[game->clevel]->user->pos->y, game->levels[game->clevel]->user->pos->x);
        if(player->health <= 0){
            clear();
            refresh();
            gameover(player);
            clear();
            refresh();
            credits();
            if (game->guest == 0){
                FILE *file = fopen("SCOREBOARD.txt", "r+");

                char username[256], password[256], email[256], buffer[256];
                char targetUsername[256];
                strcpy(targetUsername, game->player->name);
                int gold = player->gold;
                int xp = player->xp;

                long position;
                int found = 0;

                while (fgets(buffer, sizeof(buffer), file)) {
                    position = ftell(file); 
                    sscanf(buffer, " %s %s %s", username, password, email);

                    if (strcmp(username, targetUsername) == 0) {
                        fseek(file, position - strlen(buffer), SEEK_SET);  // -1 to skip the newline

                        // Overwrite the line with the updated information
                        fprintf(file, "%s %s %s %d %d\n", username, password, email, gold, xp);
                        
                        // Flush the file to ensure the data is written immediately
                        fflush(file);

                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    // If the username wasn't found, you could append it at the end
                    fprintf(file, "%s %s %s %d %d\n", targetUsername, "defaultPassword", "defaultEmail", gold, xp);
                }

                fclose(file); // Close the file
            }
            break;
        }
        
        if (a == 4) {
            clear();
            refresh();
            win(player);
            clear();
            refresh();
            credits();
            if (game->guest == 0){
                FILE *file = fopen("SCOREBOARD.txt", "r+"); // Open file for reading and writing

                if (file == NULL) {
                    // Handle error opening file
                    printf("Error opening SCOREBOARD.txt\n");
                    break;
                }

                char username[256], password[256], email[256], buffer[256];
                char targetUsername[256];
                strcpy(targetUsername, game->player->name); // Replace with the username you're searching for
                int gold = player->gold;
                int xp = player->xp;

                long position;
                int found = 0;

                // Read each line and check if it matches the target username
                while (fgets(buffer, sizeof(buffer), file)) {
                    position = ftell(file); // Save the current position of the file pointer
                    
                    // Read the line into variables
                    sscanf(buffer, "%s %s %s", username, password, email);

                    if (strcmp(username, targetUsername) == 0) {
                        // If the username matches, we found the line to modify

                        // Move the file pointer back to the beginning of the previous line
                        fseek(file, position - strlen(buffer) - 1, SEEK_SET);  // -1 to skip the newline

                        // Overwrite the line with the updated information
                        fprintf(file, "%s %s %s %d %d", username, password, email, gold, xp);
                        
                        // Flush the file to ensure the data is written immediately
                        fflush(file);

                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    // If the username wasn't found, you could append it at the end
                    fprintf(file, "%s %s %s %d %d\n", targetUsername, "defaultPassword", "defaultEmail", gold, xp);
                }

                fclose(file); // Close the file
            }
            break;
        }


    }
    endwin();
    return 0;
}
// int main(){
//     Game game;
//     game.clevel = 0;
//     start(&game);
// }
