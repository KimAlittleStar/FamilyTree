# C语言使用树设计族谱  

## 完整代码地址: [Github](https://github.com/KimAlittleStar/FamilyTree)  
  
 本项目可使用vscode 打开并编译,详情请参考环境搭建教程:[教程链接](https://github.com/KimAlittleStar/vscode_c_demo)
---

## 问题描述
 **家属关系查询系统**  
 1. 问题描述：用树结构表示你所在家族的家谱关系，实现家族信息的管理与查询。
 2. 具体要求：此系统应实现如下功能。  
     1. 建立(打开)家族关系树。  
     2. 添加(删除)家属成员。  
     3. 家属关系查询，例如查找某人的祖先、双亲、兄弟、孩子、堂兄弟、后代子孙、查询某入居于家族中的第几代。


## 族谱规则
 族谱只会跟踪记录男性以及男性的后代,对于女性我们只会记录她在何时出嫁,并不记录她的后代,或者说族谱中的人员向上追溯的时候默认追溯的是父亲一支的关系;  

## 逻辑分析
 族谱与数据结构中树的概念相结合,每一个节点就是族谱中的个人,于是我们就需要知道每个人最基本的特性,于是就可以抽象化变成树中的属性;   
 - 父母  (parent)       --人
 - 兄弟  (brother)      --人
 - 伴侣  (soulmate)     --人
 - 孩子  (children)     --人
 - 姓名  (name)         --字符串
 - 生辰八字 (birthday)  --日期
 - 性别  (gender)       --性别
  
  那么我们对应的树的结构就出来了
  ```C
  // def Tree node 定义节点
  typedef struct _FamilyNode
  {
      struct _FamilyNode* parent;
      struct _FamilyNode* brother;
      struct _FamilyNode* soulmate;
      struct _FamilyNode* children;
      char name[30];
      char birthday[20];
      char gender[6];
  } FamilyNode;

  // def Family Tree 定义族谱
  typedef struct _FamilyTree
  {
      FamilyNode* root;
      int deep;
  } FamilyTree;
  ```
  

## 其他问题

- **关于孩子的问题**  
很多人的孩子不止一个,那么我们就会将二儿子/三儿子添加到对应的孩子的brother指针,并且将parent指针指向自己哥哥的父母;

- **关于离婚的问题**  
  我们都是好孩子,不考虑离婚再婚.

- **关于变性问题**  
  - ### ***不考虑---不要问---问了就是不考虑***  

- 简单示例   
  这是小明家的族谱  
  ![小明族谱.png](https://s2.ax1x.com/2020/01/02/lYybnO.png)  
  ```
  小明->parent = NULL;
  小明->brother = NULL;
  小明->soulmate = NULL;
  小明->children = 武大郎;

  武大郎->parent = 小明;
  武大郎->brother = 武松;
  武大郎->soulmate = 潘金莲;
  武大郎->children = 小红;

  武松->parent = 小明;
  武松->brother = NULL;
  武松->soulmate = 玉兰;
  武松->children = 龙龙;

  ....

  ```

## **代码实现部分**  

### 头文件定义

 ```C
 // headfile familytree.h

 #ifndef _familytree_h
 #define _familytree_h
 #include <stdio.h>
 
 typedef struct
 {
     char name[30];
     char birthday[20];
     char gender[6];
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
 
 FamilyTree *newFamilyTree(Human origin);
 void *deleteFamilyTree(FamilyTree *tree);
 
 int insertNewBaby(FamilyNode *parent, Human baby);
 int marryPeople(FamilyNode *wifi, FamilyNode *husband);
 int editFamilyNode(FamilyNode *old, FamilyNode *newone);
 void removeFamilyNode(FamilyTree *tree, FamilyNode *node);
 
 FamilyNode *findFamilyNodee(Human man);
 FamilyNode *findOrigin(FamilyNode *node, int generation);
 FamilyNode *findParent(FamilyNode *node);
 
 void printBrother(FamilyNode *node);
 void printCousin(FamilyNode *node);
 
 extern int
 compareFamilyNode(FamilyNode *a, FamilyNode *b);
 
 #endif // _familytree_h
 ```  

### 增删改查基础操作

#### 1. new 一个家族的崛起
  为了方便后续的管理,我重新自定义了一个FamilyTree,实际上来说任何一个FamilyNode都是一个familytree,但是不能人人都是先祖把~所以咱们得要有一个根~
  于是乎:
  ```C
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
  ```
#### 2. delete 这个家族覆灭了  
 有生就有死,不可能我只New 没有Delete,这样不符合计算机的要求,也不符合自然的规律,当这个家族不复存在时(俗称满门抄斩),我们就会将其删除.
 ```C
 void deleteFamilyTree(FamilyTree *tree)
 {
     if (tree != NULL)
     {
         if (tree->root != NULL)
             removeFamilyNode(tree->root);
         free(tree);
     }
 } 
 ```

#### 3. insert 我要当爸爸了
 当新生命出现,我们的家族进一步壮大
 ```C
 int insertNewBaby(FamilyNode *parent, Human baby)
 {
     if (parent == NULL)
         return 0;
     if (parent->soulmate == NULL)
     {
         K_ERROR("%s没有爱人\n", parent->man.name);
         return 0;
     }
     FamilyNode *chld = (FamilyNode *)malloc(sizeof (FamilyNode));
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
     K_INFOMATION("%s和%s的结合在%s诞生了一名叫%s的小%s孩 \n",
                  parent->man.name,
                  parent->soulmate->man.name,
                  chld->man.birthday,
                  chld->man.name,
                  (chld->man.gender == Gender_Man) ? ("男 ") : ("女"));
     return 1;
 }
 ```
#### 4. edit 我把我儿子改名叫"狗子"  
 ```C
    Human son;
    strcpy(son.name."二狗子");
    FamilyNode* myson = findFamilyNode(myFamilyTree,son);
    strcpy( myson->man.name,"狗子");
 ```
#### 5. remove 我与某某人断绝父子关系
 断绝关系之后,你的孙子就不是你的孙子,你的儿媳也不是你的儿媳,你就是你,既不妖艳,也不清高;
 ```C
 ///< 递归删除当前节点下的所有子节点下的所有元素
 void removeFamilyNode(FamilyNode *node)
 {
     if (node == NULL)
         return;
     node->deep = 0;    //深度置0 ,表示当前节点节点需要删除
     removeFamilyNode(node->children);
     if (node->parent == NULL || node->parent->deep == 0) //如果 父母都要被删除,那么他的兄弟也要被删除
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
             while (tmp->brother != node && tmp->brother  != NULL)
                 tmp = tmp->brother;
             tmp->brother = node->brother;
         }
     }
     free(node);
 }
 ```
#### 6. find 皇上派我来查查你的底细  
 3分钟我要这个人的全部资料,这个女人朕要定了!  
 皇上~~(颤抖),武大郎是个男的~(哭了)
 ```C
 FamilyNode *findFamilyNode(FamilyTree *tree, Human man)
 {
     if (tree == NULL || tree->root == NULL)
         return NULL;
     return findFamilyNodeByNode(tree->root, &man);
 }
 ```
  
### 解决上述题目中的几个问题

 1. **找祖先**  
   你找第几代祖先~?  
   再族谱里,你想找几代就找几代~
   ```C
   //使用方式: findOrigin(tigerKiller,1);  //往上找武松一代祖先
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
   ```
 2. **找双亲**  
   ```C
   FamilyNode *findParent(FamilyNode *node)
   {
       if (node == NULL)
           return NULL;
       return node->parent;
   }
   ```
 3. **找兄弟**
   ```C
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
   ```
 4. **找孩子**
   ```c
   // someone->children 后遍历 孩子的 brother 即可
   ```
 5. **找堂兄弟**
   ```c
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
   ```
 6. **找后代子孙**  
   ```c
   void printFamily(FamilyNode *node)
   {
       if (node == NULL)
       {
           return;
       }
   
       for (int i = 0; i < node->deep; i++)
       {
           char *c = " ";
           if (i == node->deep - 2)
               c = "└";
           else if (i == node->deep - 1)
               c = "--";
           else
               c = "  ";
   
           K_PRINT("%s", c);
       }
       K_PRINT("%s:%s生,性别 %s", node->man.name,
               node->man.birthday, GENDER_TO_STR   (node->man.gender));
       if (node->soulmate != NULL)
       {
           K_PRINT(",伴侣: %s, 性别: %s",
                   node->soulmate->man.name,
                   GENDER_TO_STR(node->soulmate->man.gender)   );
       }
       K_PRINT("%s", "\n");
       printFamily(node->children);
       printFamily(node->brother);
   }
   ```
 7. **查询某人居于家族中的第几代**
   ```c
   someone->deep;
   ```

### 运行结果
```
>[Congratulation] :小明和蛙蛙喜结连理,祝他们百年好合  
  >[Info] :小明和蛙蛙的结合在1969-11-11诞生了一名叫武大郎的小男孩  
  >[Info] :小明和蛙蛙的结合在1970-11-11诞生了一名叫武松的小男孩  
  >[Congratulation] :武大郎和潘金莲喜结连理,祝他们百年好合  
  >[Congratulation] :武松和玉兰喜结连理,祝他们百年好合  
  >[Info] :武大郎和潘金莲的结合在1990-11-11诞生了一名叫西红沁的小女孩  
  >[Info] :武大郎和潘金莲的结合在1993-11-11诞生了一名叫武云的小男孩  
  >[Info] :武松和玉兰的结合在1995-11-11诞生了一名叫武龙的小男孩  
  >[Info] :武松和玉兰的结合在1996-11-11诞生了一名叫武丽的小女孩  
  >[Congratulation] :武云和静香喜结连理,祝他们百年好合  
  >[Warning] :潘勇是上门女婿  
  >[Congratulation] :西红沁和潘勇喜结连理,祝他们百年好合  
  >[Congratulation] :武龙和李娜喜结连理,祝他们百年好合  
  >[Info] :武云和静香的结合在2020-01-03诞生了一名叫武毛的小女孩  
  >[Info] :武云和静香的结合在2020-01-03诞生了一名叫武重的小男孩  
--小明:1949-11-11生,性别 男,伴侣: 蛙蛙, 性别: 女  
└--武大郎:1969-11-11生,性别 男,伴侣: 潘金莲, 性别: 女  
  └--西红沁:1990-11-11生,性别 女,伴侣: 潘勇, 性别: 男  
  └--武云:1993-11-11生,性别 男,伴侣: 静香, 性别: 女  
    └--武毛:2020-01-03生,性别 女  
    └--武重:2020-01-03生,性别 男  
└--武松:1970-11-11生,性别 男,伴侣: 玉兰, 性别: 女  
  └--武龙:1995-11-11生,性别 男,伴侣: 李娜, 性别: 女  
  └--武丽:1996-11-11生,性别 女  
  >[Info] :发现武大郎的老婆潘金莲搞外遇,他的女儿不是他亲生的~  好惨啊~  
  >[Info] :将 西红沁 踢出族谱~!!!  
  >[Info] :最终的族谱为  
--小明:1949-11-11生,性别 男,伴侣: 蛙蛙, 性别: 女  
└--武大郎:1969-11-11生,性别 男,伴侣: 潘金莲, 性别: 女  
  └--武云:1993-11-11生,性别 男,伴侣: 静香, 性别: 女  
    └--武毛:2020-01-03生,性别 女  
    └--武重:2020-01-03生,性别 男  
└--武松:1970-11-11生,性别 男,伴侣: 玉兰, 性别: 女  
  └--武龙:1995-11-11生,性别 男,伴侣: 李娜, 性别: 女  
  └--武丽:1996-11-11生,性别 女  
  >[Info] :展示武大郎的兄弟  
武大郎的兄弟姐妹有:  武松  
  >[Info] :展示武云的堂兄弟  
武云的堂兄弟姐妹有:  武龙  
  武丽  
```
## 后记  
 本问题并不考虑算法问题,因此效率/空间/时间复杂度在这里不做考虑;

