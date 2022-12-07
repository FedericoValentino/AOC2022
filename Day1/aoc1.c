#include<stdio.h>
#include<stdlib.h>



struct Node{
    int elfNumber;
    int calories;
    struct Node* right;
    struct Node* left;
};

typedef struct Node ElfNode;

struct Tree{
    ElfNode* root;
};

typedef struct Tree ElfTree;


void bstInsertion(ElfTree * tree, ElfNode * node, ElfNode * toInsert)
{
    ElfNode * y = NULL;
    ElfNode * x = node;
    while(x != NULL)
    {
        y = x;
        if(toInsert->calories > x->calories)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    if(y == NULL)
    {
        tree->root = toInsert;
    }
    else if(toInsert->calories > y->calories)
    {
        y->left = toInsert;
    }
    else
    {
        y->right = toInsert;
    }
}

void InOrderPrint(ElfNode * node)
{
    if(node != NULL)
    {
        InOrderPrint(node->left);
        printf("Elf %d with calories %d\n", node->elfNumber, node->calories);
        InOrderPrint(node->right);
    }
}

int main()
{
    FILE* input = fopen("../Day1/input.txt", "r");
    if(input == NULL)
    {
        return -1;
    }

    ElfTree* tree = malloc(sizeof(ElfTree));

    tree->root = NULL;


    int elf = 1;
    int calories = 0;
    int tempCal = 0;


    while(!feof(input))
    {
        fscanf(input, "%d", &tempCal);
        calories += tempCal;
        fgetc(input);
        char c = fgetc(input);
        if(c == '\n' || c == EOF)
        {
            ElfNode * newNode = malloc(sizeof(ElfNode));
            newNode->calories = calories;
            newNode->elfNumber = elf;
            newNode->left = NULL;
            newNode->right = NULL;
            bstInsertion(tree, tree->root, newNode);

            calories = 0;
            elf++;
        }
        else
        {
            fseek(input, -1, SEEK_CUR);
        }
    }
    InOrderPrint(tree->root);
}