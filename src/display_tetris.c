#include "display_tetris.h"

void display_tetris()
{
    int i, j;
    system("clear");
    printf("Next Block\n");
    for (i = 0; i < 4; i++) // Next Bolock 형태 출력
    {
        printf("\n");
        for (j = 0; j < 4; j++)
        {
            if (block[0][i][j] == 1)
                printf("* ");
            else if (block[0][i][j] == 0)
                printf("o ");
        }
    } 
    printf("\n\n");
    printf("Tetris Table\n"); // 테트리스 게임부분 출력
    for (i = 2; i < 21; i++)
    {
        printf("\t");
        for (j = 0; j < 10; j++)
        {
            if (j == 0 || j == 9) // j가 양사이드 부분에 도달하였을떄
            {
                printf("│ "); // 막대기 출력해서 틀 잡기
            }
            else if (i == 20 && (j > 1 || j < 9)) // 테트리스 모형 맨 밑줄에 도달하였을때
            {
                printf("──"); // 바닥 만들어주기
            }
            else if (tetris_table[i][j] == 1)
                printf("* ");
            else if (tetris_table[i][j] == 0)
                printf("0 ");
        }
        printf("\n");
    }
}