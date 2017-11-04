//
//  main.c
//  03线索二叉树
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

typedef int Status;
typedef char TElemType;
typedef enum {Link, Thread} PointerTag;

typedef struct BiThrNode{
    
    TElemType data;
    struct BiThrNode *lchid, *rchild;
    PointerTag LTag;
    PointerTag RTag;
}BiThrNode, *BiThrTree;

TElemType Nil='#'; /* 字符型以空格符为空 */

BiThrTree pre; /* 全局变量,始终指向刚刚访问过的结点 */

/* 按前序输入二叉线索树中结点的值,构造二叉线索树T */
/* 0(整型)/空格(字符型)表示空结点 */
Status CreateBiThrTree(BiThrTree *T) {
    TElemType h;
    scanf("%c", &h);
    if (h == Nil) {
        *T = NULL;
    }else {
        *T = (BiThrTree) malloc(sizeof(BiThrNode));
        if (!(*T)) {
            exit(OVERFLOW);
        }
        (*T)->data = h;
        CreateBiThrTree(&(*T)->lchid);
        if ((*T)->lchid) {
            (*T)->LTag = Link;
        }
        CreateBiThrTree(&(*T)->rchild);
        if ((*T)->rchild) {
            (*T)->RTag = Link;
        }
    }
    return OK;
}

/* 中序遍历进行中序线索化 */
Status InThreading(BiThrTree P) {
    if (P) {
        InThreading(P->lchid);
        if (!P->lchid) {
            P->LTag = Thread;
            P->lchid = pre;
        }
        if (!pre->rchild) {
            pre->RTag = Thread;
            pre->rchild = P;
        }
        pre = P;
        InThreading(P->rchild);
    }
    return OK;
}

/* 中序遍历二叉树T,并将其中序线索化,Thrt指向头结点 */
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T) {
    *Thrt = (BiThrTree) malloc(sizeof(BiThrNode));
    if (!Thrt) {
        exit(OVERFLOW);
    }
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;
    (*Thrt)->rchild = (*Thrt);
    if (!T) {/* 若二叉树空,则左指针回指 */
        (*Thrt)->lchid = *Thrt;
    }else {
        (*Thrt)->lchid = T;
        pre = (*Thrt);
        InThreading(T);
        pre->rchild = *Thrt;
        pre->RTag = Thread;
        (*Thrt)->rchild = pre;
    }
    return OK;
}

Status visit(TElemType e){
    printf("%c",e);
    return OK;
}

/* 中序遍历二叉线索树T(头结点)的非递归算法 */
Status InOrderTraverse_Thr(BiThrTree T) {
    BiThrTree p;
    p = T->lchid;
    while (p != T) {
        /*空域或者遍历结束时p==T*/
        while (p->LTag == Link) {
            p = p->lchid;
        }
        if (!visit(p->data)) {
            return ERROR;
        }
        while (p->RTag==Thread && p->rchild!=T) {
            p = p->rchild;
            visit(p->data);
        }
        p = p->rchild;
    }
    return OK;
}

int main(int argc, const char * argv[]) {
    BiThrTree H,T;
    printf("请按前序输入二叉树(如:'ABDH##I##EJ###CF##G##')\n");
    CreateBiThrTree(&T);
    InOrderThreading(&H,T); /* 中序遍历,并中序线索化二叉树 */
    printf("中序遍历(输出)二叉线索树:\n");
    
    InOrderTraverse_Thr(H); /* 中序遍历(输出)二叉线索树 */
    printf("\n");
    return 0;
}
