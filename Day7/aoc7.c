#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUGMA 100000

struct ListNode
{
    struct Node* directory;
    struct ListNode* next;
    struct ListNode* previous;
};

typedef struct ListNode ListNode;

struct List{
    int size;
    ListNode* head;
    ListNode* tail;
};

typedef struct List List;


struct Node{
    char* dirName;
    int dirAmount;
    int dirDimension;
    struct Node* father;
    List* subDirectories;
};

typedef struct Node Node;

struct Tree{
    Node* root;
};

typedef struct Tree Tree;

Node* directoryToDelete;
int current = INT_MAX;


List* newList()
{
    List* list = malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

ListNode* newListNode(Node* node)
{
    ListNode* newListNode = malloc(sizeof(ListNode));
    newListNode->directory = node;
    newListNode->next = NULL;
    newListNode->previous = NULL;

    return newListNode;
}

void addToList(List* list, Node* node)
{
    ListNode* newSubDir = newListNode(node);
    if(list->head == NULL)
    {
        //Empty list
        list->head = newSubDir;
        list->tail = newSubDir;
    }
    else
    {
        list->tail->next = newSubDir;
        newSubDir->previous = list->tail;
        list->tail = newSubDir;
    }

    list->size++;
}

Node* newNode(char* dirName, int nameSize)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->dirName = malloc(nameSize);
    memcpy(newNode->dirName, dirName, nameSize);
    newNode->dirName[nameSize] = '\0';
    newNode->dirAmount = 0;
    newNode->dirDimension = 0;
    newNode->father = NULL;
    newNode->subDirectories = newList();

    return newNode;
}

void CreateDir(Node * node, char* dirName, int nameSize)
{
    node->dirAmount++;
    Node* newDir = newNode(dirName, nameSize);
    newDir->father = node;
    addToList(node->subDirectories, newDir);
}

Node* findDirectory(Node* directory, char* name)
{
    List* subDirs = directory->subDirectories;
    ListNode* traveler = subDirs->head;

    while(traveler != NULL)
    {
        if (strcmp(name, traveler->directory->dirName) == 0)
        {
            return traveler->directory;
        }
        else
        {
            traveler = traveler->next;
        }
    }

    return NULL;
}

int setFileSystemSize(Node* node)
{
    if(node->subDirectories->size == 0)
    {
        return node->dirDimension;
    }
    else
    {
        ListNode* traveler = node->subDirectories->head;
        for(int i = 0; i < node->subDirectories->size; i++)
        {
            node->dirDimension += setFileSystemSize(traveler->directory);
            traveler = traveler->next;
        }
    }

    return node->dirDimension;
}

int sumDir(Node* node)
{
    if(node->subDirectories->size == 0)
    {
        if(node->dirDimension <= SUGMA)
        {
            return node->dirDimension;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        int sumOfSubs = 0;
        ListNode* traveler = node->subDirectories->head;
        for(int i = 0; i < node->subDirectories->size; i++)
        {
            sumOfSubs += sumDir(traveler->directory);
            traveler = traveler->next;
        }

        if(node->dirDimension <= SUGMA)
        {
            sumOfSubs += node->dirDimension;
            return sumOfSubs;
        }
        else
        {
            return sumOfSubs;
        }
    }
}


void findDirectoryToDelete(Node* node, int freespace, int updatesize)
{
    if(node->dirAmount == 0)
    {
        if(freespace + node->dirDimension < current && freespace + node->dirDimension >= updatesize)
        {
            current = freespace + node->dirDimension;
            directoryToDelete = node;
            return;
        }
    }
    else
    {
        ListNode* traveler = node->subDirectories->head;
        for(int i = 0; i < node->subDirectories->size; i++)
        {
            findDirectoryToDelete(traveler->directory, freespace, updatesize);
            traveler = traveler->next;
        }
        if(freespace + node->dirDimension < current && freespace + node->dirDimension >= updatesize)
        {
            current = freespace + node->dirDimension;
            directoryToDelete = node;
            return;
        }
    }
}

int main()
{
    FILE *input = fopen("../Day7/input.txt", "r");
    if (input == NULL) {
        return -1;
    }

    char command[100];
    char inputChar;
    int position;

    Tree* filesystem = malloc(sizeof(Tree));
    filesystem->root = newNode("\\0", 1);

    Node* currentDirectory = filesystem->root;

    while(!feof(input))
    {
        position = 0;
        while ((inputChar = fgetc(input)) != '\n' && !feof(input))
        {
            command[position] = inputChar;
            position++;
        }
        command[position] = '\0';


        if(command[0] == '$') {
            if (command[2] == 'c')
            {
                char nextDirName[100];
                int pos = 0;
                for(int i = 0; command[i+5] != '\0'; i++)
                {
                    nextDirName[i] = command[i+5];
                    pos++;
                }
                nextDirName[pos] = '\0';

                if(nextDirName[0] == '.')
                {
                    currentDirectory = currentDirectory->father;
                }
                else if(nextDirName[0] == '/')
                {
                    currentDirectory = filesystem->root;
                }
                else
                {
                    Node *nextDirectory = findDirectory(currentDirectory, nextDirName);

                    currentDirectory = nextDirectory;
                }
            }
            else if (command[2] == 'l')
            {
                char c = fgetc(input);
                while(c != '$' && !feof(input))
                {
                    if (c  == 'd')
                    {
                        fgetc(input);
                        fgetc(input);
                        fgetc(input);
                        char newDirName[100];
                        int pos = 0;
                        while ((inputChar = fgetc(input)) != '\n' && !feof(input))
                        {
                            newDirName[pos] = inputChar;
                            pos++;
                        }
                        newDirName[pos] = '\0';
                        CreateDir(currentDirectory, newDirName, pos);
                    }
                    else
                    {
                        fseek(input, -1, SEEK_CUR);
                        int dim;
                        fscanf(input, "%d", &dim);
                        currentDirectory->dirDimension += dim;
                        while ((inputChar = fgetc(input)) != '\n' && !feof(input));
                    }
                    c = fgetc(input);
                }
                fseek(input, -1, SEEK_CUR);
            }
        }

    }


    setFileSystemSize(filesystem->root);

    printf("FileSystem setup complete\n");
    //PT1
    printf("Answer is %d\n", sumDir(filesystem->root));


    //PT2
    int fileSystemSize = 70000000;
    int UpdateSize = 30000000;
    int freeSpace = fileSystemSize - filesystem->root->dirDimension;

    findDirectoryToDelete(filesystem->root, freeSpace, UpdateSize);

    printf("If update size is %d you should delete directory %s with size %d", UpdateSize, directoryToDelete->dirName, directoryToDelete->dirDimension);

}