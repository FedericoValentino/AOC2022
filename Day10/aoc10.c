#include<stdio.h>
#include<stdlib.h>

/*
addx 15     2 cycles x = 1 + 15 = 16;
addx -11    2 cycles x = 16 - 11 = 5;
addx 6      2 cycles x = 5 + 6 = 11;
addx -3     2 cycles x = 11 - 3 = 8;
addx 5      2 cycles x = 8 + 5 = 13;
addx -1     2 cycles x = 13 - 1 = 12;
addx -8     2 cycles x = 12 - 8 = 4;
addx 13     2 cycles x = 4 + 13 = 17;
addx 4      2 cycles x = 17 + 4 = 21;
noop        1 cycles x = 21;
addx -1     2 cycles-> first cycle x += 0 -> second cycle x = 21 - 1;
 */

int targetCycles[6] = {20, 60, 100, 140, 180, 220};
char CRT[240] = {0};

void drawOnCRT(int value, int cycle)
{
    int CRTrowCell = (cycle - 1) % 40;
    int CRTcell = (cycle-1) % 240;
    CRT[CRTcell] = '.';
    if(value >= -1 && value <= 41)
    {
        if(CRTrowCell == value - 1 || CRTrowCell == value || CRTrowCell == value + 1)
        {
            CRT[CRTcell] = '#';
        }
    }
}

void updateVariables(int* registerX, int* cycle, int Value)
{

    *cycle += 1;

    for(int i = 0; i < 6; i++)
    {
        if(*cycle == targetCycles[i])
        {
            targetCycles[i] = targetCycles[i] * *registerX;
        }
    }

    drawOnCRT(*registerX, *cycle);

    *registerX += Value;
}

void printCRT()
{
  for(int i = 0; i < 6; i++)
  {
      for(int j = 0; j < 40; j++)
      {
          printf("%c", CRT[i*40+j]);
      }
      printf("\n");
  }
}

int main()
{
    FILE *input = fopen("../Day10/input.txt", "r");
    if (input == NULL) {
        return -1;
    }

    int x = 1;
    int cycle = 0;
    int Value = 0;

    char command[5];

    command[4] = '\0';
    char inputChar;

    while(!feof(input))
    {
        for(int i = 0; i < 4; i++)
        {
            command[i] = fgetc(input);
        }


        if(command[0] == 'n')
        {
            updateVariables(&x, &cycle, 0);
            fgetc(input);
        }
        else
        {
            fgetc(input);
            updateVariables(&x, &cycle, 0);
            fscanf(input, "%d\n", &Value);
            updateVariables(&x, &cycle, Value);
        }

    }

    int sum = 0;

    for(int i = 0; i < 6; i++)
    {
        sum = sum + targetCycles[i];
    }

    printf("sum %d\n", sum);

    printCRT();



}