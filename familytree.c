#include "familytree.h"
#include <stdlib.h>
#include <string.h>

FamilyTree *newFamilyTree(Human origin, char *introduce)
{
    FamilyTree *ret = (FamilyTree *)malloc(sizeof(FamilyTree));
    if (introduce != NULL)
        strcpy(ret->introduce, introduce);
    ret->root = (FamilyNode *)malloc(sizeof(FamilyNode));
    memset(ret->root, 0, sizeof(FamilyNode));
    ret->root->man = origin;
    ret->root->deep = 1;
    return ret;
}
void deleteFamilyTree(FamilyTree *tree)
{
    if (tree != NULL)
    {
        if (tree->root != NULL)
            removeFamilyNode(tree->root);
        free(tree);
    }
}

int insertNewBaby(FamilyNode *parent, Human baby)
{
    if (parent == NULL)
        return 0;
    if (parent->soulmate == NULL)
    {
        K_ERROR("%s没有爱人\n", parent->man.name);
        return 0;
    }
    FamilyNode *chld = (FamilyNode *)malloc(sizeof(FamilyNode));
    memset(chld, 0, sizeof(FamilyNode));

    chld->man = baby;
    chld->parent = parent;
    if (parent->children == NULL)
    {
        parent->children = chld;
        chld->deep = parent->deep + 1;
    }
    else
    {
        FamilyNode *tmp = parent->children;
        while (tmp->brother != NULL)
            tmp = tmp->brother;
        tmp->brother = chld;
        chld->deep = tmp->deep;
    }
    K_INFOMATION("%s和%s的结合在%s诞生了一名叫%s的小%s孩\n",
                 parent->man.name,
                 parent->soulmate->man.name,
                 chld->man.birthday,
                 chld->man.name,
                 (chld->man.gender == Gender_Man) ? ("男") : ("女"));
    return 1;
}
int marryPeople(FamilyNode *wifi, FamilyNode *husband)
{
    if (wifi == NULL || husband == NULL)
        return 0;
    if (wifi->man.gender == husband->man.gender)
    {
        K_ERROR("%s和%s怎么能搞%s呢?\n", husband->man.name, wifi->man.name, (wifi->man.gender == Gender_Man) ? ("基") : ("拉拉"));
        return 0;
    }
    if (husband->man.gender == Gender_Woman)
    {
        K_WARNINR("%s是上门女婿\n", husband->man.name);
    }
    wifi->soulmate = husband;
    husband->soulmate = wifi;
    K_CONGRATULATION("%s和%s喜结连理,祝他们百年好合\n", husband->man.name, wifi->man.name);
    return 1;
}
int editFamilyNode(FamilyNode *old, FamilyNode *newone)
{
    return 0;
}
void removeFamilyNode(FamilyNode *node)
{
    if (node == NULL)
        return;
    node->deep = 0;
    removeFamilyNode(node->children);
    if (node->parent == NULL || node->parent->deep == 0)
        removeFamilyNode(node->brother);
    else
    {
        FamilyNode *tmp = node->parent->children;
        if (tmp == node)
        {
            node->parent->children = NULL;
        }
        else
        {
            while (tmp->brother != node && tmp->brother != NULL)
                tmp = tmp->brother;
            tmp->brother = node->brother;
        }
    }
    free(node);
}

FamilyNode *findFamilyNode(FamilyTree *tree, Human man)
{
    if (tree == NULL || tree->root == NULL)
        return NULL;
    return findFamilyNodeByNode(tree->root, &man);
}
FamilyNode *findFamilyNodeByNode(FamilyNode *node, Human *man)
{
    FamilyNode *ret = NULL;
    if (node == NULL)
        return NULL;
    if (compareMan(&node->man, man) == 0)
        return node;
    else
    {
        if ((ret = findFamilyNodeByNode(node->brother, man)) == NULL)
        {
            ret = findFamilyNodeByNode(node->children, man);
        }
    }
    return ret;
}

FamilyNode *findOrigin(FamilyNode *node, int generation)
{
    if (node == NULL)
        return NULL;
    FamilyNode *ret = node;
    while (ret->parent != NULL && generation != 0)
    {
        ret = ret->parent;
        generation--;
    }
    return ret;
}
FamilyNode *findParent(FamilyNode *node)
{
    if (node == NULL)
        return NULL;
    return node->parent;
}

void printBrother(FamilyNode *node)
{
    if (node == NULL)
        return;
    FamilyNode *tmp = NULL;
    K_PRINT("%s的兄弟姐妹有:", node->man.name);
    if (node->parent != NULL)
        tmp = node->parent->children;
    else
        tmp = node->brother;
    while (tmp != NULL)
    {
        if (tmp != node)
            K_PRINT("  %s\n", tmp->man.name);
        tmp = tmp->brother;
    }
}

void printCousin(FamilyNode *node)
{
    if (node == NULL || node->parent == NULL)
        return;
    FamilyNode *tmpuncle = NULL;
    FamilyNode *tmpbro = NULL;
    K_PRINT("%s的堂兄弟姐妹有:", node->man.name);
    if (node->parent->parent == NULL)
        tmpuncle = node->parent->brother;
    else
        tmpuncle = node->parent->parent->children;
    while (tmpuncle != NULL)
    {
        tmpbro = tmpuncle->children;
        while (tmpbro != NULL)
        {
            if (tmpbro != node)
                K_PRINT("  %s\n", tmpbro->man.name);
            tmpbro = tmpbro->brother;
        }
        tmpuncle = tmpuncle->brother;
    }
}

int compareMan(Human *a, Human *b)
{
    int ret = -1;
    if ((ret = strcmp(a->name, b->name)) == 0)
    {
        return strcmp(a->birthday, b->birthday);
    }
    else
        return ret;
}