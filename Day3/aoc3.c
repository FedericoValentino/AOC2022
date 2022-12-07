#include <stdio.h>



int CharToHash(char c)
{
    if(c >= 97 && c <= 122)
    {
        return c - 96;
    }
    if(c >= 65 && c <= 90)
    {
        return c - 38;
    }
    return 0;
}

int HashToChar(int i)
{
    if(i >= 1 && i <= 26)
    {
        return i + 96;
    }
    if(i >= 27 && i <= 52)
    {
        return i + 38;
    }
    return 0;
}

int analyzePriorityPT1(char array[], int size)
{
    const int halfSize = size/2;

    int countFirstHalf[53] = {0};
    int countSecondHalf[53] = {0};

    for(int i = 0; i < halfSize; i++)
    {
        countFirstHalf[CharToHash(array[i])]++;
        countSecondHalf[CharToHash(array[i + halfSize])]++;
    }

    for(int i = 1; i < 53; i++)
    {
        if(countFirstHalf[i] > 0 && countSecondHalf[i] > 0)
        {
            return i;
        }
    }
    return 0;
}

int analyzeBadgePT2(char array[], int size, char array1[], int size1, char array2[], int size2)
{
    int countFirst[53] = {0};
    int countSecond[53] = {0};
    int countThird[53] = {0};


    for(int i = 0; i < size; i++)
    {
        countFirst[CharToHash(array[i])]++;
    }

    for(int i = 0; i < size1; i++)
    {
        countSecond[CharToHash(array1[i])]++;
    }

    for(int i = 0; i < size2; i++)
    {
        countThird[CharToHash(array2[i])]++;
    }


    for(int i = 1; i < 53; i++)
    {
        if(countFirst[i] > 0 && countSecond[i] > 0 && countThird[i] > 0)
        {
            return i;
        }
    }
    return 0;
}

int main()
{
    FILE* input = fopen("../Day3/input.txt", "r");
    if(input == NULL)
    {
        return -1;
    }

    char rucksack[500];
    char rucksack2[500];
    char rucksack3[500];
    char inputChar;
    int position;
    int position2;
    int position3;
    int totalpriority = 0;

    while(!feof(input))
    {
        position = 0;
        position2 = 0;
        position3 = 0;
        while ((inputChar = fgetc(input)) != '\n' && !feof(input))
        {
            rucksack[position] = inputChar;
            position++;
        }
        rucksack[position] = '\0';

        while ((inputChar = fgetc(input)) != '\n' && !feof(input))
        {
            rucksack2[position2] = inputChar;
            position2++;
        }
        rucksack2[position2] = '\0';

        while ((inputChar = fgetc(input)) != '\n' && !feof(input))
        {
            rucksack3[position3] = inputChar;
            position3++;
        }
        rucksack3[position3] = '\0';

        totalpriority += analyzeBadgePT2(rucksack, position, rucksack2, position2, rucksack3, position3);

        position = 0;
        position2 = 0;
        position3 = 0;


    }
    printf("%d", totalpriority);

}