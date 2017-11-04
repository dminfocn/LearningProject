//
//  main.c
//  二叉树顺序结构实现
//
//  Created by 朱占龙 on 2017/11/4.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */
#define MAX_TREE_SIZE 100  /* 二叉树的最大结点数 */

#define ClearBiTree InitBiTree /* 在顺序存储结构中，两函数完全一样 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int TElemType;/* 树结点的数据类型，目前暂定为整型 */
typedef TElemType SqBiTree[MAX_TREE_SIZE];

/* 结点的层,本层序号(按满二叉树计算) */
typedef struct {
    int level, order;
}Position;

TElemType Nil = 0;/*  设整型以0为空 */

/* 构造空二叉树T。因为T是固定数组，不会改变，故不需要& */
Status InitBiTree(SqBiTree T) {
    int i;
    for (i=0; i<MAX_TREE_SIZE; i++) {
        T[i] = Nil;
    }
    return OK;
}

/* 按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T */
Status CreateBiTree(SqBiTree T) {
    int i=0;
    printf("请按层序输入节点的值，0表示空结点，输999结束。结点数≤%d\n",MAX_TREE_SIZE);
    while (i<10) {
        T[i]=i+1;
        if (i!=0 && T[(i+1)/2-1]==Nil && T[i]!=Nil) {
            printf("出现无双亲的非根节点");
            exit(ERROR);
        }
        i++;
    }
    while (i<MAX_TREE_SIZE) {
        T[i] = Nil;
        i++;
    }
    return OK;
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
Status BiTreeEmpty(SqBiTree T) {
     /* 根结点为空,则树空 */
    if (T[0] == Nil) {
        return TRUE;
    }else {
        return FALSE;
    }
}


/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
int BiTreeDepth(SqBiTree T) {
    int i, j=-1;
    for (i=MAX_TREE_SIZE-1; i>=0; i--) {
        if (T[i] != Nil) {
            break;
        }
    }
    i++;
    do {
        j++;
    } while (i>=powl(2, j));/* 计算2的j次幂。 */
    return j;
}

/* 初始条件: 二叉树T存在 */
/* 操作结果:  当T不空,用e返回T的根,返回OK;否则返回ERROR,e无定义 */
Status Root(SqBiTree T, TElemType *e) {
    if (BiTreeEmpty(T)) {
        return ERROR;
    }else {
        *e = T[0];
        return OK;
    }
}

Status Visit(TElemType e) {
    printf("%d", e);
    return OK;
}

void LevelOrderTraverse(SqBiTree T) {
    int i = MAX_TREE_SIZE -1, j;
    while (T[i] == Nil) {
        i--;/* 找到最后一个非空结点的序号 */
    }
    for (j=0; j<i; j++) {
        if (T[j] != Nil) {
            Visit(T[j]);
        }
    }
    printf("\n");
}

void PreTraverse(SqBiTree T, int e) {
    Visit(e);
    if (T[2*e + 1] != Nil) {/* 左子树不空 */
        PreTraverse(T, 2*e+1);
    }
    if (T[2*e + 2] != Nil) {/* 右子树不空 */
        PreTraverse(T, 2*e+2);
    }
}

/* 初始条件: 二叉树存在 */
/* 操作结果: 先序遍历T。 */
Status PreOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {
        PreTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

Status InTraverse(SqBiTree T, int e) {
    if (T[e*2+1] != Nil) {
        /*左子树不为空*/
        InTraverse(T, e*2+1);
    }
    Visit(T[e]);
    if (T[e*2 + 2]) {
        /*右子树不为空*/
        InTraverse(T, e*2+2);
    }
    return OK;
}

Status InOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {//树不为空
        InTraverse(T,0);
    }
    printf("\n");
    return OK;
}

Status PostTraverse(SqBiTree T, int e) {
    if (T[2*e+1] != Nil) {
        PostTraverse(T, 2*e+1);
    }
    if (T[2*e+2] != Nil) {
        PostTraverse(T, 2*e+2);
    }
    Visit(T[e]);
    return OK;
}

Status PostOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {
        PostTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

/* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
/* 操作结果: 返回处于位置e(层,本层序号)的结点的值 */
TElemType Value(SqBiTree T, Position e) {
    return T[(int)powl(2, e.level-1) + e.order-2];
}

/* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
/* 操作结果: 给处于位置e(层,本层序号)的结点赋新值value */
Status Assign(SqBiTree T,Position e,TElemType value) {
    int i=(int)powl(2,e.level-1)+e.order-2; /* 将层、本层序号转为矩阵的序号 */
    if(value!=Nil && T[(i+1)/2-1]==Nil) { /* 给叶子赋非空值但双亲为空 */
        return ERROR;
    }else if(value==Nil && (T[i*2+1]!=Nil || T[i*2+2]!=Nil)){ /*  给双亲赋空值但有叶子（不空） */
        return ERROR;
    }
    T[i]=value;
    return OK;
}

/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ */
TElemType Parent(SqBiTree T, TElemType e) {
    int i=0;
    if (T[0] == Nil) {
        return ERROR;
    }
    for (i=1; i<MAX_TREE_SIZE-1; i++) {
        if (T[i] == e) {
            return T[(i+1)/2-1];
        }
    }
    return Nil;
}

/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂ */
TElemType LeftChild(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == Nil) { /* 空树 */
        return Nil;
    }
    for (i=0; i<MAX_TREE_SIZE-1; i++) {
        if (T[i] == e) {
            return T[2*i+1];
        }
    }
    return Nil;
}

TElemType RightChild(SqBiTree T, int e) {
    int i;
    if (T[0] == Nil) { /* 空树 */
        return Nil;
    }
    for (i=0; i<MAX_TREE_SIZE-1; i++) {
        if (T[i] == e) {
            return T[2*i+2];
        }
    }
    return Nil;
}

TElemType LeftSibling(SqBiTree T,  int e) {
    int i;
    if (T[0] == Nil) {
        return ERROR;
    }
    for (i=1; i<MAX_TREE_SIZE-1; i++) {
        if (T[i] == e && i % 2 == 0) {
            return T[i-1];
        }
    }
    return Nil;
}

TElemType RightSibling(SqBiTree T, int e) {
    int i;
    if (T[0] == Nil) {
        return ERROR;
    }
    for (i=1; i<MAX_TREE_SIZE-1; i++) {
        if (T[i] == e && i % 2 == 0) {
            return T[i+1];
        }
    }
    return Nil;
}

int main(int argc, const char * argv[]) {
    
    Status i;
    Position p;
    TElemType e;
    SqBiTree T;
    InitBiTree(T);
    CreateBiTree(T);
    printf("建立二叉树后是否为空：%d（1：是，0：否）,树的深度为：%d\n",BiTreeEmpty(T), BiTreeDepth(T));
    i=Root(T,&e);
    if (i) {
        printf("二叉树的根为：%d\n",e);
    }else {
        printf("数空，无根");
    }
    printf("层序遍历二叉树：\n");
    LevelOrderTraverse(T);
    
    printf("前序遍历二叉树\n");
    PreOrderTraverse(T);
    
    printf("中序遍历二叉树:\n");
    InOrderTraverse(T);
    
    printf("后序遍历二叉树:\n");
    PostOrderTraverse(T);
    
    printf("修改结点的层号3本层序号2。");
    p.level = 3;
    p.order = 2;
    e=Value(T,p);
    printf("待修改结点的原值为%d请输入新值:50 ",e);
    e=50;
    Assign(T,p,e);
    printf("前序遍历二叉树:\n");
    PreOrderTraverse(T);
    printf("结点%d的双亲为%d\n",e,Parent(T,e));
    printf("左右孩子分别为%d,%d\n",LeftChild(T,e),RightChild(T,e));
    printf("左右兄弟为：%d,%d\n",LeftSibling(T,e),RightSibling(T,e));
    
    ClearBiTree(T);
    printf("清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    i=Root(T,&e);
    if(i)
        printf("二叉树的根为：%d\n",e);
    else
        printf("树空，无根\n");
    return 0;
}
