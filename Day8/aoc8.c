#include <stdio.h>
#include<stdlib.h>

#define GRIDSIZE 99

struct ActualTree{
    int height;
    int visible;
};

typedef struct ActualTree ActualTree;

void analyzeTreeLine(ActualTree* grid[GRIDSIZE][GRIDSIZE])
{
    //from the top
    //current column
    for(int i = 1; i < GRIDSIZE; i++)
    {
        int maxHeight = grid[0][i]->height;
        for(int j = 1; j < GRIDSIZE; j++)
        {
            if(grid[j][i]->height > maxHeight)
            {
                grid[j][i]->visible = 1;
                maxHeight = grid[j][i]->height;
            }
            if(maxHeight == 9)
            {
                break;
            }
        }
    }

    //from the bottom
    //current column
    for(int i = 1; i < GRIDSIZE; i++)
    {
        int maxHeight = grid[GRIDSIZE-1][i]->height;
        for(int j = GRIDSIZE-2; j >= 0; j--)
        {
            if(grid[j][i]->height > maxHeight)
            {
                grid[j][i]->visible = 1;
                maxHeight = grid[j][i]->height;
            }
            if(maxHeight == 9)
            {
                break;
            }
        }
    }



    //from the left
    //current row
    for(int i = 1; i < GRIDSIZE; i++)
    {
        int maxHeight = grid[i][0]->height;
        for(int j = 1; j < GRIDSIZE; j++)
        {
            if(grid[i][j]->height > maxHeight)
            {
                grid[i][j]->visible = 1;
                maxHeight = grid[i][j]->height;
            }
            if(maxHeight == 9)
            {
                break;
            }
        }
    }




    //from the right
    //current row
    for(int i = 1; i < GRIDSIZE; i++)
    {
        int maxHeight = grid[i][GRIDSIZE-1]->height;
        for(int j = GRIDSIZE-2; j >= 0; j--)
        {
            if(grid[i][j]->height > maxHeight)
            {
                grid[i][j]->visible = 1;
                maxHeight = grid[i][j]->height;
            }
            if(maxHeight == 9)
            {
                break;
            }
        }
    }

}

int countVisible(ActualTree* grid[GRIDSIZE][GRIDSIZE])
{
    int totalVisible = 0;
    for(int i = 0; i < GRIDSIZE; i++)
    {
        for(int j = 0; j < GRIDSIZE; j++)
        {
            if(grid[i][j]->visible == 1)
            {
                totalVisible++;
            }
        }
    }
    return totalVisible;
}


int scenicScore(ActualTree* grid[GRIDSIZE][GRIDSIZE])
{
    int maxScenicScore = 0;
    for(int i = 1; i < GRIDSIZE; i++)
    {
        for(int j = 1; j < GRIDSIZE; j++)
        {
            int currentScenicScore;
            int countUp = 0;
            int countDown = 0;
            int countLeft = 0;
            int countRight = 0;

            for(int x = i+1; x < GRIDSIZE; x++)
            {
                countDown++;
                if(grid[i][j]->height <= grid[x][j]->height)
                {
                    break;
                }
            }

            for(int x = i-1; x>= 0; x--)
            {
                countUp++;
                if(grid[i][j]->height <= grid[x][j]->height)
                {
                    break;
                }
            }

            for(int x = j+1; x < GRIDSIZE; x++)
            {
                countRight++;
                if(grid[i][j]->height <= grid[i][x]->height)
                {
                    break;
                }
            }

            for(int x = j-1; x >= 0; x--)
            {
                countLeft++;
                if(grid[i][j]->height <= grid[i][x]->height)
                {
                    break;
                }
            }


            currentScenicScore = countRight * countLeft * countDown * countUp;
            if(currentScenicScore > maxScenicScore)
            {
                maxScenicScore = currentScenicScore;
            }
        }

    }
    return maxScenicScore;
}

int main()
{
    FILE *input = fopen("../Day8/input.txt", "r");
    if (input == NULL) {
        return -1;
    }

    ActualTree* grid[GRIDSIZE][GRIDSIZE];

    for(int i = 0; i < GRIDSIZE; i++)
    {
        for(int j = 0; j < GRIDSIZE; j++)
        {
            grid[i][j] = malloc(sizeof(ActualTree));
            char c;
            do {
                c = fgetc(input);
            }while(c  == '\n' && !feof(input));
            grid[i][j]->height = c - 48;
            if(i == 0 || j == 0 || j == GRIDSIZE-1 || i == GRIDSIZE-1)
            {
                grid[i][j]->visible = 1;
            }
            else
            {
                grid[i][j]->visible = 0;
            }
        }
    }

    analyzeTreeLine(grid);
    printf("Visible trees: %d\n", countVisible(grid));
    printf("Best Scenic Tree score is %d", scenicScore(grid));



}
