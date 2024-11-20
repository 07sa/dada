#include <stdio.h>

char A[3][3] = {{' ', ' ', ' '},
                {' ', ' ', ' '},
                {' ', ' ', ' '}};

int check()
{
    for (int i = 0; i < 3; i++)
    {
        if (A[i][1] == A[i][2] && A[i][2] == A[i][0] && A[i][i] != ' ')
        {
            return 1;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (A[1][i] == A[2][i] && A[2][i] == A[0][i] && A[i][i] != ' ')
        {
            return 1;
        }
    }
    if (A[1][1] == A[2][2] && A[2][2] == A[0][0] && A[1][1] != ' ')
    {
        return 1;
    }
    if (A[0][2] == A[1][1] && A[1][1] == A[2][0] && A[1][1] != ' ')
    {
        return 1;
    }
    return 0;
}

void board()
{
    printf("\n\n");
    for (int i = 0; i < 3; i++)
    {
        printf("-------------\n");
        printf("| %c | %c | %c |\n", A[i][0], A[i][1], A[i][2]);
    }
    printf("-------------\n");
}

int main()
{
    printf("\t\tWELCOME TO GAME\n\n");
    char player = 'X';
    int a, b;

    for (int i = 0; i < 9; i++)
    {
        printf("%c's Move : ", player);
        scanf("%d %d", &a, &b);
        if (a < 3 && b < 3 && A[a][b] == ' ')
        {
            A[a][b] = player;
            board();
        }
        else
        {
            printf("\tInvalid choice!!!!");
            i--;
            if (player == 'X')
            {
                player = 'O';
            }
            else
            {
                player = 'X';
            }
        }
        if (check() == 1)
        {
            printf("\n\n\t\tPlayer %c Wins!!!!!!!\n\n", player);
            return 0;
        }
        if (player == 'X')
        {
            player = 'O';
        }
        else
        {
            player = 'X';
        }
    }
    board();
}