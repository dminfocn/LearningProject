//
//  main.c
//  02二叉排序树
//
//  Created by 朱占龙 on 2017/11/12.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERRO 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /*最大容量*/

typedef int Status;

/*二叉树的二叉链表结点结构定义*/
typedef struct BitNode{
    int data;
    struct BitNode *lchild, *rchild;/* 左右孩子指针 */
}BitNode;

typedef struct BitNode *BiTree;

/* 递归查找二叉排序树T中是否存在key, */
/* 指针f指向T的双亲，其初始调用值为NULL */
/* 若查找成功，则指针p指向该数据元素结点，并返回TRUE */
/* 否则指针p指向查找路径上访问的最后一个结点并返回FALSE */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) {
    if(!T) {/*T为空，查找不成功*/
        *p = f;
        return FALSE;
    }else if(T->data == key) {/*查找成功*/
        *p = T;
        return TRUE;
    }else if(key < T -> data) {
        SearchBST(T->lchild, key, f, p);/*  在左子树中继续查找 */
    }else {
        SearchBST(T->rchild, key, f, p);/*在右子树中继续查找*/
    }
    return FALSE;
}

/*  当二叉排序树T中不存在关键字等于key的数据元素时， */
/*  插入key并返回TRUE，否则返回FALSE */
Status InsertBST(BiTree *T, int key) {
    BiTree p,s;
    if(!SearchBST(*T, key, NULL, &p)) {/*查找不成功*/
        s = (BiTree) malloc(sizeof(BitNode));
        s -> data = key;
        s -> lchild = s -> rchild = NULL;
        if(!p) {/*插入s为根节点*/
            *T = s;
        }else if(key < p -> data) {/*插入s为左孩子*/
            p -> lchild = s;
        }else {
            p -> rchild = s;
        }
        return TRUE;
    }else {
        return FALSE;/*  树中已有关键字相同的结点，不再插入 */
    }
}

Status Delete(BiTree *p) {
    BiTree q,s;
    if((*p) -> rchild == NULL) {/* 右子树空则只需重接它的左子树（待删结点是叶子也走此分支) */
        q = *p;
        *p  = (*p) -> lchild;
        free(q);
    }else if((*p) -> lchild == NULL) {/* 只需重接它的右子树 */
        q = *p;
        *p = (*p) -> rchild;
        free(q);
    }else {/*左右子树均存在*/
        q = *p;
        s = (*p) -> lchild;
        while (s -> rchild) {/* 转左，然后向右到尽头（找待删结点的前驱） */
            q = s;
            s = s -> rchild;
        }
        (*p) -> data = s->data;/*s指向被删节点的直接前驱*/
        if(q != *p) {
            q ->rchild = s -> lchild;/*重接q的右子树*/
        }else {
            q -> lchild = s -> lchild;/*重接q的左子树*/
        }
        free(s);
    }
    return TRUE;
}

/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点, */
/* 并返回TRUE；否则返回FALSE。 */
Status DeleteBST(BiTree *T, int key) {
    if(!*T) {
        return FALSE;
    }else {
        if(key == (*T) -> data) {/*找到关键字等于key 的元素，并删除*/
            return Delete(T);
        }else if(key < (*T)->data) {
            DeleteBST(&(*T)->lchild, key);
        }else {
            DeleteBST(&(*T)->rchild, key);
        }
    }
    return OK;
}

int main(int argc, const char * argv[]) {
    int i;
    int a[10] = {62,88,58,47,35,73,51,99,37,93};
    BiTree T = NULL;
    for(i=0; i<10; i++) {
        InsertBST(&T, a[i]);
    }
    
    DeleteBST(&T, 93);
    DeleteBST(&T, 47);
    
    printf("本样例建议断点跟踪查看二叉排序树结构");
    return 0;
}
