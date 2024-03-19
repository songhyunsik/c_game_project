#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

#define GAME_START 0
#define GAME_END 1

int display_menu();
void display_tetris();
int game;
int update(int signum);
int x = 3;
int y = 0;
int point = 0;
extern int tetris_table[21][10];

int game_start()
{
    // signal 설정
    static struct itimerval timer;
    signal(SIGVTALRM, update);
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 16667;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 16667;
    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    while (1)
    {
        if (game == GAME_END)
        {
            x = 3;
            y = 0;
            point = 0;
            return 1;
        }
    }
    game = GAME_END;
}

int main()
{
    int menu = 1;
    menu = display_menu();
    switch (menu)
    {
    case 1:
        game = GAME_START;
        init_tetris_table();
        menu = game_start();
        break;
    case 2:
        printf("Search history\n");
        break;
    case 3:
        printf("Record Output\n");
        break;
    case 4:
        printf("Quit\n");
        break;
    }
    return 0;
}

int init_tetris_table()
{
    int i, j;
    // 모든 데이터에 0을 넣는다.
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 10; j++)
        {
            tetris_table[i][j] = 0;
        }
    }
    // 맨 아래칸에 1 추가 (바닥)
    for (j = 1; j < 9; j++)
    {
        tetris_table[20][j] = 1;
    }
    // 양 옆에 1 추가 (벽)
    for (i = 0; i < 21; i++)
    {
        tetris_table[i][0] = 1;
        tetris_table[i][9] = 1;
    }
}