#include <stdio.h>



#define MARKER_SIZE 14
void push(char marker[], char c)
{
    for(int i = 0; i < MARKER_SIZE - 1; i++)
    {
        marker[i] = marker[i+1];
    }
    marker[MARKER_SIZE-1] = c;
}

int allDifferent(char marker[])
{
    for(int i = 0; i < MARKER_SIZE; i++)
    {
        for(int j = i+1; j < MARKER_SIZE; j++)
        {
            if(marker[i] == marker[j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    FILE *input = fopen("../Day6/input.txt", "r");
    if (input == NULL) {
        return -1;
    }

    char marker[MARKER_SIZE];

    for(int i = 0; i < MARKER_SIZE; i++)
    {
        marker[i] = fgetc(input);
    }

    int characterRead = MARKER_SIZE;

    while(!feof(input))
    {
        char c = fgetc(input);
        characterRead++;
        push(marker, c);
        if(allDifferent(marker) == 1)
        {
            break;
        }
    }

    printf("%d", characterRead);
}