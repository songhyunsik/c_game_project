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
int next_block_number;
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
            firststart++;
    }

    display_tetris();
    check_one_line();

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

    if (x == 3 && y == 0)
    {
        if (collision_test(LEFT) || collision_test(RIGHT) || collision_test(DOWN) || collision_test(ROTATE))
        {
            printf("\n Game End! \n");
            downcount = 0;
            setcount = 0;
            speedcount = 0;
            countrange = 5;
            firststart = 0;
            game = GAME_END;
        }
    }

    if (collision_test(DOWN))
    {
        if (setcount == 9)
        {
            block_number = next_block_number;
            next_block_number = rand() % 7;
            block_state = 0;
            x = 3;
            y = 0;
        }
        setcount++;
        setcount %= 10;
    }

    ch = getch();

    switch (ch)
    {
    case 74:
    case 106:
        move_block(LEFT);
        break;
    case 76:
    case 108:
        move_block(RIGHT);
        break;
    case 75:
    case 107:
        move_block(DOWN);
        break;
    case 73:
    case 105:
        move_block(ROTATE);
        break;
    case 65:
    case 97:
        drop();
        break;
    case 80:
    case 112:
        downcount = 0;
        setcount = 0;
        speedcount = 0;
        countrange = 5;
        firststart = 0;
        game = GAME_END;
        break;
    default:
        break;
    }
    return 0;
}

/**
 * ------------------------------------------------------------------------------------
 * @file update.c
 * 
 * int move_block(int command)
 * @brief int move_block(int command) -- 테트리스 게임에서 블록의 삭제, 생성, 종류 부분을 담당하는 함수이다.
 * @author 정현우
 * @date 2024-3-20
 * @param command:  충돌값 테스트를 담당하는 매개 변수이다. 이후 switch문을 이용하여 블록의 종류, 삭제, 추가부분을 판단한다.  
 * @details 블록 종류에 맞게 연결, old_block 제거블록, new_block 추가를 담당
 * 
 * ------------------------------------------------------------------------------------
 */

/*이동, 회전키가 입력되면, 충돌검사후 이동시킨다*/
int move_block(int command)
{
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
        case LEFT:
            newx--;
            break;
        case RIGHT:
            newx++;
            break;
        case DOWN:
            newy++;
            break;
        case ROTATE:
            block_state++;
            block_state %= 4;
            break;
        }
    }
    else
    {
        return 1;
    }

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
        block_pointer = &l_block;
        break;
    case 5:
        block_pointer = &j_block;
        break;
    case 6:
        block_pointer = &o_block;
        break;
    }

        for (i = 0, oldy = y; i < 4; i++, oldy++)
    {
        for (j = 0, oldx = x; j < 4; j++, oldx++)
        {
            if (oldx > 0 && oldx < 9 && oldy < 20 && oldy > 0)
                if ((*block_pointer)[old_block_state][i][j] == 1)
                    tetris_table[oldy][oldx] = 0;
        }
    }

    x = newx;
    y = newy;

    for (i = 0, newy = y; i < 4; i++, newy++)
    {
        for (j = 0, newx = x; j < 4; j++, newx++)
        {
            if (newx > 0 && newx < 9 && newy < 20 && newy > 0)
                if ((*block_pointer)[block_state][i][j] == 1)
                    tetris_table[newy][newx] = (*block_pointer)[block_state][i][j];
        }
    }

    return 0;
}

/* 블록이 이동, 회전하기 전에 충돌되는 블록이나 벽이 없는지 확인하는 함수*/
int collision_test(int command)
{
    int i, j;
    int tempx, tempy;
    int oldx, oldy;
    int temp_block_state;
    int(*block_pointer)[4][4][4];
    int temp_tetris_table[21][10];

    oldx = tempx = x;
    oldy = tempy = y;
    temp_block_state = block_state;

    switch (command)
    {
    case LEFT:
        tempx--;
        break;
    case RIGHT:
        tempx++;
        break;
    case DOWN:
        tempy++;
        break;
    case ROTATE:
        temp_block_state++;
        temp_block_state %= 4;
        break;
    }

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
        block_pointer = &l_block;
        break;
    case 5:
        block_pointer = &j_block;
        break;
    case 6:
        block_pointer = &o_block;
        break;
    }

    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 10; j++)
        {
            temp_tetris_table[i][j] = tetris_table[i][j];
        }
    }

    for (i = 0, oldy = y; i < 4; i++, oldy++)
    {
        for (j = 0, oldx = x; j < 4; j++, oldx++)
        {
            if (oldx > 0 && oldx < 9 && oldy < 20 && oldy > 0)
            {
                if ((*block_pointer)[block_state][i][j] == 1)
                    temp_tetris_table[oldy][oldx] = 0;
            }
        }
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {

            if (temp_tetris_table[tempy + i][tempx + j] == 1 && (*block_pointer)[temp_block_state][i][j] == 1)
                return 1;
        }
    }

    return 0;
}

/**
 * ------------------------------------------------------------------------------------
 * @file update.c
 * 
 * int drop(void)
 * @brief int drop(void) -- 게임에서 블록이 맨 밑에 충돌되기 전까지 다운을 시켜주는 함수이다. 
 * @author 정현우
 * @date 2024-3-20
 * @param DOWN:  위에서 선언한 함수로, 블록의 방향을 담당한다. DOWN을 사용할시, 블록의 y값이 증가하여 밑으로 내려가게된다.  
 * @details while (!collision_test(DOWN)) --> 블록이 맨 마지막에 충돌할때까지,
 * @details move_block(DOWN) --> 블록이 다운된다.
 * 
 * ------------------------------------------------------------------------------------
 */
/* 충돌되기 전까지 블록을 다운시킨다.*/
int drop(void)
{
    while (!collision_test(DOWN))
        move_block(DOWN);

    return 0;
}

/* 한줄이 완성되었는지 확인하는 함수. 완성되면 한줄을 지우고, 점수에 1000점을 더한다*/
int check_one_line(void)
{
    int i, j;
    int ti, tj;
    int line_hole;

    for (i = 19; i > 0; i--)
    {
        line_hole = 0;
        for (j = 1; j < 9; j++)
        {
            if (tetris_table[i][j] == 0)
            {
                line_hole = 1;
            }
        }

        if (line_hole == 0)
        {
            point += 1000;
            for (ti = i; ti > 0; ti--)
            {
                for (tj = 0; tj < 9; tj++)
                {
                    tetris_table[ti][tj] = tetris_table[ti - 1][tj];
                }
            }
        }
    }

    return 0;
}