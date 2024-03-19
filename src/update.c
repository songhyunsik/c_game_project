#include <stdio.h>
#include <time.h>
#include <stdlib.h>

extern int x;
extern int y;
int block_state = 0;
extern int block[4][4][4];
extern int point;
extern int tetris_table[21][10];
int block_number;
char getch();
extern int game;
int i_block[4][4][4] =
    {
        {{1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 0, 0, 1},
         {0, 0, 0, 1},
         {0, 0, 0, 1},
         {0, 0, 0, 1}},
        {{0, 0, 0, 0},
         {0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0}},
        {{1, 0, 0, 0},
         {1, 0, 0, 0},
         {1, 0, 0, 0},
         {1, 0, 0, 0}}};

int t_block[4][4][4] =
    {
        {{1, 0, 0, 0},
         {1, 1, 0, 0},
         {1, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        {{0, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}}};

int s_block[4][4][4] =
    {
        {{1, 0, 0, 0},
         {1, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}};

int z_block[4][4][4] =
    {
        {{0, 1, 0, 0},
         {1, 1, 0, 0},
         {1, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 0, 1, 0},
         {0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 0, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}};

int l_block[4][4][4] =
    {
        {{1, 0, 0, 0},
         {1, 0, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 1, 0},
         {1, 0, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        {{0, 0, 1, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}};

int j_block[4][4][4] =
    {
        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0}},
        {{1, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 0, 0, 0},
         {1, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}};

int o_block[4][4][4] =
    {
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}};

#define GAME_START 0
#define GAME_END 1

typedef enum
{
    DOWN,
    LEFT,
    RIGHT,
    ROTATE
} COMMAND;

int update(int signum)
{
    static int downcount = 0;
    static int setcount = 0;
    static long speedcount = 0;
    static int countrange = 5;
    static int firststart = 0;
    char ch;

    srand((unsigned)time(NULL));
    if (firststart == 0)
    {
        block_number = rand() % 7;
        if (firststart == 0)
            firststart = 1;
    }
    display_tetris();

    // down speed setting
    if (downcount == countrange - 1)
    {
        point += 1;
        move_block(DOWN);
    }
    if (speedcount == 499)
    {
        if (countrange != 1)
            countrange--;
    }
    downcount++;
    downcount %= countrange;
    speedcount++;
    speedcount %= 500;

    // new block setting
    if (collision_test(DOWN))
    {
        if (setcount == 9)
        {
            // block_number = next_block_number;
            // next_block_number = rand() % 7;
            block_state = 0;
            x = 3;
            y = 0;
        }
        setcount++;
        setcount %= 10;
    }

    // keyboard input
    ch = getch();

    switch (ch)
    {
    case 106: // j
        move_block(LEFT);
        break;
    case 107: // k
        move_block(DOWN);
        break;
    case 108: // l
        move_block(RIGHT);
        break;
    case 105: // i
        move_block(ROTATE);
        break;
    case 112: // p
        game = GAME_END;
        break;
    default:
        break;
    }
    return 0;
}

int move_block(int command)
{
    printf("move_block\n");
    int i, j;
    int newx, newy;
    int oldx, oldy;
    int old_block_state;
    int(*block_pointer)[4][4][4] = NULL;

    newx = x;
    newy = y;
    old_block_state = block_state;

    if (collision_test(command) == 0)
    {
        switch (command)
        {
        case DOWN:
            newy++;
            break;
        case LEFT:
            newx--;
            break;
        case RIGHT:
            newx++;
            break;
        case ROTATE:
            block_state++;
            if (block_state > 3)
            {
                block_state = 0;
            }
            break;
        }
    }
    // 포인터가 블록 종류에 맞게 연결
    switch (block_number)
    {
    case 0:
        block_pointer = &i_block;
        break;
    case 1:
        block_pointer = &t_block;
        break;
    case 2:
        block_pointer = &s_block;
        break;
    case 3:
        block_pointer = &z_block;
        break;
    case 4:
        block_pointer = &j_block;
        break;
    case 5:
        block_pointer = &o_block;
        break;
    }

    // tetris_table 의 old_block 제거
    for (i = 0, oldy = y; i < 4; i++, oldy++)
    {
        for (j = 0, oldx = x; j < 4; j++, oldx++)
        {
            if (block[old_block_state][i][j] == 1)
            {
                tetris_table[oldy][oldx] = 0;
            }
        }
    }

    // tetris_table 에 new_block 추가
    x = newx;
    y = newy;
    for (i = 0, newy = y; i < 4; i++, newy++)
    {
        for (j = 0, newx = x; j < 4; j++, newx++)
        {
            if (newx > 0 && newx < 9 && newy < 20 && newy > 0)
            {
                tetris_table[newy][newx] = block[block_state][i][j];
            }
        }
    }
    return 0;
}

int collision_test(int command)
{
    int i, j;
    int tempx, tempy;
    int oldx, oldy;
    int temp_block_state;
    int temp_tetris_table[21][10];

    // daisy chain
    oldx = tempx = x;
    oldy = tempy = y;
    temp_block_state = block_state;

    switch (command)
    {
    case DOWN:
        tempy++;
        break;
    case LEFT:
        tempx--;
        break;
    case RIGHT:
        tempx++;
        break;
    case ROTATE:
        temp_block_state++;
        if (temp_block_state > 3)
        {
            temp_block_state = 0;
        }
        break;
    }
    // tetris_table 을 temp_tetris_table 로 복사
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 10; j++)
        {
            temp_tetris_table[i][j] = tetris_table[i][j];
        }
    }

    // collision check
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (temp_tetris_table[tempy + i][tempx + j] == 1 && block[temp_block_state][i][j] == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}