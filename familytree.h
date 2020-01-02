#ifndef _familytree_h
#define _familytree_h
#include "include.h"
#include <stdio.h>

#define K_CONGRATULATION(fmt, ...) K_LOG(Congratulation, fmt, ##__VA_ARGS__)

typedef enum
{
    Gender_Man,
    Gender_Woman
} Gender_e;
typedef struct
{
    char name[30];
    char birthday[20];
    Gender_e gender;
} Human;

typedef struct _FamilyNode
{
    struct _FamilyNode *parent;
    struct _FamilyNode *brother;
    struct _FamilyNode *soulmate;
    struct _FamilyNode *children;
    Human man;
    int deep;
} FamilyNode;

// def Family Tree 定义族谱
typedef struct _FamilyTree
{
    FamilyNode *root;
    char introduce[200]; ///< 对于该族谱的简单介绍
} FamilyTree;

FamilyTree *newFamilyTree(Human origin, char *introduce);
void deleteFamilyTree(FamilyTree *tree);

int insertNewBaby(FamilyNode *parent, Human baby);
int marryPeople(FamilyNode *wifi, FamilyNode *husband);
int editFamilyNode(FamilyNode *old, FamilyNode *newone);
void removeFamilyNode(FamilyNode *node);

FamilyNode *findFamilyNode(FamilyTree *tree, Human man);
FamilyNode *findFamilyNodeByNode(FamilyNode *node, Human *man);

FamilyNode *findOrigin(FamilyNode *node, int generation);
FamilyNode *findParent(FamilyNode *node);

void printBrother(FamilyNode *node);
void printCousin(FamilyNode *node);

extern int compareMan(Human *a, Human *b);

#endif // _familytree_h