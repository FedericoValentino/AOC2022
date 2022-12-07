#include <stdio.h>


int gameScorePT1(char me, char enemy)
{
    if(me == 'X')
    {
        if(enemy == 'A')
        {
            return 3 + 1;
        }
        else if(enemy == 'B')
        {
            return 0 + 1;
        }
        else
        {
            return 6 + 1;
        }
    }
    else if(me == 'Y')
    {
        if(enemy == 'A')
        {
            return 6 + 2;
        }
        else if(enemy == 'B')
        {
            return 3 + 2;
        }
        else
        {
            return 0 + 2;
        }
    }
    else
    {
        if(enemy == 'A')
        {
            return 0 + 3;
        }
        else if(enemy == 'B')
        {
            return 6 + 3;
        }
        else
        {
            return 3 + 3;
        }
    }
}


int gameScorePT2(char me, char enemy)
{
    if(me == 'X')
    {
        if(enemy == 'A')
        {
            return 3 + 0;
        }
        else if(enemy == 'B')
        {
            return 1 + 0;
        }
        else
        {
            return 2 + 0;
        }
    }
    else if(me == 'Y')
    {
        if(enemy == 'A')
        {
            return 1 + 3;
        }
        else if(enemy == 'B')
        {
            return 2 + 3;
        }
        else
        {
            return 3 + 3;
        }
    }
    else
    {
        if(enemy == 'A')
        {
            return 2 + 6;
        }
        else if(enemy == 'B')
        {
            return 3 + 6;
        }
        else
        {
            return 1 + 6;
        }
    }
}




int main()
{
    FILE* input = fopen("../Day2/input.txt", "r");
    if(input == NULL)
    {
        return -1;
    }

    char elfChoice;
    char playerChoice;
    int roundScorePT1 = 0;
    int roundScorePT2 = 0;

    while(!feof(input))
    {
        fscanf(input, "%c %c\n", &elfChoice, &playerChoice);

        roundScorePT1 += gameScorePT1(playerChoice, elfChoice);

        roundScorePT2 += gameScorePT2(playerChoice, elfChoice);
    }

    printf("Total score for PT1 = %d\nTotal score for PT2 = %d", roundScorePT1, roundScorePT2);
}