#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define KNOT_AMOUNT 10

struct Knot
{
    int prevX;
    int prevY;
    int X;
    int Y;
};

typedef struct Knot Knot;

struct positions
{
    int x;
    int y;
    struct positions* next;
};

float distance(int x1, int y1, int x2, int y2)
{
    return floor(sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}

void changeKnotPos(Knot* tail, Knot* head)
{
    if (distance(tail->X, tail->Y, head->X, head->Y) > 1.0f)
    {
        if(tail->X == head->X)
        {
            if(head->Y > tail->Y)
            {
                tail->Y++;
            }
            else
            {
                tail->Y--;
            }
        }

        else if(tail->Y == head->Y)
        {
            if(head->X > tail->X)
            {
                tail->X++;
            }
            else
            {
                tail->X--;
            }
        }

        else
        {
            if(head->X > tail->X)
            {
                tail->X++;
            }
            else
            {
                tail->X--;
            }

            if(head->Y > tail->Y)
            {
                tail->Y++;
            }
            else
            {
                tail->Y--;
            }
        }

    }
}

int isVisited(struct positions * Positions, Knot* tail)
{
    struct positions* traveler = Positions;
    for(int i = 0; traveler != NULL; i++)
    {
        if(traveler->x == tail->X && traveler->y == tail->Y)
        {
            return 1;
        }
        traveler = traveler->next;
    }
    return 0;
}

void addPosition(Knot * tail, struct positions* Positions)
{
    struct positions* traveler = Positions;
    while(traveler->next != NULL)
    {
        traveler = traveler->next;
    }

    traveler->next = malloc(sizeof(struct positions));

    traveler = traveler->next;

    traveler->x = tail->X;
    traveler->y = tail->Y;
    traveler->next = NULL;
}

int main()
{
    FILE *input = fopen("../Day9/input.txt", "r");
    if (input == NULL) {
        return -1;
    }

    Knot* knots[KNOT_AMOUNT];

    for(int i = 0; i < KNOT_AMOUNT; i++)
    {
        knots[i] = malloc(sizeof(Knot));
        knots[i]->prevX = 0;
        knots[i]->prevY = 0;
        knots[i]->X = 0;
        knots[i]->Y = 0;
    }

    struct positions* Position = malloc(sizeof(struct positions));
    Position->x = 0;
    Position->y = 0;
    Position->next = NULL;



    char direction;
    int steps;
    int positions = 1;

    while(!feof(input))
    {
        fscanf(input, "%c %d\n", &direction, &steps);

        for(int i = 0; i < steps; i++)
        {
            for(int j = 0; j < KNOT_AMOUNT; j++)
            {
                knots[j]->prevX = knots[j]->X;
                knots[j]->prevY = knots[j]->Y;
            }

            switch (direction) {
                case 'R':
                    ;
                    knots[KNOT_AMOUNT-1]->X++;
                    for(int j = KNOT_AMOUNT - 2; j >= 0; j--)
                    {
                        changeKnotPos(knots[j], knots[j+1]);
                    }
                    break;
                case 'L':
                    knots[KNOT_AMOUNT-1]->X--;
                    for(int j = KNOT_AMOUNT - 2; j >= 0; j--)
                    {
                        changeKnotPos(knots[j], knots[j+1]);
                    }
                    break;
                case 'U':
                    knots[KNOT_AMOUNT-1]->Y++;
                    for(int j = KNOT_AMOUNT - 2; j >= 0; j--)
                    {
                        changeKnotPos(knots[j], knots[j+1]);
                    }
                    break;
                case 'D':
                    knots[KNOT_AMOUNT-1]->Y--;
                    for(int j = KNOT_AMOUNT - 2; j >= 0; j--)
                    {
                        changeKnotPos(knots[j], knots[j+1]);
                    }
                    break;
            }
            if(!isVisited(Position, knots[0]))
            {
                addPosition(knots[0], Position);
                positions++;
            }
        }

    }

    printf("%d", positions);

}