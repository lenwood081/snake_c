#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

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
    char body_char;
    pos_t data;
    node_t* next;
};

//will be a stack data type, first elemetn will be the most recently added
typedef struct {
    node_t *tail_tip;
    node_t *head;
} snake_t;

//snake tail functions
snake_t* make_new_snake(pos_t*);
snake_t* insert_at_tail(snake_t*);
snake_t* update_snake(snake_t*, pos_t*, pos_t*);

//game functions
void game_setup(pos_t*, pos_t*, pos_t*);
void generate_game(snake_t*, pos_t*);
void create_fruit_pos(pos_t*);
void get_input(pos_t*);
void process_input(pos_t*, pos_t*, pos_t*, snake_t*);

//make a que data structure
int score = 0;
int game_state = GME_CONT;
int board_array[20][20];//have to implicitly type this as VLAs are not supported by vs code for c17 :(



int main(int argc, char *argv[])
{
    pos_t* player_pos = (pos_t*)malloc(sizeof(player_pos));
    pos_t* fruit_pos = (pos_t*)malloc(sizeof(fruit_pos));
    pos_t* dir = (pos_t*)malloc(sizeof(dir));
    snake_t* snake;
    
    //setup game
    
    game_setup(player_pos, dir, fruit_pos);
    
    snake = make_new_snake(player_pos);
    node_t *tip = (node_t*)malloc(sizeof(*tip));
    while (game_state) {
       generate_game(snake, fruit_pos);
       get_input(dir);
       process_input(player_pos, dir, fruit_pos, snake);
    }

    return 0;
}


//snake tail functions
snake_t* make_new_snake(pos_t* player) {
    snake_t* snake;
    snake = (snake_t*)malloc(sizeof(*snake));
    assert(snake!=NULL);

    node_t* snake_head;
    snake_head = (node_t*)malloc(sizeof(*snake_head));
    assert(snake_head!=NULL);

    snake_head->data.x = player->x;
    snake_head->data.y = player->y;
    snake_head->body_char = '0';
    snake_head->next = NULL;


    snake->head = snake_head;
    snake->tail_tip = snake_head;
    

    return snake;
}

snake_t* insert_at_tail(snake_t* snake) {

    node_t *tip = (node_t*)malloc(sizeof(*tip));
    assert(snake!=NULL&&tip!=NULL);

    tip->data.x = 0;
    tip->data.y = 0;
    tip->body_char = '+';
    tip->next = snake->tail_tip;
    snake->tail_tip = tip;

    return snake;
}

snake_t* update_snake(snake_t* snake, pos_t* snake_head_pos, pos_t* dir) {
    node_t* current_node;
    current_node = snake->tail_tip;

    //determine char based on direction
    if (dir->x!=0) {
        snake->head->body_char = '-';
    } else if (dir->y!=0) {
        snake->head->body_char = '|';
    }

    while (current_node->next!=NULL) {
        current_node->data.x = current_node->next->data.x;
        current_node->data.y = current_node->next->data.y;
        current_node->body_char = current_node->next->body_char;
        current_node = current_node->next;
    }

    //for the head of the snake
    snake->head->data.x = snake_head_pos->x;
    snake->head->data.y = snake_head_pos->y;

    

    return snake;
}

//sets up game varibles 
void game_setup(pos_t* player, pos_t* dir, pos_t* fruit) {
    game_state = GME_CONT;
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
                board_array[x][y] = 3;
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

void generate_game(snake_t* snake, pos_t* fruit) {
    printf("\e[H\e[2J\e[3J"); //faster alternative to system("cls"); also system("cls") wasnt working
    for (int y = 0; y <= BRD_HGHT; y++) {
        for (int x = 0; x <= BRD_WDTH; x++) {
            if (board_array[x][y] == 2) {
                printf("#");
            }else if (board_array[x][y]== 3) {
                printf("0");
            }else if (board_array[x][y] == 1) {
                node_t* current_node;
                current_node = snake->tail_tip;
                while (current_node->next!=NULL) {
                    if (current_node->data.x==x&&current_node->data.y==y) {
                        printf("%c", current_node->body_char);
                        break;
                    }
                    current_node = current_node->next;
                }
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

void process_input(pos_t* player, pos_t* dir, pos_t* fruit, snake_t* snake) {

    Sleep(300);
    board_array[snake->head->data.x][snake->head->data.y] = 1;
    board_array[snake->tail_tip->data.x][snake->tail_tip->data.y] = 0;
    player->x += dir->x;
    player->y += dir->y;
    //check if fruit is found
    if (player->x==fruit->x&&player->y==fruit->y) {
        score+=1;
        create_fruit_pos(fruit);
        snake = insert_at_tail(snake);
        snake = update_snake(snake, player, dir);
        board_array[snake->tail_tip->data.x][snake->tail_tip->data.y] = 1;
    }else {
        snake = update_snake(snake, player, dir);
    }

    //check not hitting tail or border
    if (board_array[player->x][player->y] != 0) {
        game_state = GME_OVER;
        return;
    }
    board_array[player->x][player->y] = 3;

}



