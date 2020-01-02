#include "familytree.h"
#include <stdlib.h>
#include <string.h>
Human randHuman(void);

int main(void)
{
    printf("hello world\n");
    Human or ;
    strcpy(or.name, "小明");
    or.gender = Gender_Man;
    sprintf(or.birthday, "%s", __DATE__);
    FamilyTree *treem = newFamilyTree(or, "这是一个悲伤的家族");
    strcpy(or.name, "小红");
    or.gender = Gender_Woman;
    FamilyTree *treeh = newFamilyTree(or, "这是一个悲伤的家族的老婆家族");

    marryPeople(treeh->root, treem->root);
    insertNewBaby(treem->root, randHuman());
    deleteFamilyTree(treem);
    deleteFamilyTree(treeh);
    return 0;
}

const char *firstName[] = {
    "赵",
    "钱",
    "孙",
    "李",
    "周",
    "吴",
    "郑",
    "王",
};
const char *lastName[] = {
    "甲",
    "乙 ",
    "丙 ",
    "丁",
    "戊",
    "己",
    "庚",
    "辛",
    "壬",
    "葵"};
Human randHuman(void)
{
    Human ret;
    strcpy(ret.name, firstName[rand() % (8)]);
    strcat(ret.name, lastName[rand() % 10]);
    ret.gender = (rand() % 2) ? (Gender_Man) : (Gender_Woman);
    sprintf(ret.birthday, "19%d-%02d-%02d %02d:%02d",
            rand() % 100, rand() % 12 + 1,
            rand() % 30 + 1, rand() % 24 + 1,
            rand() % 61);
    return ret;
}