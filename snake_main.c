#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <assert.h>

#define GME_OVER 0;
#define GME_CONT 1;
const int BRD_WDTH = 20;
const int BRD_HGHT = 20;

typedef struct node node_t; //repesents a node 

typedef struct {
    int x;
    int y;
} pos_t;

struct node {
    pos_t* data;
    node_t* next;
};

typedef struct {
    node_t *head;
    node_t *tail;
} snake_t;

//snake tail functions
snake_t* insert_at_tail(snake_t*, int);
snake_t* make_new_snake(pos_t*);
snake_t* update_snake(snake_t*, pos_t*);

//game functions
void game_setup(pos_t* player, pos_t* dir, pos_t* fruit);
void generate_game(pos_t* player, pos_t* fruit);
void create_fruit_pos(pos_t* fruit);
void get_input(pos_t* dir);
void process_input(pos_t* player, pos_t* dir, pos_t* fruit);

//make a que data structure
int score;
int game_state = GME_CONT;
int board_array[20][20];//have to implicitly type this as VLAs are not supported by vs code for c17 :(

//snake tail functions
snake_t* make_new_snake(pos_t* player) {
    snake_t* snake;
    snake = (snake_t*)malloc(sizeof(*snake));

    node_t* snake_head;
    snake_head = (node_t*)malloc(sizeof(*snake_head));



}

//sets up game varibles 
void game_setup(pos_t* player, pos_t* dir, pos_t* fruit) {
       
    //starting positions
    player->x = BRD_WDTH/2;
    player->y = BRD_WDTH/2;
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

void create_fruit_pos(pos_t* fruit) {
    int x = rand() % (BRD_WDTH-1) + 1;
    int y = rand() % (BRD_HGHT-1) + 1;

    //if the position is on a free tile
    if (board_array[x][y] == 0) {
        fruit->x = x;
        fruit->y = y;
        return;
    }

    //systimatically using random input find a square that is unoccupied
    int up_or_down = (rand() % 2) * 2 - 1;
    for (int j = 0; j<BRD_HGHT; j++) {
        int left_or_right = (rand() % 2) * 2 - 1;
        for (int i = 0; i<=BRD_WDTH; i++) {
            x = x+left_or_right;
            if (board_array[x][y] == 0) {
                fruit->x = x;
                fruit->y = y;
                return;
            }
            if (x==BRD_WDTH) {
                x=0;
            }else if (x==0) {
            x=BRD_WDTH;
            }
        }
        y = y+up_or_down;
        if (y==BRD_HGHT) {
            y=0;
        }else if (y==0) {
            y=BRD_HGHT;
        }
    }

    //still not found
}   

void generate_game(pos_t* player, pos_t* fruit) {
    system("cls");
    for (int y = 0; y <= BRD_HGHT; y++) {
        for (int x = 0; x <= BRD_WDTH; x++) {
            if (board_array[x][y] == 2) {
                printf("#");
            }else if (x== player->x && y== player->y) {
                board_array[x][y] = 1;
                printf("0");
            }else if (x== fruit->x && y== fruit->y) {
                printf("*");
            }else {
                printf(" ");
            }
        }
        printf("\n");
    }
    
    //display score
    printf("\n");
    printf("Score: %d\n", score);
    printf("Press x to end.");
}

void get_input(pos_t* dir) {
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

void process_input(pos_t* player, pos_t* dir, pos_t* fruit) {

    Sleep(500);
    player->x += dir->x;
    player->y += dir->y;
    
    //check not hitting border
    if (player->x <= 0 || player->y <= 0 || player->x >= BRD_WDTH || player->y >= BRD_HGHT) {
        game_state = GME_OVER;
        return;
    }

    //check if fruit is found
    if (player->x==fruit->x&&player->y==fruit->y) {
        score++;
        create_fruit_pos(fruit);
    }

    //remove previous player pos from board
    board_array[player->x][player->y] = 0;

    
}


int main(int argc, char *argv[])
{
    pos_t* player_pos = (pos_t*)malloc(sizeof(player_pos));
    pos_t* fruit_pos = (pos_t*)malloc(sizeof(fruit_pos));
    pos_t* dir = (pos_t*)malloc(sizeof(dir));
    
    //setup game
    game_setup(player_pos, dir, fruit_pos);

    while (game_state) {
       generate_game(player_pos, fruit_pos);
       get_input(dir);
       process_input(player_pos, dir, fruit_pos);
    }
    return 0;
}
