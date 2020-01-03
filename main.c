#include <stdlib.h>
#include <string.h>

#include "familytree.h"
Human randHuman(void);
Human createHuman(char *name, char *date, Gender_e g);

int main(void)
{
    mwInit();
    ///< 天地生小明
    FamilyTree *family = newFamilyTree(createHuman("小明", "1949-11-11", Gender_Man), "天地生小明");

    FamilyNode *alittleMing = findFamilyNodeByName(family, "小明");

    marryPeople(
        newFamilyNode(createHuman("蛙蛙", "1949-12-12", Gender_Woman)),
        alittleMing);

    //生孩子叫 武大郎 武松
    insertNewBaby(alittleMing, createHuman("武大郎", "1969-11-11", Gender_Man));
    insertNewBaby(alittleMing, createHuman("武松", "1970-11-11", Gender_Man));

    //武大郎结婚啦
    FamilyNode *bigMan = findFamilyNodeByName(family, "武大郎");
    marryPeople(newFamilyNode(createHuman("潘金莲", "1970-12-12", Gender_Woman)),
                bigMan);

    //武松结婚啦
    FamilyNode *tigerKiller = findFamilyNodeByName(family, "武松");
    marryPeople(newFamilyNode(createHuman("玉兰", "1971-11-11", Gender_Woman)),
                tigerKiller);

    // 生娃 ing
    insertNewBaby(bigMan, createHuman("西红沁", "1990-11-11", Gender_Woman));
    insertNewBaby(bigMan, createHuman("武云", "1993-11-11", Gender_Man));

    insertNewBaby(tigerKiller, createHuman("武龙", "1995-11-11", Gender_Man));
    insertNewBaby(tigerKiller, createHuman("武丽", "1996-11-11", Gender_Woman));

    //小明的孙子们也要结婚了~
    FamilyNode *cloud = findFamilyNodeByName(family, "武云");
    marryPeople(newFamilyNode(createHuman("静香", "1997-7-17", Gender_Woman)),
                cloud);

    marryPeople(newFamilyNode(createHuman("潘勇", "1989-8-27", Gender_Man)),
                findFamilyNodeByName(family, "西红沁"));

    marryPeople(newFamilyNode(createHuman("李娜", "1996-8-08", Gender_Woman)),
                findFamilyNodeByName(family, "武龙"));

    //武云的宝宝出生了
    insertNewBaby(cloud, createHuman("武毛", "2020-01-03", Gender_Woman));
    insertNewBaby(cloud, createHuman("武重", "2020-01-03", Gender_Man));

    printFamily(family->root);

    K_INFOMATION("发现%s的老婆%s搞外遇,他的女儿不是他亲生的~好惨啊~\n\n", bigMan->man.name, bigMan->soulmate->man.name);

    K_INFOMATION("将 西红沁 踢出族谱~!!!%s", "\n");
    removeFamilyNode(findFamilyNodeByName(family, "西红沁"));

    K_INFOMATION("最终的族谱为%s", "\n");
    printFamily(family->root);

    K_INFOMATION("展示武大郎的兄弟%s", "\n");
    printBrother(bigMan);

    K_INFOMATION("展示武云的堂兄弟%s", "\n");
    printCousin(cloud);

    deleteFamilyTree(family);

    mwTerm();
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
Human createHuman(char *name, char *date, Gender_e g)
{
    Human ret;
    strcpy(ret.name, name);
    strcpy(ret.birthday, date);
    ret.gender = g;
    return ret;
}

void maintest1(void)
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
    {
        FamilyNode *p = findParent(treem->root->children);
        printf("papa = %s,mama = %s\n", p->man.name, p->soulmate->man.name);
    }
    printf("\n\n\n");
    printFamily(treem->root);
    deleteFamilyTree(treem);
}