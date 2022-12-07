#include <stdio.h>
#include <stdlib.h>

struct node
{
    char c;
    struct node* up;
    struct node* down;
};

typedef struct node StackNode;

struct stack
{
    StackNode* top;
};

typedef struct stack Stack;


void push(Stack* stack, StackNode* node)
{
    if(stack->top == NULL)
    {
        stack->top = node;
    }
    else
    {
        stack->top->up = node;
        node->down = stack->top;
        stack->top = node;
    }
}

StackNode* pop(Stack* stack)
{
    StackNode* node = stack->top;
    stack->top = stack->top->down;
    return node;
}

StackNode* newNode(char c)
{
    StackNode* node = malloc(sizeof(StackNode));
    node->down = NULL;
    node->up = NULL;
    node->c = c;
    return node;
}

int main()
{
    FILE* input = fopen("../Day5/input.txt", "r");
    if(input == NULL)
    {
        return -1;
    }

    Stack* stacks[9];

    for(int i = 0; i < 9; i++)
    {
        char c;
        stacks[i] = malloc(sizeof(Stack));
        stacks[i]->top = NULL;
        printf("Stack %d, insert elements\n", i+1);
        printf("Insert 0 to stop\n");
        do {
            scanf("%c", &c);
            if(c != '0' && c != '\n')
            {
                StackNode* node = newNode(c);
                push(stacks[i], node);
            }
        }while(c != '0');
    }

    Stack* tempStack = malloc(sizeof(Stack));
    tempStack->top = NULL;

    int amount = 0;
    int from = 0;
    int to = 0;

    while(!feof(input))
    {
        fscanf(input, "move %d from %d to %d\n", &amount, &from, &to);
        from--;
        to--;
        for(int i = 0; i < amount; i++)
        {
            StackNode* node = pop(stacks[from]);
            push(tempStack, node);
        }
        //pt2
        for(int i = 0; i < amount; i++)
        {
            StackNode* node = pop(tempStack);
            push(stacks[to], node);
        }
    }

    for(int i = 0; i < 9; i++)
    {
        printf("%c ", stacks[i]->top->c);
    }
}