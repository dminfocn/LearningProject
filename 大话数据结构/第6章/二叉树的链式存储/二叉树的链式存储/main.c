//
//  main.c
//  二叉树的链式存储
//
//  Created by 朱占龙 on 2017/11/4.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */

#define ClearBiTree DestroyBiTree

typedef int Status;  /* Status是函数的类型,其值是函数结果状态代码，如OK等 */


/* 用于构造二叉树********************************** */
int indexVal = 1;
typedef char String[24]; /*  0号单元存放串的长度 */
String str;

typedef char ElemType;
ElemType Nil = ' ';/*字符为空*/

typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;/*左右孩子指针*/
}BiTNode, *BiTree;

Status InitBiTree(BiTree *T) {
    *T = NULL;
    return OK;
}

Status StrAssign(String T, char *chars) {
    int i;
    if (strlen(chars) > MAXSIZE) {
        return ERROR;
    }else {
        T[0] = strlen(chars);
        for (i = 1; i<=T[0]; i++) {
            T[i] = *(chars + i -1);
        }
    }
    return OK;
}

/* 按前序输入二叉树中结点的值（一个字符） */
/* #表示空树，构造二叉链表表示二叉树T。 */
Status CreateBiTree(BiTree *T) {
    ElemType ch;
    ch = str[indexVal++];
    if (ch == '#') {
        *T = NULL;
    }else {
        *T = (BiTree) malloc(sizeof(BiTNode));
        if (!(*T)) {
            exit(OVERFLOW);
        }
        (*T)->data = ch;/* 生成根结点 */
        CreateBiTree(&(*T)->lchild);/*创建左子树*/
        CreateBiTree(&(*T)->rchild);/*创建右子树*/
    }
    return OK;
}

Status BiTreeEmpty(BiTree B) {
    if (!B) {
        return TRUE;
    }else {
        return FALSE;
    }
}

int BiTreeDepth(BiTree T) {
    int i, j;
    if (!T) {
        return 0;
    }
    if (T->lchild) {
        i = BiTreeDepth(T->lchild);
    }else {
        i = 0;
    }
    if (T->rchild) {
        j = BiTreeDepth(T->rchild);
    }else {
        j = 0;
    }
    return i>j ? i+1 : j+1;
}

ElemType Root(BiTree T) {
    if (BiTreeEmpty(T)) {
        return Nil;
    }else {
        return T->data;
    }
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 前序递归遍历T */
void PreOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    printf("%c", T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

void InOrderTraverse(BiTree T){
    if (T == NULL) {
        return;
    }
    PreOrderTraverse(T->lchild);
    printf("%c", T->data);
    PreOrderTraverse(T->rchild);
}

void PostOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
    printf("%c", T->data);
}
/* 初始条件: 二叉树T存在。操作结果: 销毁二叉树T */
void DestroyBiTree(BiTree *T) {
    if (*T) {
        if ((*T)->lchild) {
            DestroyBiTree(&(*T)->lchild);
        }
        if ((*T)->rchild) {
            DestroyBiTree(&(*T)->rchild);
        }
        free(*T);
        *T = NULL;
    }
}

int main(int argc, const char * argv[]) {
    int i;
    BiTree T;
    ElemType e1;
    
    InitBiTree(&T);
    
    StrAssign(str, "ABDH#K###E##CFI###G#J##");
    
    CreateBiTree(&T);
    
    printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    e1=Root(T);
    printf("二叉树的根为: %c\n",e1);
    
    printf("\n前序遍历二叉树:");
    PreOrderTraverse(T);
    printf("\n中序遍历二叉树:");
    InOrderTraverse(T);
    printf("\n后序遍历二叉树:");
    PostOrderTraverse(T);
    
    printf("\n");
    
    ClearBiTree(&T);
    printf("\n清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    i=Root(T);
    
    if(i==Nil){
        printf("树空，无根\n");
    }
    return 0;
}
