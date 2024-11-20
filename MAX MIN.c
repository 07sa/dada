#include <stdio.h>
#include <conio.h>
char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
int checkwin();
void board();
int minimax(char, int);
int getBestMove();

int main()
{
    int player = 1, i, choice;

    char mark;
    do
    {
        board();
        player = (player % 2) ? 1 : 2;

        if (player == 1)
        {
            printf("Player %d, enter a number:  ", player);
            scanf("%d", &choice);

            mark = (player == 1) ? 'X' : 'O';

            if (choice >= 1 && choice <= 9 && square[choice] == choice + '0')
                square[choice] = mark;
            else
            {
                printf("Invalid move ");
                player--;
                getch();
            }
        }
        else
        {
            choice = getBestMove();
            mark = 'O';
            square[choice] = mark;
        }

        i = checkwin();
        player++;
    } while (i == -1);

    board();

    if (i == 1)
        printf("==>\aPlayer %d wins\n", --player);
    else
        printf("==>\aGame draw\n");

    getch();

    return 0;
}

int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;

    else if (square[4] == square[5] && square[5] == square[6])
        return 1;

    else if (square[7] == square[8] && square[8] == square[9])
        return 1;

    else if (square[1] == square[4] && square[4] == square[7])
        return 1;

    else if (square[2] == square[5] && square[5] == square[8])
        return 1;

    else if (square[3] == square[6] && square[6] == square[9])
        return 1;

    else if (square[1] == square[5] && square[5] == square[9])
        return 1;

    else if (square[3] == square[5] && square[5] == square[7])
        return 1;

    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
        != '7' && square[8] != '8' && square[9] != '9')
        return 0;
    else
        return -1;
}

void board()
{
   // system("cls");
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");

    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("__________________\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("__________________\n");
    printf("     |     |      \n");

    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("     |     |     \n\n");
}


int minimax(char player, int depth)
{
    int score;
    int i;
    int bestScore;
    int bestMove;

    if (checkwin() == 1)
        return depth - 10;
    else if (checkwin() == 2)
        return 100 - depth;    
    else if (checkwin() == 0)
        return 0;

    if (player == 'O')
    {
        bestScore = -1000;
        for (i = 1; i <= 9; i++)
        {
            if (square[i] == i + '0')
            {
                square[i] = 'O';
                score = minimax('X', depth + 1);
                square[i] = i + '0';
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }
        if (depth == 0)
            return bestMove;
        else
            return bestScore;
    }
    else
    {
        bestScore = 1000;
        for (i = 1; i <= 9; i++)
        {
            if (square[i] == i + '0')
            {
                square[i] = 'X';
                score = minimax('O', depth + 1);
                square[i] = i + '0';
                if (score < bestScore)
                {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }
        if (depth == 0)
            return bestMove;
        else
            return bestScore;
    }
}

int getBestMove()
{
    return minimax('O', 0);
}