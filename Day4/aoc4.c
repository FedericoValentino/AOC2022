#include <stdio.h>

int main()
{
    FILE* input = fopen("../Day4/input.txt", "r");
    if(input == NULL)
    {
        return -1;
    }

    int start;
    int finish;
    int start1;
    int finish1;

    int total = 0;

    while(!feof(input))
    {
        fscanf(input, "%d-%d,%d-%d", &start, &finish, &start1, &finish1);

        if((start <= start1 && start1 <= finish) || (start1 <= start && start <= finish1))
        {
            total++;
        }

    }
    printf("%d", total);

}