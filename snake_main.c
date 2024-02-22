#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define GME_OVER 0;
#define GME_CONT 1;
const int BRD_WDTH = 20;
const int BRD_HGHT = 20;

typedef struct {
    int x;
    int y;
}pos;

void game_setup(pos* player, pos* dir, pos* fruit);
void generate_game(pos* player, pos* fruit);
int create_fruit_pos();
void get_input(pos* dir);
void process_input(pos* player, pos* dir, pos* fruit);

//make a que data structure
int score;
int game_state = GME_CONT;
int board_array[20][20];//have to implicitly type this as VLAs are not supported by vs code for c17 :(

void game_setup(pos* player, pos* dir, pos* fruit) {
       
    //starting positions
    player->x = 10;
    player->y = 10;
    dir->x = 0;
    dir->y = 0;

    // set up starting fruit positions
    fruit->x = rand() % (BRD_WDTH-1) + 1;
    fruit->y = rand() % (BRD_HGHT-1) + 1;

    //score
    score = 0;

    //setup board array
    for (int y = 0; y <= BRD_HGHT; y++) {
        for (int x = 0; x <= BRD_WDTH; x++) {
            if (x==0 || y==0 || x == BRD_WDTH || y == BRD_HGHT) {
                board_array[x][y] = 2;
            }else if (x == player->x && y == player->y) {
                board_array[x][y] = 1;
            }else {
                board_array[x][y] = 0;
            }
        }
    }
}

int create_fruit_pos() {

}

void generate_game(pos* player, pos* fruit) {
    system("cls");
    for (int y = 0; y <= BRD_HGHT; y++) {
        for (int x = 0; x <= BRD_WDTH; x++) {
            if (board_array[x][y] == 2) {
                printf("#");
            }else if (x== player->x && y== player->y) {
                printf("0");
            }else if (x== fruit->x && y== fruit->y) {
                printf("*");
            }else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void get_input(pos* dir) {
    if (kbhit()) {
        switch(getch()) { //prevents back travel
            case 'a':
                if (!(dir->x == 1)) {
                    dir->x = -1;
                    dir->y = 0;
                }
                break;
            case 'd':
                if (!(dir->x == -1)) {
                    dir->x = 1;
                    dir->y = 0;
                }
                break;
            case 's':
                if (!(dir->y == -1)) {
                    dir->y = 1;
                    dir->x = 0;
                }
                break;
            case 'w':
                if (!(dir->y == 1)) {
                    dir->y = -1;
                    dir->x = 0;
                }
                break;
            case 'x': //press to quite the game
                game_state = GME_OVER;
                break;
            default:
                break;
        }
    }
}

void process_input(pos* player, pos* dir, pos* fruit) {

    Sleep(500);
    player->x += dir->x;
    player->y += dir->y;
    
    //check not hitting border
    if (player->x <= 0 || player->y <= 0 || player->x >= BRD_WDTH || player->y >= BRD_HGHT) {
        game_state = GME_OVER;
        return;
    }

    //check if fruit is found
    
}


int main(int argc, char *argv[])
{
    pos* player_pos = (pos*)malloc(sizeof(player_pos));
    pos* fruit_pos = (pos*)malloc(sizeof(fruit_pos));
    pos* dir = (pos*)malloc(sizeof(dir));
    
    //setup game
    game_setup(player_pos, dir, fruit_pos);

    while (game_state) {
       generate_game(player_pos, fruit_pos);
       get_input(dir);
       process_input(player_pos, dir, fruit_pos);
    }
    return 0;
}
