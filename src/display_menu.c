#include <stdio.h>
#include <stdlib.h>

int display_menu()
{
    int menu;

    system("clear");

    printf("Tetris csk\n");
    printf("-------------------\n");
    printf("\t\tGAME MENU\n");
    printf("-------------------\n");
    printf("1. Game Start\n");
    printf("2. Search history\n");
    printf("3. Record Output\n");
    printf("4. Quit\n");

    scanf("%d", &menu);
    return menu;
}