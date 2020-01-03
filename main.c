#include <stdlib.h>
#include <string.h>

#include "familytree.h"
Human randHuman(void);
Human createHuman(char *name, char *date, Gender_e g);

int main(void)
{
    mwInit();
    ///< �����С��
    FamilyTree *family = newFamilyTree(createHuman("С��", "1949-11-11", Gender_Man), "�����С��");

    FamilyNode *alittleMing = findFamilyNodeByName(family, "С��");

    marryPeople(
        newFamilyNode(createHuman("����", "1949-12-12", Gender_Woman)),
        alittleMing);

    //�����ӽ� ����� ����
    insertNewBaby(alittleMing, createHuman("�����", "1969-11-11", Gender_Man));
    insertNewBaby(alittleMing, createHuman("����", "1970-11-11", Gender_Man));

    //����ɽ����
    FamilyNode *bigMan = findFamilyNodeByName(family, "�����");
    marryPeople(newFamilyNode(createHuman("�˽���", "1970-12-12", Gender_Woman)),
                bigMan);

    //���ɽ����
    FamilyNode *tigerKiller = findFamilyNodeByName(family, "����");
    marryPeople(newFamilyNode(createHuman("����", "1971-11-11", Gender_Woman)),
                tigerKiller);

    // ���� ing
    insertNewBaby(bigMan, createHuman("������", "1990-11-11", Gender_Woman));
    insertNewBaby(bigMan, createHuman("����", "1993-11-11", Gender_Man));

    insertNewBaby(tigerKiller, createHuman("����", "1995-11-11", Gender_Man));
    insertNewBaby(tigerKiller, createHuman("����", "1996-11-11", Gender_Woman));

    //С����������ҲҪ�����~
    FamilyNode *cloud = findFamilyNodeByName(family, "����");
    marryPeople(newFamilyNode(createHuman("����", "1997-7-17", Gender_Woman)),
                cloud);

    marryPeople(newFamilyNode(createHuman("����", "1989-8-27", Gender_Man)),
                findFamilyNodeByName(family, "������"));

    marryPeople(newFamilyNode(createHuman("����", "1996-8-08", Gender_Woman)),
                findFamilyNodeByName(family, "����"));

    //���Ƶı���������
    insertNewBaby(cloud, createHuman("��ë", "2020-01-03", Gender_Woman));
    insertNewBaby(cloud, createHuman("����", "2020-01-03", Gender_Man));

    printFamily(family->root);

    K_INFOMATION("����%s������%s������,����Ů��������������~�òҰ�~\n\n", bigMan->man.name, bigMan->soulmate->man.name);

    K_INFOMATION("�� ������ �߳�����~!!!%s", "\n");
    removeFamilyNode(findFamilyNodeByName(family, "������"));

    K_INFOMATION("���յ�����Ϊ%s", "\n");
    printFamily(family->root);

    K_INFOMATION("չʾ����ɵ��ֵ�%s", "\n");
    printBrother(bigMan);

    K_INFOMATION("չʾ���Ƶ����ֵ�%s", "\n");
    printCousin(cloud);

    deleteFamilyTree(family);

    mwTerm();
    return 0;
}

const char *firstName[] = {
    "��",
    "Ǯ",
    "��",
    "��",
    "��",
    "��",
    "֣",
    "��",
};
const char *lastName[] = {
    "��",
    "�� ",
    "�� ",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��"};
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
    strcpy(or.name, "С��");
    or.gender = Gender_Man;
    sprintf(or.birthday, "%s", __DATE__);
    FamilyTree *treem = newFamilyTree(or, "����һ�����˵ļ���");
    strcpy(or.name, "С��");
    or.gender = Gender_Woman;
    FamilyTree *treeh = newFamilyTree(or, "����һ�����˵ļ�������ż���");

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